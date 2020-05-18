class Lehmer {
 public:
  explicit Lehmer(int upto = 5000005, int num_primes = 7) {
    sieve_euler(upto);
    int p = 1;
    for (int i = 0; i < num_primes; i++) {
      p *= primes[i];
    }
    product.resize(num_primes + 1);
    phi.resize(p + 1, std::vector<int>(num_primes + 1));
    for (int i = 0; i <= p; i++) {
      phi[i][0] = i;
    }
    product[0] = 1;
    for (int i = 1; i <= num_primes; i++) {
      product[i] = primes[i - 1] * product[i - 1];
      for (int j = 1; j <= p; ++j) {
        phi[j][i] = phi[j][i - 1] - phi[j / primes[i - 1]][i - 1];
      }
    }
  }

  long long count(long long x) {
    if (x < pi.size()) {
      return pi[x];
    }
    int a = (int) count(isqrt(isqrt(x)));
    int b = (int) count(isqrt(x));
    int c = (int) count(icbrt(x));
    long long sum = get_phi(x, a) + 1LL * (b + a - 2) * (b - a + 1) / 2;
    for (int i = a + 1; i <= b; i++) {
      long long w = x / primes[i - 1];
      sum -= count(w);
      if (i > c) {
        continue;
      }
      long long lim = count(isqrt(w));
      for (int j = i; j <= lim; j++) {
        sum -= count(w / primes[j - 1]) - (j - 1);
      }
    }
    return sum;
  }

 private:
  std::vector<int> primes;
  std::vector<int> pi;
  std::vector<int> product;
  std::vector<std::vector<int> > phi;

  void sieve_euler(int upto) {
    pi.resize(upto);
    std::vector<int> is_not_prime(upto, 0);
    is_not_prime[0] = is_not_prime[1] = 1;
    pi[0] = pi[1] = 0;
    for (int i = 2; i < upto; i++) {
      if (!is_not_prime[i]) {
        primes.push_back(i);
      }
      int count = primes.size();
      pi[i] = count;
      for (int j = 0; j < count && i * primes[j] < upto; j++) {
        is_not_prime[i * primes[j]] = 1;
        if (i % primes[j] == 0) {
          break;
        }
      }
    }
  }

  inline int isqrt(long long x) {
    long long r = (long long) sqrt(x - 0.1);
    while (r * r <= x) { r++; }
    return (int) (r - 1);
  }

  inline int icbrt(long long x) {
    long long r = (long long) cbrt(x - 0.1);
    while (r * r * r <= x) { r++; }
    return (int) (r - 1);
  }

  long long get_phi(long long x, int s) {
    if (s == 0) { return x; }
    if (s < product.size()) {
      return phi[x % product[s]][s] + (x / product[s]) * phi[product[s]][s];
    }
    if (x <= primes[s - 1] * primes[s - 1]) {
      return pi[x] - s + 1;
    }
    if (x <= primes[s - 1] * primes[s - 1] * primes[s - 1] && x < pi.size()) {
      int s2x = pi[isqrt(x)];
      long long res = pi[x] - (s2x + s - 2) * (s2x - s + 1) / 2;
      for (int i = s + 1; i <= s2x; i++) {
        res += pi[x / primes[i - 1]];
      }
      return res;
    }
    return get_phi(x, s - 1) - get_phi(x / primes[s - 1], s - 1);
  }

  long long get_pi(long long x) {
    if (x < pi.size()) { return pi[x]; }
    long long res = get_phi(x, pi[icbrt(x)]) + pi[icbrt(x)] - 1;
    for (int i = pi[icbrt(x)] + 1, ed = pi[isqrt(x)]; i <= ed; i++) {
      res -= get_pi(x / primes[i - 1]) - i + 1;
    }
    return res;
  }
} alg;
