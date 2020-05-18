template <class T>
class SumSparseTable {
 public:
  explicit SumSparseTable(const std::vector<T>& arr) {
    lookup.resize(arr.size(), std::vector<T>(std::log2(arr.size()) + 1));
    for (unsigned i = 0; i < arr.size(); i++) { lookup[i][0] = arr[i]; }
    for (unsigned j = 1; j < lookup[0].size(); j++) {
      for (unsigned i = 0; i + (1u << j) <= arr.size(); i++) {
        lookup[i][j] = lookup[i][j - 1] + lookup[i + (1u << (j - 1))][j - 1];
      }
    }
  }

  T query(int left, int right) {
    T res = 0;
    for (int j = lookup[0].size() - 1; j >= 0; j--) {
      if (left + (1 << j) - 1 <= right) {
        res = res + lookup[left][j];
        left += 1 << j;
      }
    }
    return res;
  }

 private:
  std::vector<std::vector<T> > lookup;
};
