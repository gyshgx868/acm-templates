class BigInteger {
 public:
  explicit BigInteger(bool neg = false) : negative(neg) {}

  explicit BigInteger(const std::string& s) {
    if (s.empty()) { return; }
    int start = s[0] == '-' || s[0] == '+';
    negative = s[0] == '-';
    int len = s.size();
    int first = (len - start) % digits;
    int val = 0;
    for (int i = start; i < first + start; i++) {
      val = val * 10 + s[i] - '0';
    }
    number.push_back(val);
    for (int i = first + start; i < len; i += digits) {
      val = 0;
      for (int j = i; j < i + digits; j++) {
        val = val * 10 + (s[j] - '0');
      }
      number.push_back(val);
    }
    std::reverse(number.begin(), number.end());
    strip_leading_zeros();
  }

  template <
      class T, class = typename std::enable_if<std::is_integral<T>::value>::type
  >
  BigInteger(T x) {
    negative = x < T();
    x = abs(x);
    do {
      number.push_back(x % multiplier);
      x /= multiplier;
    } while (x > T());
  }

  friend std::istream& operator >>(std::istream& in, BigInteger& a) {
    std::string s;
    in >> s;
    a = BigInteger(s);
    return in;
  }

  friend std::ostream& operator <<(std::ostream& out, const BigInteger& a) {
    if (a.negative && !a.is_zero()) { out << '-'; }
    out << (a.length() == 0 ? 0 : a.number.back());
    int len = a.length() - 2;
    for (int i = len; i >= 0; i--) {
      out << std::setw(digits) << std::setfill('0') << a.number[i];
    }
    return out;
  }

  BigInteger& operator =(const BigInteger& a) {
    number = a.number;
    negative = a.negative;
    return *this;
  }

  friend bool operator <(const BigInteger& lhs, const BigInteger& rhs) {
    if (lhs.negative && !rhs.negative) {
      return true;
    } else if (!lhs.negative && rhs.negative) {
      return false;
    } else if (lhs.negative) {
      return compare_less(rhs, lhs);
    } else {
      return compare_less(lhs, rhs);
    }
  }

  template <typename T>
  friend bool operator <(const BigInteger& lhs, T rhs) {
    return lhs < BigInteger(rhs);
  }

  friend bool operator >(const BigInteger& lhs, const BigInteger& rhs) {
    return rhs < lhs;
  }

  template <typename T>
  friend bool operator >(const BigInteger& lhs, T rhs) {
    return BigInteger(rhs) < lhs;
  }

  friend bool operator ==(const BigInteger& lhs, const BigInteger& rhs) {
    return !(lhs < rhs) && !(rhs < lhs);
  }

  friend bool operator !=(const BigInteger& lhs, const BigInteger& rhs) {
    return !(lhs == rhs);
  }

  template <typename T>
  friend bool operator ==(const BigInteger& lhs, T rhs) {
    BigInteger t(rhs);
    return !(lhs < t) && !(t < lhs);
  }

  template <typename T>
  friend bool operator <=(const BigInteger& lhs, T rhs) {
    return lhs < rhs || lhs == rhs;
  }

  template <typename T>
  friend bool operator >=(const BigInteger& lhs, T rhs) {
    return rhs < lhs || rhs == lhs;
  }

  BigInteger operator +(const BigInteger& rhs) const {
    if (negative == rhs.negative) {
      return inner_add(*this, rhs, negative);
    }
    if (compare_less(*this, rhs)) {
      return inner_minus(rhs, *this, !negative);
    }
    return inner_minus(*this, rhs, negative);
  }

  template <typename T>
  BigInteger operator +(T rhs) const { return *this + BigInteger(rhs); }

  BigInteger operator ++(int) {
    BigInteger t = *this;
    *this = *this + 1;
    return t;
  }

  BigInteger& operator ++() { return *this = *this + 1; }

  BigInteger& operator +=(const BigInteger& rhs) {
    return *this = *this + rhs;
  }

  template <typename T>
  BigInteger& operator +=(T rhs) { return *this = *this + BigInteger(rhs); }

  BigInteger operator -(const BigInteger& rhs) const {
    if (negative != rhs.negative) {
      return inner_add(*this, rhs, negative);
    }
    if (compare_less(*this, rhs)) {
      return inner_minus(rhs, *this, !negative);
    }
    return inner_minus(*this, rhs, negative);
  }

  template <typename T>
  BigInteger operator -(T rhs) const { return *this - BigInteger(rhs); }

  BigInteger operator --(int) {
    BigInteger t = *this;
    *this = *this - 1;
    return t;
  }

  BigInteger& operator --() { return *this = *this - 1; }

  BigInteger& operator -=(const BigInteger& rhs) {
    return *this = *this - rhs;
  }

  template <typename T>
  BigInteger& operator -=(T rhs) { return *this = *this - BigInteger(rhs); }

  BigInteger operator *(const BigInteger& rhs) const {
    return inner_times(*this, rhs, negative != rhs.negative);
  }

  template <typename T>
  BigInteger operator *(T rhs) const { return *this * BigInteger(rhs); }

  BigInteger& operator *=(const BigInteger& rhs) {
    return *this = *this * rhs;
  }

  template <typename T>
  BigInteger& operator *=(T rhs) { return *this = *this * BigInteger(rhs); }

  BigInteger operator /(const BigInteger& rhs) const {
    return inner_div_mod(*this, rhs).first;
  }

  template <typename T>
  BigInteger operator /(T x) const {
    BigInteger res(negative != (x < T()));
    x = abs(x);
    long long cur = 0LL;
    for (int i = length() - 1; i >= 0; i--) {
      cur = cur * multiplier + number[i];
      res.number.insert(res.number.begin(), cur / x);
      cur %= x;
    }
    res.strip_leading_zeros();
    return res;
  }

  BigInteger& operator /=(const BigInteger& x) { return *this = *this / x; }

  template <typename T>
  BigInteger& operator /=(T x) { return *this = *this / x; }

  BigInteger operator %(const BigInteger& x) const {
    return inner_div_mod(*this, x).second;
  }

  template <typename T>
  T operator %(T x) const {
    T res = T();
    for (int i = length() - 1; i >= 0; i--) {
      res = (res * (multiplier % x) + number[i] % x) % x;
    }
    return res;
  }

  BigInteger& operator %=(const BigInteger& x) { return *this = *this % x; }

  template <typename T>
  BigInteger& operator %=(T x) { return *this = *this % x; }

  friend BigInteger power(const BigInteger& a, const BigInteger& x) {
    if (x == 0 || a == 1) { return 1; }
    BigInteger tmp = power(a, x / 2);
    if (x % 2 == 0) { return tmp * tmp; }
    return tmp * tmp * a;
  }

  template <typename T>
  friend BigInteger power(const BigInteger& a, T x) {
    return power(a, BigInteger(x));
  }

  friend BigInteger gcd(BigInteger a, BigInteger b) {
    while (b > 0) {
      BigInteger r = a % b;
      a = b;
      b = r;
    }
    a.strip_leading_zeros();
    return a;
  }

  friend BigInteger lcm(const BigInteger& a, const BigInteger& b) {
    return a * b / gcd(a, b);
  }

  friend BigInteger sqrt(const BigInteger& x) {
    BigInteger res = x;
    while (x < res * res) { res = (x / res + res) / 2; }
    return res;
  }

  friend BigInteger root(const BigInteger& base, int m) {
    if (m == 1 || base == 0) { return base; }
    int step = (base.length() + m - 1) / m - 1;
    BigInteger res(std::min(base, BigInteger(multiplier - 1).move(step)));
    int top = res.length() - 1;
    int left = 0, right = multiplier - 1;
    while (left < right) {
      int mid = (left + right) / 2;
      res.number[top] = mid;
      if (power(res, m) <= base) {
        left = mid + 1;
      } else {
        right = mid;
      }
    }
    res.number[top] = left;
    res.strip_leading_zeros();
    BigInteger next = (res * (m - 1) + base / power(res, m - 1)) / m;
    while (next < res) {
      std::swap(res, next);
      next = (res * (m - 1) + base / power(res, m - 1)) / m;
    }
    return res;
  }

  friend BigInteger abs(const BigInteger& x) {
    BigInteger res = x;
    res.negative = false;
    return res;
  }

 private:
  std::vector<int> number;
  bool negative;
  static const int digits = 9;
  static const int multiplier = 1000000000;

  int length() const { return number.size(); }

  bool is_zero() const {
    return number.empty() || (number.size() == 1 && number[0] == 0);
  }

  void strip_leading_zeros() {
    while (number.size() > 1 && number.back() == 0) { number.pop_back(); }
  }

  BigInteger move(int k) const {
    if (k == 0) { return *this; }
    if (k < 0) {
      if (-k >= (int) number.size()) { return BigInteger(1); }
      BigInteger res;
      res.number = std::vector<int>(number.begin() + (-k), number.end());
      return res;
    }
    if (number.size() == 1 && number[0] == 0) { return BigInteger(1); }
    BigInteger res;
    res.number.resize(k, 0);
    res.number.insert(res.number.end(), number.begin(), number.end());
    return res;
  }

  static bool compare_less(const BigInteger& lhs, const BigInteger& rhs) {
    if (lhs.length() != rhs.length()) { return lhs.length() < rhs.length(); }
    return std::lexicographical_compare(
        lhs.number.rbegin(), lhs.number.rend(),
        rhs.number.rbegin(), rhs.number.rend());
  }

  static BigInteger inner_add(
      const BigInteger& lhs, const BigInteger& rhs, bool neg) {
    BigInteger res(neg);
    int carry = 0;
    int len = std::max(lhs.length(), rhs.length());
    for (int i = 0; i < len; i++) {
      if (i < lhs.length()) { carry += lhs.number[i]; }
      if (i < rhs.length()) { carry += rhs.number[i]; }
      res.number.push_back(carry % multiplier);
      carry /= multiplier;
    }
    if (carry != 0) { res.number.push_back(carry); }
    res.strip_leading_zeros();
    return res;
  }

  static BigInteger inner_minus(
      const BigInteger& lhs, const BigInteger& rhs, bool neg) {
    // lhs >= rhs
    BigInteger res(neg);
    int carry = 0, len = lhs.length();
    for (int i = 0; i < len; i++) {
      carry += lhs.number[i] - (i < rhs.length() ? rhs.number[i] : 0);
      if (carry < 0) {
        res.number.push_back(carry + multiplier);
        carry = -1;
      } else {
        res.number.push_back(carry);
        carry = 0;
      }
    }
    res.strip_leading_zeros();
    return res;
  }

  static BigInteger inner_times(
      const BigInteger& lhs, const BigInteger& rhs, bool neg) {
    BigInteger res(neg);
    int xlen = rhs.length(), ylen = lhs.length();
    res.number.resize(xlen + ylen, 0);
    for (int i = 0; i < xlen; i++) {
      long long carry = 0LL;
      for (int j = 0; j < ylen || carry > 0; j++) {
        long long l = j < lhs.length() ? (long long) lhs.number[j] : 0LL;
        long long s = res.number[i + j] + carry + rhs.number[i] * l;
        res.number[i + j] = (int) (s % multiplier);
        carry = s / multiplier;
      }
    }
    res.strip_leading_zeros();
    return res;
  }

  static std::pair<BigInteger, BigInteger> inner_div_mod(
      const BigInteger& lhs, const BigInteger& rhs) {
    int norm = multiplier / (rhs.number.back() + 1);
    BigInteger a = abs(lhs) * norm;
    BigInteger b = abs(rhs) * norm;
    BigInteger q, r;
    q.number.resize(a.length());
    for (int i = a.length() - 1; i >= 0; i--) {
      r *= multiplier;
      r += a.number[i];
      int s1 = b.length() < r.length() ? r.number[b.length()] : 0;
      int s2 = b.length() - 1 < r.length() ? r.number[b.length() - 1] : 0;
      int d = (int) (((long long) s1 * multiplier + s2) / b.number.back());
      r -= b * d;
      while (r < 0) {
        r += b;
        --d;
      }
      q.number[i] = d;
    }
    q.negative = lhs.negative != rhs.negative;
    r.negative = lhs.negative;
    q.strip_leading_zeros();
    r.strip_leading_zeros();
    return std::make_pair(q, r / norm);
  }
};
