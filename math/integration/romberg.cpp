class Romberg {
 public:
  explicit Romberg(std::function<double(double)> f) : func(std::move(f)) {}

  double integrate(double left, double right, double eps = 1e-6) const {
    double len = right - left;
    std::vector<double> terms;
    terms.push_back(len * (func(left) + func(right)) / 2);
    double last, cur;
    int k = 1, i = 1;
    do {
      last = terms.back();
      cur = 0;
      double x = left + len / 2;
      for (int j = 0; j < k; j++) {
        cur += func(x);
        x += len;
      }
      cur = (terms[0] + len * cur) / 2;
      double k1 = 4.0 / 3, k2 = 1.0 / 3;
      for (int j = 0; j < i; j++) {
        double temp = k1 * cur - k2 * terms[j];
        terms[j] = cur;
        cur = temp;
        k2 /= 4 * k1 - k2;
        k1 = k2 + 1;
      }
      terms.push_back(cur);
      k *= 2;
      len /= 2;
      i++;
    } while (fabs(last - cur) > eps);
    return terms.back();
  }

 private:
  std::function<double(double)> func;
};
