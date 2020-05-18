long long num_inversions(std::vector<int>& arr, int from, int to) {
  if (to - from < 2) { return 0; }
  int mid = (from + to) / 2;
  long long res = num_inversions(arr, from, mid) + num_inversions(arr, mid, to);
  int i = from, j = mid;
  std::vector<int> b;  // 可以预先分配内存
  while (i < mid && j < to) {
    if (arr[i] <= arr[j]) {
      b.push_back(arr[i++]);
    } else {
      b.push_back(arr[j++]);
      res += mid - i;
    }
  }
  while (i < mid) { b.push_back(arr[i++]); }
  while (j < to) { b.push_back(arr[j++]); }
  for (i = from; i < to; i++) { arr[i] = b[i - from]; }
  return res;
}
