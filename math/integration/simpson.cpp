class Simpson {
 public:
  explicit Simpson(std::function<double(double)> f) : func(std::move(f)) {}

  double integrate(double left, double right, double eps = 1e-6) const {
    return asr(left, right, eps, simpson(left, right));
  }

 private:
  std::function<double(double)> func;

  double simpson(double left, double right) const {
    double mid = left + (right - left) / 2;
    return (func(left) + 4 * func(mid) + func(right)) * (right - left) / 6;
  }

  double asr(double left, double right, double eps, double s) const {
    double mid = left + (right - left) / 2;
    double from = simpson(left, mid), to = simpson(mid, right);
    if (fabs(from + to - s) <= 15 * eps) {
      return from + to + (from + to - s) / 15;
    }
    return asr(left, mid, eps / 2, from) + asr(mid, right, eps / 2, to);
  }
};
