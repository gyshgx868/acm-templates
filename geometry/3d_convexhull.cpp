class ConvexHull3D {
 public:
  explicit ConvexHull3D(int n) {
    pts.resize(n);
    tri_id.resize(n, std::vector<int>(n));
  }

  Point& operator [](int index) { return pts[index]; }

  Point operator [](int index) const { return pts[index]; }

  void build_convexhull() {  // 构建三维凸包
    if (pts.size() < 4) { return; }
    if (judge_coplanar(1) || judge_coplanar(2) || judge_coplanar(3)) { return; }
    for (int i = 0; i < 4; i++) {
      Triangle t((i + 1) % 4, (i + 2) % 4, (i + 3) % 4);
      if (compare(pts[i], t) > 0) { std::swap(t.b, t.c); }
      tri_id[t.a][t.b] = tri_id[t.b][t.c] = tri_id[t.c][t.a] = tris.size();
      tris.push_back(t);
    }
    for (int i = 4; i < pts.size(); i++) {
      for (int j = 0; j < tris.size(); j++) {
        if (tris[j].in_convexhull && compare(pts[i], tris[j]) > eps) {
          dfs(i, j);
          break;
        }
      }
    }
    int at = 0;
    for (int i = 0; i < tris.size(); i++) {
      if (tris[i].in_convexhull) { tris[at++] = tris[i]; }
    }
    tris.resize(at);
  }

  double get_area() const {
    // 凸包表面积
    if (pts.size() == 3) {
      Point p = det(det(pts[0], pts[1]), pts[2]);
      return p.norm() / 2.0;
    }
    double res = 0.0;
    for (int i = 0; i < tris.size(); i++) {
      res += tri_area(tris[i].a, tris[i].b, tris[i].c);
    }
    return res / 2.0;
  }

  double get_volume() const {
    // 凸包体积
    double res = 0.0;
    Point origin(0, 0, 0);
    for (int i = 0; i < tris.size(); i++) {
      res += volume(origin, pts[tris[i].a], pts[tris[i].b], pts[tris[i].c]);
    }
    return fabs(res / 6.0);
  }

  int num_triangles() const { return tris.size(); }

  // 表面多边形个数
  int num_polygons() const {
    int res = 0;
    for (int i = 0; i < tris.size(); i++) {
      int flag = 1;
      for (int j = 0; j < i; j++) {
        if (is_same(i, j)) {
          flag = 0;
          break;
        }
      }
      res += flag;
    }
    return res;
  }

  Point get_center() const {
    // 求凸包质心
    Point ans(0, 0, 0), temp = pts[tris[0].a];
    double v = 0.0, t2;
    for (int i = 0; i < tris.size(); i++) {
      if (tris[i].in_convexhull) {
        Point p1 = pts[tris[i].a], p2 = pts[tris[i].b], p3 = pts[tris[i].c];
        t2 = volume(temp, p1, p2, p3) / 6.0; // 体积大于0表示点temp不在这个面上
        if (t2 > 0) {
          ans.x += (p1.x + p2.x + p3.x + temp.x) * t2;
          ans.y += (p1.y + p2.y + p3.y + temp.y) * t2;
          ans.z += (p1.z + p2.z + p3.z + temp.z) * t2;
          v += t2;
        }
      }
    }
    ans = ans / (4 * v);
    return ans;
  }

  double dist_to_convexhull(const Point& p) const {
    // 点到凸包上的最近距离 (枚举每个面到这个点的距离)
    double min = inf;
    for (int i = 0; i < tris.size(); i++) {
      if (!tris[i].in_convexhull) { continue; }
      Point p1 = pts[tris[i].a], p2 = pts[tris[i].b], p3 = pts[tris[i].c];
      double a = (p2.y - p1.y) * (p3.z - p1.z) - (p2.z - p1.z) * (p3.y - p1.y);
      double b = (p2.z - p1.z) * (p3.x - p1.x) - (p2.x - p1.x) * (p3.z - p1.z);
      double c = (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x);
      double d = -(a * p1.x + b * p1.y + c * p1.z);
      double temp = fabs(a * p.x + b * p.y + c * p.z + d)
          / sqrt(a * a + b * b + c * c);
      if (temp < min) { min = temp; }
    }
    return min;
  }

 private:
  struct Triangle {
    int a, b, c;         // 表示凸包一个面上三个点的编号
    bool in_convexhull;  // 表示该面是否属于最终凸包中的面

    Triangle() : a(0), b(0), c(0), in_convexhull(true) {}

    Triangle(int _a, int _b, int _c) : a(_a), b(_b), c(_c) {
      in_convexhull = true;
    }
  };

  std::vector<Triangle> tris;  // 凸包表面三角形
  std::vector<std::vector<int> > tri_id;
  std::vector<Point> pts;      // 凸包点集

  double compare(const Point& p, const Triangle& f) const {
    // 正: 点在面同向
    Point m = pts[f.b] - pts[f.a];
    Point n = pts[f.c] - pts[f.a];
    Point t = p - pts[f.a];
    return dot(det(m, n), t);
  }

  double tri_area(int a, int b, int c) const {
    // 三角形面积*2
    return det(pts[b] - pts[a], pts[c] - pts[a]).norm();
  }

  // 四面体体积
  double volume(
      const Point& a, const Point& b, const Point& c, const Point& d) const {
    // abc面方向与d一致时为正
    return dot(det(b - a, c - a), d - a);
  }

  bool is_same(int s, int t) const {
    const Point& a = pts[tris[s].a];
    const Point& b = pts[tris[s].b];
    const Point& c = pts[tris[s].c];
    return fabs(volume(a, b, c, pts[tris[t].a])) < eps
        && fabs(volume(a, b, c, pts[tris[t].b])) < eps
        && fabs(volume(a, b, c, pts[tris[t].c])) < eps;
  }

  bool judge_coplanar(int from) {
    std::vector<Point> diff;
    for (int i = 1; i < from; i++) { diff.push_back(pts[i] - pts[i - 1]); }
    for (int i = from; i < pts.size(); i++) {
      double d = (pts[0] - pts[i]).norm();
      if (from == 2) {
        d = det(diff[0], pts[1] - pts[i]).norm();
      } else if (from == 3) {
        d = fabs(dot(det(diff[0], diff[1]), pts[2] - pts[i]));
      }
      if (d > eps) {
        std::swap(pts[from], pts[i]);
        return false;
      }
    }
    return true;
  }

  void deal(int p, int a, int b) {
    int f = tri_id[a][b];
    if (tris[f].in_convexhull) {
      if (compare(pts[p], tris[f]) > eps) {
        dfs(p, f);
      } else {
        Triangle t(b, a, p);
        tri_id[p][b] = tri_id[a][p] = tri_id[b][a] = tris.size();
        tris.push_back(t);
      }
    }
  }

  void dfs(int p, int now) {
    tris[now].in_convexhull = false;
    deal(p, tris[now].b, tris[now].a);
    deal(p, tris[now].c, tris[now].b);
    deal(p, tris[now].a, tris[now].c);
  }
};
