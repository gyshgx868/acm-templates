/*
 * 模 M 域下的快速数论变换
 * M = C * 2 ^ NUM + 1, NUM > log(N), N 为数组大小
 * 若改 M 的值需要同时改 G 的值为 M 的原根
 */
const int M = 998244353, G = 3;
// 注意将以下乘号换成快速乘
// const ll M = 274877920265LL * (1LL << 23) + 1, G = 3;

void rader(std::vector<long long> &a) {
  int len = a.size();
  for (int i = 1, j = len / 2; i < len - 1; i++) {
    if (i < j) { std::swap(a[i], a[j]); }
    int k = len >> 1;
    while (j >= k) {
      j -= k;
      k /= 2;
    }
    if (j < k) { j += k; }
  }
}

void ntt(std::vector<long long> &a, const std::vector<long long> &wn,
         int mod, bool invert) {
  rader(a);
  int len = a.size();
  for (int h = 2, id = 1; h <= len; h <<= 1, ++id) {
    for (int j = 0; j < len; j += h) {
      long long w = 1;
      for (int k = j; k < j + (h >> 1); k++) {
        long long u = a[k] % mod;
        long long t = w * a[k + (h >> 1)] % mod;
        a[k] = (u + t) % mod;
        a[k + (h >> 1)] = (u - t + mod) % mod;
        w = w * wn[id] % mod;
      }
    }
  }
  if (invert) {
    for (int i = 1; i < (len >> 1); i++) { std::swap(a[i], a[len - i]); }
    long long inv = quick_pow(len, mod - 2, mod);
    for (int i = 0; i < len; i++) { a[i] = a[i] * inv % mod; }
  }
}

std::vector<int> multiply(char a[], char b[]) {
  int len1 = strlen(a);
  int len2 = strlen(b);
  int len = 1, bits = 1;
  while (len < len1 + len2) {
    len <<= 1;
    bits++;
  }
  std::vector<long long> wn(bits);
  for (int i = 0; i < bits; i++) {
    wn[i] = quick_pow(G, (M - 1) / (1LL << i), M);
  }
  std::vector<long long> x1(len);
  std::vector<long long> x2(len);
  for (int i = 0; i < len1; i++) { x1[i] = a[len1 - i - 1] - '0'; }
  for (int i = len1; i < len; i++) { x1[i] = 0; }
  for (int i = 0; i < len2; i++) { x2[i] = b[len2 - i - 1] - '0'; }
  for (int i = len2; i < len; i++) { x2[i] = 0; }
  ntt(x1, wn, M, false);
  ntt(x2, wn, M, false);
  for (int i = 0; i < len; i++) { x1[i] = x1[i] * x2[i]; }
  ntt(x1, wn, M, true);
  std::vector<int> res;
  int t = 0;
  for (int i = 0; i < len; i++, t /= 10) {
    t += x1[i];
    res.push_back(t % 10);
  }
  while (t != 0) {
    res.push_back(t % 10);
    t /= 10;
  }
  while (res[len - 1] == 0 && len > 1) {
    res.pop_back();
    len--;
  }
  std::reverse(res.begin(), res.end());
  return res;
}
