std::vector<long long> sieve_interval(long long l, long long r) {
  std::vector<int> is_prime_small(sqrt(r) + 1, 1);
  std::vector<int> is_prime(r - l, 1);
  for (int i = 2; 1LL * i * i < r; i++) {
    if (is_prime_small[i]) {
      for (int j = 2 * i; 1LL * j * j < r; j += i) {
        is_prime_small[j] = 0;
      }
      long long from = std::max(2LL, (l + i - 1) / i) * i;
      for (long long j = from; j < r; j += i) {
        is_prime[(int) (j - l)] = 0;
      }
    }
  }
  std::vector<long long> primes;
  for (int i = 0; i < (int) (r - l); i++) {
    if (is_prime[i] && i + l > 1) {
      primes.push_back(i + l);
    }
  }
  return primes;
}
