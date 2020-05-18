template <class T>
T knapsack(
    const std::vector<int>& weight, const std::vector<T>& value,
    const std::vector<int>& count, int capacity) {
  int n = weight.size();
  std::vector<T> f(capacity + 1, T());
  for (int i = 0; i < n; i++) {
    // 如果物品够多, 问题实际上就是完全背包问题
    if (weight[i] * count[i] > capacity) {
      for (int j = weight[i]; j <= capacity; j++) {
        if (j >= weight[i]) {
          f[j] = std::max(f[j], f[j - weight[i]] + value[i]);
        }
      }
    } else {
      int k = 1, amount = count[i];
      while (k < amount) {
        // 是否取一个重量为 k * weight[i], 价值为 k * value[i] 的物品
        for (int j = k * weight[i]; j >= 0; j--) {
          f[j] = max(f[j], f[j - weight[i]] + k * value[i]);
        }
        amount -= k;
        k += k;
      }
      // 把剩下的作为单独一个物品
      for (int j = amount * weight[i]; j >= 0; j--) {
        f[j] = max(f[j], f[j - weight[i]] + amount * value[i]);
      }
    }
  }
  return f[capacity];
}
