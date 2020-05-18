template <class T, class U = T>
T quick_pow(T x, U n, T m) {
  if (n == U() || x == 1) { return 1 % m; }
  T res = 1;
  while (n > U()) {
    if (n & 1) { res = res * x % m; }
    x = x * x % m;
    n >>= 1;
  }
  return res % m;
}
