std::vector<int> count_factors(int n) {
  std::vector<int> res(n + 1);
  for (int i = 1; i * i <= n; i++) {
    for (int j = i + 1; j * i <= n; j++) { res[i * j] += 2; }
    res[i * i]++;
  }
  return res;
}
