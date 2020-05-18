std::vector<std::vector<long long> > get_combinations(int upto, long long m) {
  std::vector<std::vector<long long> > res(upto);
  for (int i = 0; i < upto; i++) {
    res[i].resize(upto, 1);
    for (int j = 1; j < i; j++) {
      res[i][j] = (res[i - 1][j] + res[i - 1][j - 1]) % m;
    }
  }
  return res;
}
