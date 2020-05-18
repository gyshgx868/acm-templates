class DancingLinks {
 private:
  const int MAXN = 105;
  const int MAXM = 105;
  const int MAXNODE = 10005;

  int n, m, size;
  int U[MAXNODE], D[MAXNODE], R[MAXNODE], L[MAXNODE];
  int ROW[MAXNODE], COL[MAXNODE];
  int H[MAXN], S[MAXM];
  bool vis[MAXNODE];

 public:
  int K;

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
    for (int i = D[c]; i != c; i = D[i]) {
      L[R[i]] = L[i];
      R[L[i]] = R[i];
    }
  }

  void resume(int c) {
    for (int i = U[c]; i != c; i = U[i]) {
      L[R[i]] = R[L[i]] = i;
    }
  }

  int h() {
    // 估值函数, 用精确覆盖去估算剪枝
    int ret = 0;
    // memset(vis, false, sizeof(vis));
    for (int i = R[0]; i; i = R[i]) {
      vis[i] = false;
    }
    for (int i = R[0]; i; i = R[i]) {
      if (vis[i]) {
        continue;
      }
      ret++;
      vis[i] = true;
      for (int j = D[i]; j != i; j = D[j]) {
        for (int k = R[j]; k != j; k = R[k]) {
          vis[COL[k]] = true;
        }
      }
    }
    return ret;
  }

  bool dance(int d) {
    if (d + h() > K) {
      return false;
    }
    if (R[0] == 0) {
      return d <= K;
    }
    int c = R[0];
    for (int i = R[0]; i != 0; i = R[i]) {
      if (S[i] < S[c]) {
        c = i;
      }
    }
    for (int i = D[c]; i != c; i = D[i]) {
      remove(i);
      for (int j = R[i]; j != i; j = R[j]) {
        remove(j);
      }
      if (dance(d + 1)) {
        return true;
      }
      for (int j = L[i]; j != i; j = L[j]) {
        resume(j);
      }
      resume(i);
    }
    return false;
  }
} dlx;

struct Point {
  int x, y;
} city[55], station[55];

double dis(const Point& a, const Point& b) {
  return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
}

int main() {
  int n, m, t, k;
  scanf("%d", &t);
  while (t--) {
    scanf("%d%d%d", &n, &m, &k);
    for (int i = 0; i < n; i++) {
      scanf("%d%d", &city[i].x, &city[i].y);
    }
    for (int i = 0; i < m; i++) {
      scanf("%d%d", &station[i].x, &station[i].y);
    }
    double low = 0, high = 1e8;
    while (high - low >= eps) {
      double mid = (low + high) / 2.0;
      dlx.init(m, n);
      dlx.K = k;
      for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
          if (dis(station[i], city[j]) < mid) {
            dlx.link(i + 1, j + 1);
          }
        }
      }
      if (dlx.dance(0)) {
        high = mid - eps;
      } else {
        low = mid + eps;
      }
    }
    printf("%.6f\n", low);
  }
  return 0;
}