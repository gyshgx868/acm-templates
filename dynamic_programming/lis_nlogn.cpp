template <class T>
int get_lis(const std::vector<T>& seq) {
  int res = 1;
  std::vector<int> f(seq.size());
  f[1] = seq[0];
  for (int i = 1; i < seq.size(); i++) {
    // 若求解严格上升的子序列, 将 upper_bound 更换为 lower_bound 即可
    int pos = std::upper_bound(
        f.begin() + 1, f.begin() + res + 1, seq[i]) - f.begin();
    f[pos] = seq[i];
    res = std::max(res, pos);
  }
  return res;
}
