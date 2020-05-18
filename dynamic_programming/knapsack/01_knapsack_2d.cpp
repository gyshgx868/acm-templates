template <class T>
T knapsack(
    const std::vector<int>& weight, const std::vector<T>& value,
    int capacity) {
  int n = weight.size();
  std::vector<std::vector<T> > f(n + 1, std::vector<T>(capacity + 1, T()));
  for (int i = 0; i < n; i++) {
    for (int j = capacity; j >= 0; j--) {
      if (j < weight[i]) {
        f[i + 1][j] = f[i][j];
      } else {
        f[i + 1][j] = std::max(f[i][j], f[i][j - weight[i]] + value[i]);
      }
    }
  }
  return f[n][capacity];
}
