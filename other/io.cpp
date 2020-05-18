inline bool read(int& res) {
  int c = getchar();
  if (c == EOF) { return false; }
  while (c == ' ' || c == '\n') { c = getchar(); }
  bool flag = c == '-';
  res = c == '-' ? 0 : c - '0';
  while ((c = getchar()) >= '0' && c <= '9') {
    res = res * 10 + c - '0';
  }
  if (flag) { res = -res; }
  return true;
}

inline bool read(double& res) {
  int c = getchar();
  if (c == EOF) { return false; }
  while (c == ' ' || c == '\n') { c = getchar(); }
  bool flag = c == '-';
  res = c == '-' ? 0.0 : c - '0';
  while ((c = getchar()) >= '0' && c <= '9') {
    res = res * 10 + c - '0';
  }
  if (c == '.') {
    double dec = 0.1;
    while ((c = getchar()) >= '0' && c <= '9') {
      res += dec * (c - '0');
      dec *= 0.1;
    }
  }
  res = flag ? -res : res;
  return true;
}

inline void write(int res) {
  if (res < 0) {
    res = -res;
    putchar('-');
  }
  if (res >= 10) { write(res / 10); }
  putchar(res % 10 + '0');
}
