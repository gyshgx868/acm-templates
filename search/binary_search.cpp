// 左闭右开区间 [low, high)
int binary_search(int* a, int low, int high, int val) {
  while (low < high) {
    int mid = low + (high - low) / 2;
    if (val == a[mid]) {
      return mid;
    } else if (val < a[mid]) {
      high = mid;
    } else {
      low = mid + 1;
    }
  }
  return -1;
}
