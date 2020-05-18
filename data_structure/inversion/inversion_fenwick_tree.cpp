long long num_inversions(const std::vector<int>& arr) {  // 0-indexed
  FenwickTree<int> tree(arr.size());
  std::vector<int> s = arr;
  std::sort(s.begin(), s.end());
  int pos = std::unique(s.begin(), s.end()) - s.begin();
  long long res = 0;
  for (int i = 0; i < arr.size(); i++) {
    int at = std::lower_bound(s.begin(), s.begin() + pos, arr[i]) - s.begin();
    tree.add(at, 1);
    res += i + 1 - tree.get(at);
  }
  return res;
}
