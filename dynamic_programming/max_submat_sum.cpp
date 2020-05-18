template <class T>
T get_sum(const std::vector<std::vector<T> >& mat) {
  int n = mat.size(), m = mat[0].size();
  std::vector<std::vector<T> > f(n + 1, std::vector<T>(m + 1, T()));
  T res = 0;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= m; j++) {
      f[i][j] += mat[i - 1][j - 1] + f[i - 1][j];
    }
    for (int j = 1; j <= i; j++) {
      T cur_sum = T();
      for (int k = 1; k <= m; k++) {
        if (cur_sum < T()) {
          cur_sum = f[i][k] - f[j - 1][k];
        } else {
          cur_sum += f[i][k] - f[j - 1][k];
        }
        res = std::max(res, cur_sum);
      }
    }
  }
  return res;
}
