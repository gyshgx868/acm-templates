long long gp_sum(long long q, long long n, long long m) {
  n++;
  long long res = 0, temp = 1;
  while (n > 0) {
    if (n & 1) { res = (res * q % m + temp % m) % m; }
    temp = (temp * (1 + q)) % M;
    q = q * q % M;
    n >>= 1;
  }
  return res;
}
