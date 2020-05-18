long long get_inv(long long a, long long mod) {
  long long x, y;
  long long t = extended_gcd(a, mod, x, y);
  if (t != 1) { return -1; }
  return (x % mod + mod) % mod;
}

long long get_inv(long long a, long long mod) {
  return a == 1 ? a : (mod - mod / a) * inv(mod % a) % mod;
}
