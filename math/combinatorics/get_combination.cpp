std::vector<long long> fac;
std::vector<long long> inv;

void init(int upto, long long mod) {
  fac.resize(upto);
  inv.resize(upto);
  inv[0] = fac[0] = 1;
  for (int i = 1; i < upto; i++) {
    fac[i] = fac[i - 1] * i % mod;
    inv[i] = get_inv(fac[i]);
  }
}

long long c(int n, int m, long long mod) {
  return fac[n] * inv[m] % mod * inv[n - m] % mod;
}
