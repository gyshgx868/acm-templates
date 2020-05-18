long long find_coprime(long long r, long long n) {
  long long res = 0;
  std::vector<int> f = get_factors(n);
  for (long long mask = 1; mask < 1LL << f.size(); mask++) {
    long long mult = 1;
    int bit = 0;
    for (int i = 0; i < f.size(); i++) {
      if (mask & (1LL << i)) {
        bit++;
        mult *= f[i];
      }
    }
    long long cur = r / mult;
    res += bit % 2 == 1 ? cur : -cur;
  }
  return r - res;
}
