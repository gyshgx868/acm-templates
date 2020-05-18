// 位置 i 和 (i 二进制反转后位置) 互换
void rader(std::vector<std::complex<double> >& y) {
  int len = y.size();
  for (int i = 1, j = len / 2; i < len - 1; i++) {
    if (i < j) { std::swap(y[i], y[j]); }
    int k = len / 2;
    while (j >= k) {
      j -= k;
      k /= 2;
    }
    if (j < k) { j += k; }
  }
}

// y 的长度必须为 2^k 形式; invert 为 false 时是DFT, 为 true 时是IDFT
void fft(std::vector<std::complex<double> >& y, bool invert) {
  int len = y.size();
  rader(y);
  for (int h = 2; h <= len; h <<= 1) {
    double angle = 2.0 * PI / h;
    if (invert) { angle = -angle; }
    std::complex<double> wn(cos(angle), sin(angle));
    for (int j = 0; j < len; j += h) {
      std::complex<double> w(1, 0);
      for (int k = j; k < j + h / 2; k++) {
        std::complex<double> u = y[k];
        std::complex<double> t = w * y[k + h / 2];
        y[k] = u + t;
        y[k + h / 2] = u - t;
        w = w * wn;
      }
    }
  }
  if (invert) {
    for (int i = 0; i < len; i++) { y[i].real(y[i].real() / len); }
  }
}

std::vector<int> multiply(char a[], char b[]) {
  int len1 = strlen(a);
  int len2 = strlen(b);
  int len = 1;
  while (len < len1 + len2) { len <<= 1; }
  std::vector<std::complex<double> > x1(len);
  std::vector<std::complex<double> > x2(len);
  for (int i = 0; i < len1; i++) {
    x1[i] = std::complex<double>(a[len1 - i - 1] - '0', 0);
  }
  for (int i = len1; i < len; i++) { x1[i] = std::complex<double>(0, 0); }
  for (int i = 0; i < len2; i++) {
    x2[i] = std::complex<double>(b[len2 - i - 1] - '0', 0);
  }
  for (int i = len2; i < len; i++) { x2[i] = std::complex<double>(0, 0); }
  fft(x1, false);
  fft(x2, false);
  for (int i = 0; i < len; i++) { x1[i] = x1[i] * x2[i]; }
  fft(x1, true);
  std::vector<int> res;
  int t = 0;
  for (int i = 0; i < len; i++, t /= 10) {
    t += (int) (x1[i].real() + 0.1);
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
