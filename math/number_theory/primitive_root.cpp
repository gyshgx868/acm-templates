class PrimitiveRoot {
 public:
  explicit PrimitiveRoot(int upto) {
    primes = sieve_euler(upto);
  }

  bool has_primitive_root(int n) {
    if (n % 2 == 0) { n /= 2; }
    if (n % 2 == 0) { return false; }
    for (int i = 1; primes[i] * primes[i] <= n; i++) {
      if (n % primes[i] == 0) {
        while (n % primes[i] == 0) { n /= primes[i]; }
        return n == 1;
      }
    }
    return true;
  }

  int get_smallest(int n, int phi_n = 0) {
    if (phi_n < 1) { phi_n = euler(n); }
    std::vector<int> factors = get_factors(phi_n);
    int res = 1;
    while (true) {
      if (quick_pow(res, phi_n, n) != 1) {
        res++;
        continue;
      }
      if (test_root(res, n, phi_n, factors)) { return res; }
      res++;
    }
  }

  std::vector<int> get_all(int n) {
    std::vector<int> res;
    int phi_n = euler(n);
    int smallest = get_smallest(n);
    res.push_back(smallest);
    for (int i = 2; i < phi_n; i++) {
      if (gcd(i, phi_n) != 1) { continue; }
      res.push_back(quick_pow(smallest, i, n));
    }
    return res;
  }

 private:
  std::vector<int> primes;

  bool test_root(int g, int p, int phi_n, const std::vector<int>& factors) {
    for (int i = 0; i < factors.size(); i++) {
      if (quick_pow(g, phi_n / factors[i], p) == 1) { return false; }
    }
    return true;
  }
} pr(1000001);
