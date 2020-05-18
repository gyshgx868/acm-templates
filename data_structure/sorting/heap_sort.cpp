template <class T>
void sift_down(std::vector<T>& arr, int at, int m) {
  int i = at, j = 2 * i + 1;
  T temp = arr[i];
  while (j <= m) {
    if (j < m && arr[j] < arr[j + 1]) { j++; }
    if (temp >= arr[j]) {
      break;
    } else {
      arr[i] = arr[j];
      i = j;
      j = 2 * j + 1;
    }
  }
  arr[i] = temp;
}

// 区间为 [left, right]
template <class T>
void heap_sort(std::vector<T>& arr, int from, int to) {
  int n = to - from + 1;
  for (int i = (n - 2) / 2; i >= 0; i--) { sift_down(arr, i, n - 1); }
  for (int i = n - 1; i >= 0; i--) {
    std::swap(arr[0], arr[i]);
    sift_down(arr, 0, i - 1);
  }
}
