// next[i]: t[i]...t[m - 1] 与 t 的最长相同前缀长度
// extend[i]: s[i]...s[n - 1] 与 t 的最长相同前缀长度
void get_next(char* t, int m, int* next) {
  int a = 0, p = 0;
  next[0] = m;
  for (int i = 1; i < m; i++) {
    if (i >= p || i + next[i - a] >= p) {
      if (i >= p) { p = i; }
      while (p < m && t[p] == t[p - i]) { p++; }
      next[i] = p - i;
      a = i;
    } else {
      next[i] = next[i - a];
    }
  }
}

void get_extend(char* s, int n, char* t, int m, int* extend, int* next) {
  int a = 0, p = 0;
  get_next(t, m, next);
  for (int i = 0; i < n; i++) {
    if (i >= p || i + next[i - a] >= p) {
      if (i >= p) { p = i; }
      while (p < n && p - i < m && s[p] == t[p - i]) { p++; }
      extend[i] = p - i;
      a = i;
    } else {
      extend[i] = next[i - a];
    }
  }
}
