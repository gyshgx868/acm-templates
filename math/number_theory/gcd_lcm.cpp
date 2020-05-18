// non-recursive
template <class T>
T gcd(T m, T n) {
  if (n == T()) { return m; }
  while (n > T()) {
    T tmp = m % n;
    m = n;
    n = tmp;
  }
  return m;
}

// recursive
template <class T>
T gcd(T m, T n) { return n ? gcd(n, m % n) : m; }

template <class T>
T lcm(T m, T n) { return m * n / gcd(m, n); }
