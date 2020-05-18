long long pollard_rho(long long x, long long c) {
  long long i = 1, k = 2;
  long long x0 = rand() % x;
  long long y = x0;
  while (true) {
    i++;
    x0 = (quick_mul(x0, x0, x) + c) % x;
    long long d = gcd(y - x0 + x, x);
    if (d != 1 && d != x) { return d; }
    if (y == x0) { return x; }
    if (i == k) {
      y = x0;
      k += k;
    }
  }
}

void get_factors(long long n, std::vector<long long>& fac) {
  if (miller_rabin(n)) {
    fac.push_back(n);
    return;
  }
  long long p = n;
  while (p >= n) { p = pollard_rho(p, rand() % (n - 1) + 1); }
  get_factors(p, fac);
  get_factors(n / p, fac);
}
