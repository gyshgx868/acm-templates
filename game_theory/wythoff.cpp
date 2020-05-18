bool wythoff(int n, int m) {
  if (n > m) { std::swap(n, m); }
  int a = (int) ((m - n) * (1.0 + sqrt(5.0)) / 2.0);
  return a != n;
}
