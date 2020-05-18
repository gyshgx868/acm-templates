template <class T>
T extended_gcd(T a, T b, T& x, T& y) {
  if (b == T()) {
    x = 1;
    y = T();
    return a;
  }
  T res = extended_gcd(b, a % b, x, y);
  T temp = x;
  x = y;
  y = temp - (a / b) * y;
  return res;
}
