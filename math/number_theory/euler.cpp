long long euler(long long n) {
  long long res = n;
  long long x = (long long) sqrt(n);
  for (long long i = 2; i <= x; i++) {
    if (n % i == 0) {
      while (n % i == 0) { n /= i; }
      res = res / i * (i - 1);
    }
  }
  if (n > 1) { res = res / n * (n - 1); }
  return res;
}
