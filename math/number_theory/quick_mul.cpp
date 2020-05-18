long long quick_mul(long long a, long long b, long long m) {
  a %= m;
  b %= m;
  long long res = 0;
  while (b != 0) {
    if (b & 1) {
      res += a;
      res %= m;
    }
    a <<= 1;
    if (a >= m) { a %= m; }
    b >>= 1;
  }
  return res;
}

long long quick_mul(long long a, long long b, long long m) {
  return (a * b - (long long) (a / (long double) m * b + 1e-3) * m + m) % m;
}
