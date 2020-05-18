int upper_bound(int* a, int low, int high, int val) {
  while (low < high) {
    int mid = low + (high - low) / 2;
    /**
     * v == a[mid]: 答案肯定在后面, 因为不可能等于 v
     * v < a[mid]: mid 和后面都不可以
     * v > a[mid]: 应该在 mid 的后面
     */
    if (val < a[mid]) {
      high = mid;
    } else {
      low = mid + 1;
    }
  }
  return high;
}
