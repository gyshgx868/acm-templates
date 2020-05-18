template <class T>
T knapsack(
    const std::vector<int>& weight, const std::vector<int>& cost,
    const std::vector<T>& value, int capacity, int remain) {
  int n = weight.size();
  std::vector<std::vector<T> > f(capacity + 1, std::vector<T>(remain + 1, T()));
  for (int i = 0; i < n; i++) {
    for (int j = capacity; j >= weight[i]; j--) {
      for (int k = remain; k >= cost[i]; k--) {
        f[j][k] = std::max(f[j][k], f[j - weight[i]][k - cost[i]] + value[i]);
      }
    }
  }
  return f[capacity][remain];
}
