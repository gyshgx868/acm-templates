template <class T, class Op = SumOperation<T> >
class IntervalTree {
 public:
  explicit IntervalTree(int n) {
    size = n;
    int num_nodes = std::max(1, size * 4);
    values.resize(num_nodes, T());
    deltas.resize(num_nodes, T());
    if (size != 0) { init_empty(0, 0, size - 1); }
  }

  explicit IntervalTree(const std::vector<T>& arr) {
    size = arr.size();
    int num_nodes = std::max(1, size * 4);
    values.resize(num_nodes, T());
    deltas.resize(num_nodes, T());
    if (size != 0) { init_array(arr, 0, 0, size - 1); }
  }

  void update(int from, int to, T delta) {
    update(0, 0, size - 1, from, to, delta);
  }

  T query(int from, int to) { return query(0, 0, size - 1, from, to); }

 protected:
  int size;

  void push_down(int root, int left, int middle, int right) {
    values[2 * root + 1] =
        Op::accumulate(values[2 * root + 1], deltas[root], middle - left + 1);
    values[2 * root + 2] =
        Op::accumulate(values[2 * root + 2], deltas[root], right - middle);
    deltas[2 * root + 1] = Op::join_delta(deltas[2 * root + 1], deltas[root]);
    deltas[2 * root + 2] = Op::join_delta(deltas[2 * root + 2], deltas[root]);
    deltas[root] = Op::neutral_delta();
  }

  void update(int root, int left, int right, int from, int to, T delta) {
    if (left > to || right < from) { return; }
    if (left >= from && right <= to) {
      values[root] = Op::accumulate(values[root], delta, right - left + 1);
      deltas[root] = Op::join_delta(deltas[root], delta);
      return;
    }
    int middle = (left + right) / 2;
    push_down(root, left, middle, right);
    update(2 * root + 1, left, middle, from, to, delta);
    update(2 * root + 2, middle + 1, right, from, to, delta);
    values[root] = Op::join_value(values[2 * root + 1], values[2 * root + 2]);
  }

  T query(int root, int left, int right, int from, int to) {
    if (left > to || right < from) { return Op::neutral_value(); }
    if (left >= from && right <= to) { return values[root]; }
    int middle = (left + right) / 2;
    push_down(root, left, middle, right);
    T left_result = query(2 * root + 1, left, middle, from, to);
    T right_result = query(2 * root + 2, middle + 1, right, from, to);
    return Op::join_value(left_result, right_result);
  }

 private:
  std::vector<T> values;
  std::vector<T> deltas;

  void init_array(const std::vector<T>& arr, int root, int left, int right) {
    if (left == right) {
      values[root] = arr[left];
      deltas[root] = Op::neutral_delta();
    } else {
      int middle = (left + right) / 2;
      init_array(arr, 2 * root + 1, left, middle);
      init_array(arr, 2 * root + 2, middle + 1, right);
      values[root] = Op::join_value(values[2 * root + 1], values[2 * root + 2]);
      deltas[root] = Op::neutral_delta();
    }
  }

  void init_empty(int root, int left, int right) {
    if (left == right) {
      values[root] = Op::neutral_value();
      deltas[root] = Op::neutral_delta();
    } else {
      int middle = (left + right) / 2;
      init_empty(2 * root + 1, left, middle);
      init_empty(2 * root + 2, middle + 1, right);
      values[root] = Op::join_value(values[2 * root + 1], values[2 * root + 2]);
      deltas[root] = Op::neutral_delta();
    }
  }
};
