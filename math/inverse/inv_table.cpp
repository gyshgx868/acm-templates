std::vector<long long> get_inv(int upto, long long mod) {
  std::vector<long long> inv(upto);
  inv[1] = inv[0] = 1;
  for (int i = 2; i < upto; i++) {
    inv[i] = inv[mod % i] * (mod - mod / i) % mod;
  }
  return inv;
}
