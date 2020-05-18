template <class T>
int min_representation(const std::vector<T>& arr) {
  int len = arr.size();
  int i = 0, j = 1, k;
  while (i < len && j < len) {
    for (k = 0; k < len; k++) {
      if (arr[(i + k) % len] != arr[(j + k) % len]) { break; }
    }
    if (k >= len) { break; }
    if (arr[(i + k) % len] > arr[(j + k) % len]) {
      if (i + k + 1 > j) {
        i = i + k + 1;
      } else {
        i = j + 1;
      }
    } else if (j + k + 1 > i) {
      j = j + k + 1;
    } else {
      j = i + 1;
    }
  }
  return std::min(i, j);
}
