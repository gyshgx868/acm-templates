class PrimitiveRoot {
 public:
  explicit PrimitiveRoot(int upto) {
    primes = sieve_euler(upto);
    phi = get_euler(upto);
  }

  bool has_primitive_root(int n) const {
    if (n == 2 || n == 4) { return true; }
    if (n % 2 == 0) { n /= 2; }
    if (n % 2 == 0) { return false; }
    for (int i = 1; 1LL * primes[i] * primes[i] <= n; i++) {
      if (n % primes[i] == 0) {
        while (n % primes[i] == 0) { n /= primes[i]; }
        return n == 1;
      }
    }
    return true;
  }

  int get_smallest(int n) const {
    if (n == 2) { return 1; }
    int phi_n = phi[n];
    std::vector<int> factors = get_factors(phi_n);
    for (int res = 2;; res++) {
      if (gcd(res, n) > 1) { continue; }
      if (test_root(res, n, phi[n], factors)) { return res; }
    }
  }

  std::vector<int> get_all(int n) const {
    std::vector<int> res;
    if (!has_primitive_root(n)) { return res; }
    int smallest = get_smallest(n);
    res.push_back(smallest);
    if (phi[n] <= 2) { return res; }
    res.push_back(quick_pow(smallest, phi[n] - 1, n));
    int m = phi[n] / 2;
    for (int i = 2; i <= m; i++) {
      if (gcd(i, phi[n]) == 1) {
        res.push_back(quick_pow(smallest, i, n));
        res.push_back(quick_pow(smallest, phi[n] - i, n));
      }
    }
    std::sort(res.begin(), res.end());
    return res;
  }

 private:
  std::vector<int> primes;
  std::vector<int> phi;

  static bool test_root(
      int g, int p, int phi_n, const std::vector<int>& factors) {
    for (int i = 0; i < factors.size(); i++) {
      if (quick_pow(g, phi_n / factors[i], p) == 1) { return false; }
    }
    return true;
  }
};
