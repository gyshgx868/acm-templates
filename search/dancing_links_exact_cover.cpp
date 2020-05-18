class DancingLinks {
 private:
  const int MAXN = 1005;
  const int MAXM = 1005;
  const int MAXNODE = 1000005

  int n, m, size;
  int U[MAXNODE], D[MAXNODE], R[MAXNODE], L[MAXNODE];
  int ROW[MAXNODE], COL[MAXNODE];
  int H[MAXN], S[MAXM];
  int ANS[MAXN];

 public:
  void init(int _n, int _m) {
    n = _n;
    m = _m;
    for (int i = 0; i <= m; i++) {
      S[i] = 0;
      U[i] = D[i] = i;
      L[i] = i - 1;
      R[i] = i + 1;
    }
    R[m] = 0;
    L[0] = m;
    size = m;
    for (int i = 1; i <= n; i++) {
      H[i] = -1;
    }
  }

  void link(int r, int c) {
    ++S[COL[++size] = c];
    ROW[size] = r;
    D[size] = D[c];
    U[D[c]] = size;
    U[size] = c;
    D[c] = size;
    if (H[r] < 0) {
      H[r] = L[size] = R[size] = size;
    } else {
      R[size] = R[H[r]];
      L[R[H[r]]] = size;
      L[size] = H[r];
      R[H[r]] = size;
    }
  }

  void remove(int c) {
    L[R[c]] = L[c];
    R[L[c]] = R[c];
    for (int i = D[c]; i != c; i = D[i]) {
      for (int j = R[i]; j != i; j = R[j]) {
        U[D[j]] = U[j];
        D[U[j]] = D[j];
        --S[COL[j]];
      }
    }
  }

  void resume(int c) {
    for (int i = U[c]; i != c; i = U[i]) {
      for (int j = L[i]; j != i; j = L[j]) {
        ++S[COL[U[D[j]] = D[U[j]] = j]];
      }
    }
    L[R[c]] = R[L[c]] = c;
  }

  bool dance(int d) {
    if (R[0] == 0) {
      printf("%d", d);
      for (int i = 0; i < d; i++) {
        printf(" %d", ANS[i]);
      }
      printf("\n");
      return true;
    }
    int c = R[0];
    for (int i = R[0]; i != 0; i = R[i]) {
      if (S[i] < S[c]) {
        c = i;
      }
    }
    remove(c);
    for (int i = D[c]; i != c; i = D[i]) {
      ANS[d] = ROW[i];
      for (int j = R[i]; j != i; j = R[j]) {
        remove(COL[j]);
      }
      if (dance(d + 1)) {
        return true;
      }
      for (int j = L[i]; j != i; j = L[j]) {
        resume(COL[j]);
      }
    }
    resume(c);
    return false;
  }
} dlx;

int main() {
  int n, m;
  while (~scanf("%d%d", &n, &m)) {
    dlx.init(n, m);
    for (int i = 1; i <= n; i++) {
      int cnt, c;
      scanf("%d", &cnt);
      while (cnt--) {
        scanf("%d", &c);
        dlx.link(i, c);
      }
    }
    if (!dlx.dance(0)) {
      puts("NO");
    }
  }
  return 0;
}
