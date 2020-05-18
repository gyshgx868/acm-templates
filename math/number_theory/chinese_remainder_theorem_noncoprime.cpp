int crt(const std::vector<int>& a, const std::vector<int>& m) {
  int n = m.size();
  if (n == 1) { return a[0] > m[0] ? m[0] : -1; }
  int last_a = a[0];
  int last_m = m[0];
  for (int i = 1; i < n; i++) {
    if (a[i] <= m[i]) { return -1; }
    int x, y;
    int d = extended_gcd(last_a, a[i], x, y);
    if ((m[i] - last_m) % d != 0) { return -1; }
    int t = a[i] / d;
    x = ((m[i] - last_m) / d * x % t + t) % t;
    last_m = x * last_a + last_m;
    last_a = last_a * a[i] / d;
    last_m = (last_m % last_a + last_a) % last_a;
  }
  return last_m;
}
