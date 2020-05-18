template <class T>
class FenwickTree {
 public:
  explicit FenwickTree(int size = 0) { value.resize(size + 1, T()); }

  void add(int from, int to, T delta) {
    add(from, delta);
    add(to + 1, -delta);
  }

  T get(int at) const {
    T res = T();
    for (at++; at > 0; at -= at & -at) { res += value[at]; }
    return res;
  }

 private:
  std::vector<T> value;

  void add(int at, T delta) {
    for (at++; at < value.size(); at += at & -at) { value[at] += delta; }
  }
};
