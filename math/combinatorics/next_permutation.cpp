// 如果已经是最后一个序列则返回 false
bool next_permutation(std::vector<int>& arr) {
  int j = (int) arr.size() - 2;
  while (j >= 0 && arr[j] >= arr[j + 1]) { j--; }
  if (j >= 0) {
    int k = (int) arr.size() - 1;
    while (arr[k] <= arr[j]) { k--; }
    std::swap(arr[j], arr[k]);
    for (int p = j + 1, q = (int) arr.size() - 1; p < q; p++, q--) {
      std::swap(arr[p], arr[q]);
    }
  }
  return j >= 0;
}
