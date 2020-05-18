inline double f(double x) {
  // 函数体
}

double simpson(double a, double b) {
  double c = a + (b - a) / 2;
  return (f(a) + 4 * f(c) + f(b)) * (b - a) / 6;
}

double asr(double a, double b, double eps, double A) {
  double c = a + (b - a) / 2;
  double l = simpson(a, c), r = simpson(c, b);
  if (fabs(l + r - A) <= 15 * eps) { return l + r + (l + r - A) / 15; }
  return asr(a, c, eps / 2, l) + asr(c, b, eps / 2, r);
}

double integrate(double l, double r, double eps) {
  return asr(l, r, eps, simpson(l, r));
}
