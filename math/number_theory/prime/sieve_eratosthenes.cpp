std::vector<int> sieve_eratosthenes(int upto) {
  std::vector<int> primes;
  std::vector<int> is_prime(upto, 1);
  is_prime[0] = is_prime[1] = 0;
  for (int i = 2; i < upto; i++) {
    if (is_prime[i]) {
      primes.push_back(i);
      for (int k = i * i; k < upto; k += i) {
        is_prime[k] = 0;
      }
    }
  }
  return primes;
}

std::vector<int> sieve_euler(int upto) {
  std::vector<int> primes;
  std::vector<int> is_not_prime(upto, 0);
  is_not_prime[0] = is_not_prime[1] = 1;
  for (int i = 2; i < upto; i++) {
    if (!is_not_prime[i]) {
      primes.push_back(i);
    }
    int count = primes.size();
    for (int j = 0; j < count && i * primes[j] < upto; j++) {
      is_not_prime[i * primes[j]] = 1;
      if (i % primes[j] == 0) {
        break;
      }
    }
  }
  return primes;
}
