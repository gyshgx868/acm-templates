class Rational {
 public:
  explicit Rational(long long num = 1, long long den = 1) {
    this->num = num;
    this->den = den;
    format();
  }

  Rational operator +(const Rational& rhs) const {
    return Rational(num * rhs.den + den * rhs.num, den * rhs.den);
  }

  Rational operator -(const Rational& rhs) const {
    return Rational(num * rhs.den - den * rhs.num, den * rhs.den);
  }

  Rational operator *(const Rational& rhs) const {
    return Rational(num * rhs.num, den * rhs.den);
  }

  Rational operator /(const Rational& rhs) const {
    return Rational(num * rhs.den, den * rhs.num);
  }

  Rational& operator +=(const Rational& rhs) {
    *this = *this + rhs;
    return *this;
  }

  Rational& operator -=(const Rational& rhs) {
    *this = *this - rhs;
    return *this;
  }

  Rational& operator *=(const Rational& rhs) {
    *this = *this * rhs;
    return *this;
  }

  Rational& operator /=(const Rational& rhs) {
    *this = *this / rhs;
    return *this;
  }

  Rational& operator =(const Rational& rhs) {
    this->num = rhs.num;
    this->den = rhs.den;
    return *this;
  }

  bool operator <(const Rational& rhs) const {
    return num * rhs.den < den * rhs.num;
  }

  bool operator >(const Rational& rhs) const { return rhs < *this; }

  bool operator <=(const Rational& rhs) const { return !(rhs < *this); }

  bool operator >=(const Rational& rhs) const { return !(*this < rhs); }

  bool operator ==(const Rational& rhs) const {
    return num * rhs.den == den * rhs.num;
  }

  bool operator !=(const Rational& rhs) const { return !(rhs == *this); }

  long long numerator() const { return num; }

  long long denominator() const { return den; }

  double value() const { return (double) num / den; }

  friend std::ostream& operator <<(std::ostream& os, const Rational& x) {
    if (abs(x.num) % x.den == 0) {
      os << x.num / x.den;
    } else {
      os << x.num << '/' << x.den;
    }
    return os;
  }

 private:
  long long num;
  long long den;

  void format() {
    if (den < 0) {
      num = -num;
      den = -den;
    }
    long long g = gcd(abs(num), den);
    num /= g;
    den /= g;
  }
};
