template <class T>
class FenwickTree {
 public:
  explicit FenwickTree(int size = 0) {
    if (size > 0) { initialize(size); }
  }

  void initialize(int size) { value.resize(size, T()); }

  // [from, to]
  T get(int from, int to) const { return get(to) - get(from - 1); }

  T get(int to) const {
    to = std::min(to, (int) value.size() - 1);
    T res = T();
    while (to >= 0) {
      res += value[to];
      to = (to & (to + 1)) - 1;
    }
    return res;
  }

  void add(int at, T delta) {
    while (at < value.size()) {
      value[at] += delta;
      at = at | (at + 1);
    }
  }

 private:
  std::vector<T> value;
};
