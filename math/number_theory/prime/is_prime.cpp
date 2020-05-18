bool is_prime(long long n) {
  if (n == 1 || n == 0) { return false; }
  for (int i = 2; 1LL * i * i <= n; i++) {
    if (n % i == 0) { return false; }
  }
  return true;
}
