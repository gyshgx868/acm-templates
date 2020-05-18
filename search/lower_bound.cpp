int lower_bound(int* a, int low, int high, int val) {
  while (low < high) {
    int mid = low + (high - low) / 2;
    /**
     * v == a[mid]: 至少找到一个等于 v 的, 但前面可能还有
     * v < a[mid]: v 肯定不能在 mid 的后面
     * v > a[mid]: mid 和前面都不可以
     */
    if (val <= a[mid]) {
      high = mid;
    } else {
      low = mid + 1;
    }
  }
  return low;
}
