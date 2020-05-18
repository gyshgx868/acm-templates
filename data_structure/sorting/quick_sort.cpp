template <class T>
int partition(std::vector<T>& arr, int from, int to) {
  T pivot = arr[to];
  int i = from - 1;
  for (int j = from; j <= to - 1; j++) {
    if (arr[j] < pivot) { std::swap(arr[++i], arr[j]); }
  }
  std::swap(arr[i + 1], arr[to]);
  return i + 1;
}

// 区间为 [left, right]
template <class T>
void quick_sort(std::vector<T>& arr, int from, int to) {
  if (from >= to) { return; }
  int mid = partition(arr, from, to);
  quick_sort(arr, from, mid - 1);
  quick_sort(arr, mid + 1, to);
}
