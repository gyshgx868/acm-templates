int bsgs(int b, int n, int p) {
  long long k = 1 % n;
  int d = 0;
  if (gcd(b, n) != 1) {
    long long res = 1;
    for (int i = 0; i <= 50; i++) {
      if (res == p) { return i; }
      res = res * b % n;
    }
    long long tmp;
    while ((tmp = gcd(b, n)) != 1) {
      if (p % tmp) { return -1; }
      d++;
      p /= tmp;
      n /= tmp;
      k = k * b / tmp % n;
    }
  }
  HashTable ht;
  int M = (int) ceil(sqrt(n));
  long long r = 1;
  for (int i = 0; i < M; i++) {
    ht.add(r);
    r = r * b % n;
  }
  long long x, y;
  for (int i = 0; i < M; i++) {
    extended_gcd(k, n, x, y);
    int j = ht.get((x * p % n + n) % n);
    if (j != -1) { return i * M + j + d; }
    k = k * r % n;
  }
  return -1;
}
