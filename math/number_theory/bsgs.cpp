int bsgs(int b, int n, int p) {
  if (n == 1) { return 0; }
  HashTable ht;
  int m = (int) sqrt(p);
  long long x = 1, y = 1;
  for (int i = 0; i < m; i++, y = y * b % p) { ht.add(y * n % p); }
  for (int i = m;; i += m) {
    x = x * y % p;
    int j = ht.get(x);
    if (j != -1) { return i - j; }
    if (i > p) { break; }
  }
  return -1;
}
