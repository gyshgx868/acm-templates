std::vector<int> get_factors(long long n) {
  std::vector<int> factors;
  for (int i = 2; 1LL * i * i <= n; i++) {
    if (n % i == 0) {
      factors.push_back(i);
      while (n % i == 0) { n /= i; }
    }
  }
  if (n > 1) { factors.push_back(n); }
  return factors;
}
