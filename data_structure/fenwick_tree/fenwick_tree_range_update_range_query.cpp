template <class T>
class FenwickTree {
 public:
  explicit FenwickTree(int size = 0) {
    tree1.resize(size + 1, T());
    tree2.resize(size + 1, T());
  }

  void add(int from, int to, T delta) {
    add(tree1, from, delta);
    add(tree1, to + 1, -delta);
    add(tree2, from, delta * (from - 1));
    add(tree2, to + 1, -delta * to);
  }

  T get(int to) const { return get(tree1, to) * to - get(tree2, to); }

  T get(int from, int to) const { return get(to) - get(from - 1); }

 private:
  std::vector<T> tree1;
  std::vector<T> tree2;

  void add(std::vector<T>& value, int at, T delta) {
    for (at++; at < value.size(); at += at & -at) {
      value[at] += delta;
    }
  }

  T get(const std::vector<T>& value, int at) const {
    T res = T();
    for (at++; at > 0; at -= at & -at) { res += value[at]; }
    return res;
  }
};
