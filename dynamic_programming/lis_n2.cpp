template <class T>
int get_lis(const std::vector<T>& seq) {
  int res = 1;
  std::vector<int> f(seq.size(), 1);
  for (int i = 1; i < seq.size(); i++) {
    for (int j = 0; j < i; j++) {
      // 如果要求非递减子序列只需将 seq[j] < seq[i] 改成 <=
      // 如果要求递减子序列只需改为 >
      if (seq[j] < seq[i] && f[i] < f[j] + 1) {
        f[i] = f[j] + 1;
        res = std::max(f[i], res);
      }
    }
  }
  return res;
}
