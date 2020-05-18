template <class T>
class FenwickTree2D {
 public:
  explicit FenwickTree2D(int rows, int columns) {
    value.resize(rows, std::vector<T>(columns, T()));
  }

  void add(int row, int column, T delta) {
    for (int i = row; i < value.size(); i |= i + 1) {
      for (int j = column; j < value[0].size(); j |= j + 1) {
        value[i][j] += delta;
      }
    }
  }

  T sum(int row, int column) {
    T res = T();
    for (int i = row; i >= 0; i = (i & (i + 1)) - 1) {
      for (int j = column; j >= 0; j = (j & (j + 1)) - 1) {
        res += value[i][j];
      }
    }
    return res;
  }

  T sum(int fromRow, int fromColumn, int toRow, int toColumn) {
    return sum(toRow, toColumn) - sum(fromRow - 1, toColumn) -
        sum(toRow, fromColumn - 1) + sum(fromRow - 1, fromColumn - 1);
  }

  T get(int row, int column) {
    return sum(row, column, row, column);
  }

  void set(int row, int column, T val) {
    add(row, column, -get(row, column) + val);
  }

 private:
  std::vector<std::vector<T> > value;
};
