template <class T>
T knapsack(
    const std::vector<int>& weight, const std::vector<T>& value,
    int capacity) {
  std::vector<T> f(capacity + 1, T());
  for (int i = 0; i < weight.size(); i++) {
    for (int j = capacity; j >= weight[i]; j--) {
      f[j] = std::max(f[j], f[j - weight[i]] + value[i]);
    }
  }
  return f[capacity];
}
