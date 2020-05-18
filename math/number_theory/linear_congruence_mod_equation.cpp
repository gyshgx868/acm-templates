// 如果有解则输出解并返回 true, 否则返回 false
bool solve_equation(int a, int b, int n) {
  int x, y;
  int d = extended_gcd(a, n, x, y);
  if (b % d != 0) {
    return false;
  } else {
    int e = x * (b / d) % n;
    for (int i = 0; i < d; i++) {
      printf("%d\n", (e + i * (n / d)) % n);
    }
    return true;
  }
}
