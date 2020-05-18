template <class T>
class FenwickTree3D {
 private:
  std::vector<std::vector<std::vector<T> > > value;

 public:
  explicit FenwickTree3D(int x, int y, int z) {
    value.resize(x, std::vector<T>(y, std::vector<T>(z, T())));
  }

  void add(int x, int y, int z, T delta) {
    for (int i = x; i < value.size(); i |= i + 1) {
      for (int j = y; j < value[0].size(); j |= j + 1) {
        for (int k = z; k < value[0][0].size(); k |= k + 1) {
          value[i][j][k] += delta;
        }
      }
    }
  }

  T sum(int x, int y, int z) {
    T res = T();
    for (int i = x; i >= 0; i = (i & (i + 1)) - 1) {
      for (int j = y; j >= 0; j = (j & (j + 1)) - 1) {
        for (int k = z; k >= 0; k = (k & (k + 1)) - 1) {
          res += value[i][j][k];
        }
      }
    }
    return res;
  }
};
