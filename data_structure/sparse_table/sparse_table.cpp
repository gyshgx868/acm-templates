template <class T, class Op = Min>
class SparseTable {
 public:
  explicit SparseTable(const std::vector<T>& arr) {
    lookup.resize(arr.size(), std::vector<T>(std::log2(arr.size()) + 1));
    for (unsigned i = 0; i < arr.size(); i++) { lookup[i][0] = arr[i]; }
    for (unsigned j = 1; (1u << j) <= arr.size(); j++) {
      for (unsigned i = 0; i + (1u << j) - 1 < arr.size(); i++) {
        lookup[i][j] = op(lookup[i][j - 1], lookup[i + (1u << (j - 1))][j - 1]);
      }
    }
  }

  int query(int left, int right) const {
    unsigned j = std::log2(right - left + 1);
    return op(lookup[left][j], lookup[right - (1u << j) + 1][j]);
  }

 private:
  Op op;
  std::vector<std::vector<T> > lookup;
};
