long long lucas(int n, int m, long long mod) {
  if (m == 0) { return 1; }
  return (lucas(n / mod, m / mod, mod) * c(n % mod, m % mod, mod)) % mod;
}
