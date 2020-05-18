std::vector<long long> get_bells(
    const std::vector<std::vector<long long> >& c, long long m) {
  int upto = c.size();
  std::vector<long long> bell(upto, 0);
  bell[0] = bell[1] = 1;
  for (int i = 2; i < upto; i++) {
    for (int j = 0; j <= i - 1; j++) {
      bell[i] = (bell[i] + c[i - 1][j] * bell[j] % m) % m;
    }
  }
  return bell;
}
