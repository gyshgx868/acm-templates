template <class T>
class Zn {
  typedef typename std::decay<decltype(T::value)>::type value_type;

 public:
  Zn() : value() {}

  Zn(const Zn& x) : value(x.value) {}

  template <class U>
  Zn(const U& x) { value = value_of(x); }

  template <class U>
  static value_type value_of(const U& x) {
    value_type res;
    if (-mod() <= x && x < mod()) {
      res = static_cast<value_type>(x);
    } else {
      res = static_cast<value_type>(x % mod());
    }
    if (res < value_type()) { res += mod(); }
    return res;
  }

  static value_type mod() { return T::value; }

  template <class U>
  explicit operator U() const { return static_cast<U>(value); }

  Zn& operator +=(const Zn& rhs) {
    value += rhs.value;
    if (value >= mod()) { value -= mod(); }
    return *this;
  }

  Zn& operator -=(const Zn& rhs) {
    value -= rhs.value;
    if (value < value_type()) { value += mod(); }
    return *this;
  }

  Zn& operator ++() { return *this += 1; }

  Zn& operator --() { return *this -= 1; }

  Zn operator ++(int) {
    Zn res(*this);
    *this += 1;
    return res;
  }

  Zn operator --(int) {
    Zn res(*this);
    *this -= 1;
    return res;
  }

  Zn operator -() const { return Zn(-value); }

  Zn& operator *=(const Zn& rhs) {
    value = value_of(value * rhs.value);
    return *this;
  }

  Zn& operator /=(const Zn& rhs) {
    return *this *= Zn(get_inv(rhs.value, mod()));
  }

  bool operator ==(const Zn& rhs) const { return value == rhs.value; }

  bool operator !=(const Zn& rhs) const { return !(rhs == *this); }

  template <class U>
  friend bool operator ==(const Zn& lhs, const U& rhs) {
    return lhs == Zn<T>(rhs);
  }

  template <class U>
  friend bool operator ==(const U& lhs, const Zn& rhs) {
    return Zn<T>(lhs) == rhs;
  }

  template <class U>
  friend bool operator !=(const Zn& lhs, const U& rhs) {
    return !(lhs == rhs);
  }

  template <class U>
  friend bool operator !=(const U& lhs, const Zn& rhs) {
    return !(lhs == rhs);
  }

  bool operator <(const Zn& rhs) const { return value < rhs.value; }

  bool operator >(const Zn& rhs) const { return rhs < *this; }

  bool operator <=(const Zn& rhs) const { return !(rhs < *this); }

  bool operator >=(const Zn& rhs) const { return !(*this < rhs); }

  Zn operator +(const Zn& rhs) const { return Zn(*this) += rhs; }

  template <class U>
  friend Zn operator +(const Zn& lhs, const U& rhs) { return lhs + Zn(rhs); }

  template <class U>
  friend Zn operator +(const U& lhs, const Zn& rhs) { return Zn(lhs) + rhs; }

  Zn operator -(const Zn& rhs) const { return Zn(*this) -= rhs; }

  template <class U>
  friend Zn operator -(const Zn& lhs, const U& rhs) { return lhs - Zn(rhs); }

  template <class U>
  friend Zn operator -(const U& lhs, const Zn& rhs) { return Zn(lhs) - rhs; }

  Zn operator *(const Zn& rhs) const { return Zn(*this) *= rhs; }

  template <class U>
  friend Zn operator *(const Zn& lhs, const U& rhs) { return lhs * Zn(rhs); }

  template <class U>
  friend Zn operator *(const U& lhs, const Zn& rhs) { return Zn(lhs) * rhs; }

  Zn operator /(const Zn& rhs) const { return Zn(*this) /= rhs; }

  template <class U>
  friend Zn operator /(const Zn& lhs, const U& rhs) { return lhs / Zn(rhs); }

  template <class U>
  friend Zn operator /(const U& lhs, const Zn& rhs) { return Zn(lhs) / rhs; }

  friend std::ostream& operator <<(std::ostream& os, const Zn& x) {
    return os << x.value;
  }

  friend std::istream& operator >>(std::istream& is, Zn& x) {
    is >> x.value;
    x.value = Zn::value_of(x.value);
    return is;
  }

 private:
  value_type value;
};

typedef Zn<std::integral_constant<long long, 1000000007LL> > mint;
