// 以a为基, 检查n是否为合数, 是合数返回true, 否则返回false
bool is_composite(long long a, long long n, long long x, long long t) {
  long long res = quick_pow(a, x, n);
  long long last = res;
  for (int i = 1; i <= t; i++) {
    res = quick_mul(res, res, n);
    if (res == 1 && last != 1 && last != n - 1) { return true; }
    last = res;
  }
  return res != 1;
}

// test_num为随机算法判定次数, 该值越大, 判错概率越小
bool miller_rabin(long long n, int test_num = 20) {
  if (n == 2) { return true; }
  if ((n & 1) == 0 || n < 2) { return false; }
  long long x = n - 1;
  long long t = 0;
  while ((x & 1) == 0) {
    x >>= 1;
    t++;
  }
  for (int i = 0; i < test_num; i++) {
    long long a = rand() % (n - 1) + 1;
    if (is_composite(a, n, x, t)) { return false; }
  }
  return true;
}
