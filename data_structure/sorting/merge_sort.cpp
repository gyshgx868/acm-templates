template <class T>
void merge(std::vector<T>& arr, int from, int mid, int to) {
  int n1 = mid - from + 1, n2 = to - mid;
  std::vector<T> left(n1), right(n2);
  for (int i = 0; i < n1; i++) { left[i] = arr[from + i]; }
  for (int j = 0; j < n2; j++) { right[j] = arr[mid + 1 + j]; }
  int i = 0, j = 0, k = from;
  while (i < n1 && j < n2) {
    if (left[i] <= right[j]) {
      arr[k] = left[i++];
    } else {
      arr[k] = right[j++];
    }
    k++;
  }
  while (i < n1) { arr[k++] = left[i++]; }
  while (j < n2) { arr[k++] = right[j++]; }
}

// 区间为 [left, right]
template <class T>
void merge_sort(std::vector<T>& arr, int from, int to) {
  if (from >= to) { return; }
  int mid = from + (to - from) / 2;
  merge_sort(arr, from, mid);
  merge_sort(arr, mid + 1, to);
  merge(arr, from, mid, to);
}
