template <class T, class Op = SumOperation<T> >
class IntervalTree2D {
 public:
  explicit IntervalTree2D(int r, int c) {
    rows = r;
    cols = c;
    int row_nodes = std::max(1, high_bit(rows) * 2);
    int col_nodes = std::max(1, high_bit(cols) * 2);
    values.resize(row_nodes, std::vector<T>(col_nodes));
    init(0, 0, rows - 1);
  }

  explicit IntervalTree2D(int size) {
    rows = cols = size;
    int num_nodes = std::max(1, high_bit(rows) * 2);
    values.resize(num_nodes, std::vector<T>(num_nodes));
    init(0, 0, rows - 1);
  }

  void update(int row_at, int col_at, T val) {  // 单点更新
    update(0, 0, rows - 1, row_at, col_at, val);
  }

  T query(int from_row, int to_row, int from_col, int to_col) {
    return query(0, 0, rows - 1, from_row, to_row, from_col, to_col);
  }

 private:
  int rows, cols;
  std::vector<std::vector<T> > values;

  static int high_bit(int x) {
    int res = 1;
    while (res < x) { res *= 2; }
    return res;
  }

  void sub_init(int row_id, int root, int left, int right) {
    values[row_id][root] = Op::neutral_value();
    if (left != right) {
      int mid = (left + right) / 2;
      sub_init(row_id, root * 2 + 1, left, mid);
      sub_init(row_id, root * 2 + 2, mid + 1, right);
    }
  }

  void init(int root, int left, int right) {
    sub_init(root, 0, 0, cols - 1);
    if (left != right) {
      int mid = (left + right) / 2;
      init(root * 2 + 1, left, mid);
      init(root * 2 + 2, mid + 1, right);
    }
  }

  void sub_update(
      int root, int left, int right, int row_id, int col_at, T val) {
    if (left == right) {
      values[row_id][root] = Op::join_delta(values[row_id][root], val);
    } else {
      int mid = (left + right) / 2;
      if (col_at <= mid) {
        sub_update(root * 2 + 1, left, mid, row_id, col_at, val);
      } else {
        sub_update(root * 2 + 2, mid + 1, right, row_id, col_at, val);
      }
      values[row_id][root] = Op::join_value(
          values[row_id][root * 2 + 1], values[row_id][root * 2 + 2]);
    }
  }

  void update(int root, int left, int right, int row_at, int col_at, T val) {
    sub_update(0, 0, cols - 1, root, col_at, val);
    if (left != right) {
      int mid = (left + right) / 2;
      if (row_at <= mid) {
        update(root * 2 + 1, left, mid, row_at, col_at, val);
      } else {
        update(root * 2 + 2, mid + 1, right, row_at, col_at, val);
      }
    }
  }

  T sub_query(int root, int left, int right, int row_id, int from, int to) {
    if (left > to || right < from) { return Op::neutral_value(); }
    if (from <= left && to >= right) { return values[row_id][root]; }
    int mid = (left + right) / 2;
    T left_result = sub_query(root * 2 + 1, left, mid, row_id, from, to);
    T right_result = sub_query(root * 2 + 2, mid + 1, right, row_id, from, to);
    return Op::join_value(left_result, right_result);
  }

  T query(
      int root, int left, int right, int from_row, int to_row,
      int from_col, int to_col) {
    if (left > to_row || right < from_row) { return Op::neutral_value(); }
    if (from_row <= left && to_row >= right) {
      return sub_query(0, 0, cols - 1, root, from_col, to_col);
    }
    int mid = (left + right) / 2;
    T left_result = query(
        root * 2 + 1, left, mid, from_row, to_row, from_col, to_col);
    T right_result = query(
        root * 2 + 2, mid + 1, right, from_row, to_row, from_col, to_col);
    return Op::join_value(left_result, right_result);
  }
};
