long long c(int n, int m, long long mod) {
  if (m > n) { return 0; }
  if (m > n - m) { m = n - m; }
  long long a = 1, b = 1;
  for (int i = 1; i <= m; i++) {
    a = quick_mul(a, n + i - m, mod);
    b = quick_mul(b, i, mod);
  }
  return quick_mul(a, quick_pow(b, mod - 2, mod), mod);
}
