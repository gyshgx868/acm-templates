int crt(const std::vector<int>& a, const std::vector<int>& m) {
  int n = a.size();
  int mod = 1;
  for (int i = 0; i < n; i++) { mod *= m[i]; }
  int res = 0;
  for (int i = 0; i < n; i++) {
    int tm = mod / m[i];
    int x, y;
    extended_gcd(tm, m[i], x, y);
    res = (res + tm * x * a[i]) % mod;
  }
  return (res + mod) % mod;
}
