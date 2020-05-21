namespace ntt {

/*
 * 模 mod 域下的快速数论变换
 * 若改 mod 的值需要同时改 G 的值为 mod 的原根
 */
const int G = 3;
const int mod = 998244353;

template <class T>
void rader(std::vector<T>& a) {
  int len = a.size(), half_len = a.size() / 2;
  for (int i = 1, j = half_len; i < len - 1; i++) {
    if (i < j) { std::swap(a[i], a[j]); }
    int k = half_len;
    while (j >= k) {
      j -= k;
      k /= 2;
    }
    if (j < k) { j += k; }
  }
}

template <class T>
void transform(std::vector<T>& a, bool invert) {
  static std::vector<T> wn;
  if (wn.empty()) {
    wn.resize(64);
    for (int i = 0; i < 64; i++) {
      wn[i] = quick_pow(G, (mod - 1) / (1LL << i), mod);
    }
  }
  rader(a);
  int len = a.size();
  for (int h = 2, id = 1; h <= len; h *= 2, id++) {
    int half = h / 2;
    for (int j = 0; j < len; j += h) {
      T w = 1;
      for (int k = j; k < j + half; k++) {
        T u = a[k] % mod;
        T t = static_cast<T>(1LL * w * a[k + half] % mod);
        a[k] = (u + t) % mod;
        a[k + half] = (u - t + mod) % mod;
        w = static_cast<T>(1LL * w * wn[id] % mod);
      }
    }
  }
  if (invert) {
    int half_len = len / 2;
    for (int i = 1; i < half_len; i++) { std::swap(a[i], a[len - i]); }
    T inv = quick_pow(len, mod - 2, mod);
    for (int i = 0; i < len; i++) {
      a[i] = static_cast<T>(1LL * a[i] * inv % mod);
    }
  }
}

std::vector<int> multiply(char a[], char b[]) {
  int len1 = strlen(a);
  int len2 = strlen(b);
  int len = 1;
  while (len < len1 + len2) { len *= 2; }
  std::vector<int> x1(len, 0);
  std::vector<int> x2(len, 0);
  for (int i = 0; i < len1; i++) { x1[i] = a[len1 - i - 1] - '0'; }
  for (int i = 0; i < len2; i++) { x2[i] = b[len2 - i - 1] - '0'; }
  transform(x1, false);
  transform(x2, false);
  for (int i = 0; i < len; i++) { x1[i] = 1LL * x1[i] * x2[i] % mod; }
  transform(x1, true);
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

} // namespace ntt
