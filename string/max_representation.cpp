template <class T>
int max_representation(const std::vector<T>& arr) {
  int len = arr.size();
  int i = 0, j = 1, k = 0;
  while (i < len && j < len && k < len) {
    int t = arr[(i + k) % len] - arr[(j + k) % len];
    if (t == 0) {
      k++;
    } else {
      if (t > 0) {
        if (j + k + 1 > i) {
          j = j + k + 1;
        } else {
          j = i + 1;
        }
      } else if (i + k + 1 > j) {
        i = i + k + 1;
      } else {
        i = j + 1;
      }
      k = 0;
    }
  }
  return std::min(i, j);
}
