#define next(i) ((i + 1) % n)

inline double sqr(double x) { return x * x; }

inline double safe_sqrt(double x) { return std::sqrt(std::max(0.0, x)); }

inline int sgn(double x) { return x < -eps ? -1 : x > eps; }

struct Point {
  double x, y;

  explicit Point(double x = 0, double y = 0) : x(x), y(y) {}

  Point operator +(const Point& b) const { return Point(x + b.x, y + b.y); }

  Point operator -(const Point& b) const { return Point(x - b.x, y - b.y); }

  Point operator *(double b) const { return Point(x * b, y * b); }

  Point operator /(double b) const { return Point(x / b, y / b); }

  friend Point operator *(double a, const Point& b) {
    return Point(a * b.x, a * b.y);
  }

  bool operator ==(const Point& b) const {
    return !sgn(x - b.x) && !sgn(y - b.y);
  }

  bool operator !=(const Point& rhs) const { return !(rhs == *this); }

  bool operator <(const Point& b) const {
    return sgn(x - b.x) < 0 || (sgn(x - b.x) == 0 && sgn(y - b.y) < 0);
  }

  bool operator >(const Point& rhs) const { return rhs < *this; }

  bool operator <=(const Point& rhs) const { return !(rhs < *this); }

  bool operator >=(const Point& rhs) const { return !(*this < rhs); }

  double norm() const { return safe_sqrt(sqr(x) + sqr(y)); }

  friend double det(const Point& a, const Point& b) {
    return a.x * b.y - a.y * b.x;
  }

  friend double dot(const Point& a, const Point& b) {
    return a.x * b.x + a.y * b.y;
  }

  friend double dist(const Point& a, const Point& b) {
    return (a - b).norm();
  }

  double arg() const { return std::atan2(y, x); }

  // 逆时针旋转angle弧度
  Point rotate(double angle) const { return rotate(cos(angle), sin(angle)); }

  Point rotate(const Point& p, double angle) const {
    return (*this - p).rotate(angle) + p;
  }

  Point rotate(double cosa, double sina) const {
    return Point(x * cosa - y * sina, x * sina + y * cosa);
  }

  friend std::istream& operator >>(std::istream& in, Point& p) {
    in >> p.x >> p.y;
    return in;
  }

  friend std::ostream& operator <<(std::ostream& os, const Point& p) {
    os << p.x << ' ' << p.y;
    return os;
  }

  int input() { return scanf("%lf%lf", &x, &y); }
};

struct Line {
  Point s, t;

  Line() : s(Point()), t(Point()) {}

  explicit Line(const Point& _s, const Point& _t) : s(_s), t(_t) {}

  Point vec() const { return t - s; }

  double norm() const { return vec().norm(); }

  // 点在直线上
  bool is_point_on_line(const Point& p) const {
    return sgn(det(p - s, t - s)) == 0;
  }

  // 点在线段上
  bool is_point_on_seg(const Point& p) const {
    return is_point_on_line(p) && sgn(dot(p - s, p - t)) <= 0;
  }

  // 点在线段上 (不含端点)
  bool is_point_on_segx(const Point& p) const {
    return is_point_on_line(p) && sgn(dot(p - s, p - t)) < 0;
  }

  // 点到直线的垂足
  Point foot_point(const Point& p) const {
    return s + vec() * ((dot(p - s, vec()) / norm()) / (norm()));
  }

  // 点到直线的距离
  double dist_to_line(const Point& p) const {
    return fabs(det(p - s, vec()) / norm());
  }

  // 点到线段的距离
  double dist_to_seg(const Point& p) const {
    if (sgn(dot(p - s, t - s)) < 0) { return (p - s).norm(); }
    if (sgn(dot(p - t, s - t)) < 0) { return (p - t).norm(); }
    return dist_to_line(p);
  }

  // 判断两直线是否平行 (0: 不平行; 1: 平行; 2: 重合)
  friend int is_parallel(const Line& l1, const Line& l2) {
    if (sgn(det(l1.vec(), l2.vec())) == 0) {
      if (sgn(det(l2.s - l1.s, l2.t - l1.s)) == 0) { return 2; }
      return 1;
    }
    return 0;
  }

  // 判断两个点是否在直线的同一侧
  friend bool is_on_same_side(const Line& l, const Point& a, const Point& b) {
    return sgn(det(b - l.s, l.vec())) * sgn(det(a - l.s, l.vec())) > 0;
  }

  // 两直线的交点
  friend Point line_intersect_line(const Line& l1, const Line& l2) {
    // 利用相似三角形对应边成比例
    double s1 = det(l1.s - l2.s, l2.vec());
    double s2 = det(l1.t - l2.s, l2.vec());
    return (l1.t * s1 - l1.s * s2) / (s1 - s2);
  }

  // 判断线段交
  friend bool is_seg_intersect_seg(const Line& l1, const Line& l2) {
    if (!sgn(det(l2.s - l1.s, l1.vec())) && !sgn(det(l2.t - l1.s, l1.vec()))) {
      bool t1 = l1.is_point_on_seg(l2.s) || l1.is_point_on_seg(l2.t);
      bool t2 = l2.is_point_on_seg(l1.s) || l2.is_point_on_seg(l1.t);
      return t1 || t2;
    }
    return !is_on_same_side(l1, l2.s, l2.t) && !is_on_same_side(l2, l1.s, l1.t);
  }

  // 直线沿法线方向移动d距离
  friend Line move(const Line& l, double d) {
    Point p = l.vec();
    p = p / p.norm();
    p = p.rotate(PI / 2);
    return Line(l.s + p * d, l.t + p * d);
  }

  friend std::istream& operator >>(std::istream& in, Line& l) {
    in >> l.s >> l.t;
    return in;
  }

  friend std::ostream& operator <<(std::ostream& os, const Line& l) {
    os << l.s << '\n' << l.t;
    return os;
  }

  int input() {
    s.input();
    return t.input();
  }
};

struct Polygon {
  int n;
  std::vector<Point> p;

  explicit Polygon(int _n = 0) : n(_n) { p.resize(_n); }

  // 多边形周长
  double perimeter() const {
    double sum = 0;
    for (int i = 0; i < n; i++) { sum += (p[next(i)] - p[i]).norm(); }
    return sum;
  }

  // 多边形面积
  double area() const {
    double sum = 0.0;
    for (int i = 0; i < n; i++) { sum += det(p[i], p[next(i)]); }
    return sum / 2.0 + eps;
  }

  // 判断点与多边形的位置关系, 0外, 1内,2边上
  int is_point_in(const Point& t) const {
    int num = 0;
    for (int i = 0; i < n; i++) {
      if (Line(p[i], p[next(i)]).is_point_on_seg(t)) { return 2; }
      int k = sgn(det(p[next(i)] - p[i], t - p[i]));
      int d1 = sgn(p[i].y - t.y);
      int d2 = sgn(p[next(i)].y - t.y);
      if (k > 0 && d1 <= 0 && d2 > 0) { num++; }
      if (k < 0 && d2 <= 0 && d1 > 0) { num--; }
    }
    return num != 0;
  }

  // 多边形重心
  Point mass_center() const {
    Point res;
    if (sgn(area()) == 0) { return res; }
    for (int i = 0; i < n; i++) {
      res = res + (p[i] + p[next(i)]) * det(p[i], p[next(i)]);
    }
    return res / area() / 6 + Point(eps, eps);
  }

  // 多边形边界上格点的数量
  int border_point_num() const {
    int num = 0;
    for (int i = 0; i < n; i++) {
      int a = (int) fabs(p[next(i)].x - p[i].x);
      int b = (int) fabs(p[next(i)].y - p[i].y);
      num += gcd(a, b);
    }
    return num;
  }

  // 多边形内格点数量
  int inside_point_num() const {
    return int(area()) + 1 - border_point_num() / 2;
  }

  friend std::istream& operator >>(std::istream& in, Polygon& poly) {
    for (int i = 0; i < poly.n; i++) { in >> poly.p[i]; }
    return in;
  }

  friend std::ostream& operator <<(std::ostream& os, const Polygon& poly) {
    for (int i = 0; i < poly.n; i++) {
      os << poly.p[i];
      if (i != poly.n - 1) { os << '\n'; }
    }
    return os;
  }

  int input() {
    int state = -1;
    for (int i = 0; i < n; i++) { state = p[i].input(); }
    return state;
  }
};

struct Convex : public Polygon {
  explicit Convex(int n = 0) : Polygon(n) { is_init_angle = false; }

  // convex(vector<point> &v):polygon(v){}
  // 需要先求凸包, 若凸包每条边除端点外都有点, 则可唯一确定凸包
  bool is_unique(const std::vector<Point>& v) const {
    if (sgn(area()) == 0) { return false; }
    for (int i = 0; i < n; i++) {
      Line l(p[i], p[next(i)]);
      bool flag = false;
      for (int j = 0; j < v.size(); j++) {
        if (l.is_point_on_segx(v[j])) {
          flag = true;
          break;
        }
      }
      if (!flag) { return false; }
    }
    return true;
  }

  // O(n)时间内判断点是否在凸包内
  bool contains_n(const Point& a) const {
    int sign = 0;
    for (int i = 0; i < n; i++) {
      int x = sgn(det(p[i] - a, p[next(i)] - a));
      if (x) {
        if (sign) {
          if (sign != x) { return false; }
        } else {
          sign = x;
        }
      }
    }
    return true;
  }

  // O(logn)时间内判断点是否在凸包内
  bool contains_logn(const Point& a) const {
    Point g = (p[0] + p[n / 3] + p[2 * n / 3]) / 3.0;
    int l = 0, r = n;
    while (l + 1 < r) {
      int m = (l + r) / 2;
      if (sgn(det(p[l] - g, p[m] - g)) > 0) {
        if (sgn(det(p[l] - g, a - g)) >= 0 && sgn(det(p[m] - g, a - g)) < 0) {
          r = m;
        } else {
          l = m;
        }
      } else {
        if (sgn(det(p[l] - g, a - g)) < 0 && sgn(det(p[m] - g, a - g)) >= 0) {
          l = m;
        } else {
          r = m;
        }
      }
    }
    return bool(sgn(det(p[r % n] - a, p[l] - a)) - 1);
  }

  // 最远点对（直径）
  int first, second; // 最远的两个点对应标号
  double diameter() {
    double mx = 0;
    if (n == 1) {
      first = second = 0;
      return mx;
    }
    for (int i = 0, j = 1; i < n; i++) {
      while (sgn(det(p[next(i)] - p[i], p[j] - p[i]) -
          det(p[next(i)] - p[i], p[next(j)] - p[i])) < 0) {
        j = next(j);
      }
      double d = dist(p[i], p[j]);
      if (d > mx) {
        mx = d;
        first = i;
        second = j;
      }
      d = dist(p[next(i)], p[next(j)]);
      if (d > mx) {
        mx = d;
        first = next(i);
        second = next(j);
      }
    }
    return mx;
  }

  // 凸包是否与直线有交点O(logn), 需要O(n)的预处理, 适合判断与直线集是否有交点
  std::vector<double> ang; // 角度
  bool is_init_angle;

  int find_angle(double x) const {
    return std::upper_bound(ang.begin(), ang.end(), x) - ang.begin();
  }

  double get_angle(const Point& p) const { // 获取向量角度[0, 2PI]
    double res = std::atan2(p.y, p.x);   // (-PI, PI]
    if (res < -PI / 2 + eps) { res += 2 * PI; }
    return res;
  }

  void init_angle() {
    for (int i = 0; i < n; i++) {
      ang.push_back(get_angle(p[next(i)] - p[i]));
    }
    is_init_angle = true;
  }

  bool is_intersect_line(const Line& l) {
    if (!is_init_angle) { init_angle(); }
    int i = find_angle(get_angle(l.t - l.s));
    int j = find_angle(get_angle(l.s - l.t));
    return det(l.t - l.s, p[i] - l.s) * det(l.t - l.s, p[j] - l.s) < 0;
  }
};

Convex convexhull(std::vector<Point>& a) {
  // 从一个vector获取凸包
  Convex res(2 * a.size() + 5);
  sort(a.begin(), a.end());
  a.erase(unique(a.begin(), a.end()), a.end());
  int m = 0;
  res.p[0] = Point(-inf, 0);
  for (int i = 0; i < a.size(); i++) {
    // <=0则不含边界, <0则含边界
    while (m > 1 &&
        sgn(det(res.p[m - 1] - res.p[m - 2], a[i] - res.p[m - 2])) <= 0) {
      m--;
    }
    res.p[m++] = a[i];
  }
  int k = m;
  for (int i = a.size() - 2; i >= 0; i--) {
    // <=0则不含边界, <0则含边界
    while (m > k &&
        sgn(det(res.p[m - 1] - res.p[m - 2], a[i] - res.p[m - 2])) <= 0) {
      m--;
    }
    res.p[m++] = a[i];
  }
  if (m > 1) { m--; }
  res.p.resize(m);
  res.n = m;
  return res;
}

struct HalfPlane : public Line {
  // ax+by+c<=0
  double a, b, c;

  // s->t的左侧表示半平面
  explicit HalfPlane(
      const Point& s = Point(), const Point& t = Point()) : Line(s, t) {
    a = t.y - s.y;
    b = s.x - t.x;
    c = det(t, s);
  }

  HalfPlane(double a, double b, double c) : a(a), b(b), c(c) {}

  // 求点p带入直线方程的值
  double calc(const Point& p) const { return p.x * a + p.y * b + c; }

  // 半平面和直线相交
  friend Point hp_intersect_line(const HalfPlane& h, const Line& l) {
    Point res;
    double t1 = h.calc(l.s), t2 = h.calc(l.t);
    res.x = (t2 * l.s.x - t1 * l.t.x) / (t2 - t1);
    res.y = (t2 * l.s.y - t1 * l.t.y) / (t2 - t1);
    return res;
  }

  // 两个半平面相交
  friend Point hp_intersect_hp(const HalfPlane& h1, const HalfPlane& h2) {
    double x = (h1.b * h2.c - h1.c * h2.b) / (h1.a * h2.b - h2.a * h1.b) + eps;
    double y = (h1.a * h2.c - h2.a * h1.c) / (h1.b * h2.a - h1.a * h2.b) + eps;
    return Point(x, y);
  }

  // 凸多边形与半平面交 (cut)
  friend Convex hp_intersect_convex(const HalfPlane& h, const Convex& cv) {
    Convex res;
    for (int i = 0; i < cv.n; i++) {
      if (h.calc(cv.p[i]) < -eps) {
        res.p.push_back(cv.p[i]);
      } else {
        int j = i - 1;
        if (j < 0) { j = cv.n - 1; }
        if (h.calc(cv.p[j]) < -eps) {
          res.p.push_back(hp_intersect_line(h, Line(cv.p[j], cv.p[i])));
        }
        j = i + 1;
        if (j == cv.n) { j = 0; }
        if (h.calc(cv.p[j]) < -eps) {
          res.p.push_back(hp_intersect_line(h, Line(cv.p[i], cv.p[j])));
        }
      }
    }
    res.n = res.p.size();
    return res;
  }

  // 点在半平面内
  friend bool is_point_in_hp(const Point& p, const HalfPlane& h) {
    return sgn(det(p - h.s, h.t - h.s)) <= 0;
  }

  bool operator <(const HalfPlane& h2) const {
    int res = sgn(vec().arg() - h2.vec().arg());
    return res == 0 ? sgn(det(s - h2.s, h2.t - h2.s)) < 0 : res < 0;
  }

  // 半平面交出的凸多边形
  friend Convex convex_from_hps(std::vector<HalfPlane>& v) {
    std::sort(v.begin(), v.end());
    std::deque<HalfPlane> q;
    std::deque<Point> res;
    q.push_back(v[0]);
    for (int i = 1; i < v.size(); i++) {
      if (sgn(v[i].vec().arg() - v[i - 1].vec().arg()) == 0) { continue; }
      while (!res.empty() && !is_point_in_hp(res.back(), v[i])) {
        res.pop_back();
        q.pop_back();
      }
      while (!res.empty() && !is_point_in_hp(res.front(), v[i])) {
        res.pop_front();
        q.pop_front();
      }
      res.push_back(line_intersect_line(q.back(), v[i]));
      q.push_back(v[i]);
    }
    while (!res.empty() && !is_point_in_hp(res.back(), q.front())) {
      res.pop_back();
      q.pop_back();
    }
    while (!res.empty() && !is_point_in_hp(res.front(), q.back())) {
      res.pop_front();
      q.pop_front();
    }
    res.push_back(line_intersect_line(q.back(), q.front()));
    Convex cv(res.size());
    cv.p.assign(res.begin(), res.end());
    return cv;
  }
};

// 多边形的核, 逆时针
Convex polygon_core(const Polygon& a) {
  Convex res;
  res.p.push_back(Point(-inf, -inf));
  res.p.push_back(Point(inf, -inf));
  res.p.push_back(Point(inf, inf));
  res.p.push_back(Point(-inf, inf));
  res.n = 4;
  for (int i = 0; i < a.n; i++) {
    res = hp_intersect_convex(HalfPlane(a.p[i], a.p[(i + 1) % a.n]), res);
  }
  return res;
}

// 凸多边形交出的凸多边形
Convex convex_intersect_convex(const Convex& c1, const Convex& c2) {
  std::vector<HalfPlane> h;
  for (int i = 0; i < c1.p.size(); i++) {
    h.push_back(HalfPlane(c1.p[i], c1.p[(i + 1) % c1.p.size()]));
  }
  for (int i = 0; i < c2.p.size(); i++) {
    h.push_back(HalfPlane(c2.p[i], c2.p[(i + 1) % c2.p.size()]));
  }
  return convex_from_hps(h);
}

struct Circle {
  Point o;
  double r;

  explicit Circle(Point _o = Point(), double _r = 0) : o(_o), r(_r) {}

  bool operator ==(const Circle& c) const { return o == c.o && !sgn(r - c.r); }

  double area() const { return PI * r * r; }

  // 圆与线段交 用参数方程表示直线：P=A+t*(B-A), 带入圆的方程求解t
  friend std::vector<Point> circle_intersect_seg(
      const Circle& c, const Line& l) {
    double dx = l.t.x - l.s.x, dy = l.t.y - l.s.y;
    double A = dx * dx + dy * dy;
    double B = 2 * dx * (l.s.x - c.o.x) + 2 * dy * (l.s.y - c.o.y);
    double C = sqr(l.s.x - c.o.x) + sqr(l.s.y - c.o.y) - sqr(c.r);
    double delta = B * B - 4 * A * C;
    std::vector<Point> res;
    if (sgn(delta) >= 0) { // or delta > -eps ?
      // 可能需要注意delta接近-eps的情况
      double w1 = (-B - safe_sqrt(delta)) / (2 * A);
      double w2 = (-B + safe_sqrt(delta)) / (2 * A);
      if (sgn(w1 - 1) <= 0 && sgn(w1) >= 0) {
        res.push_back(l.s + w1 * (l.t - l.s));
      }
      if (sgn(w2 - 1) <= 0 && sgn(w2) >= 0) {
        res.push_back(l.s + w2 * (l.t - l.s));
      }
    }
    return res;
  }

  // 圆与直线交
  friend std::vector<Point> circle_intersect_line(
      const Circle& c, const Line& l) {
    double dx = l.t.x - l.s.x, dy = l.t.y - l.s.y;
    double A = dx * dx + dy * dy;
    double B = 2 * dx * (l.s.x - c.o.x) + 2 * dy * (l.s.y - c.o.y);
    double C = sqr(l.s.x - c.o.x) + sqr(l.s.y - c.o.y) - sqr(c.r);
    double delta = B * B - 4 * A * C;
    std::vector<Point> res;
    if (sgn(delta) >= 0) { // or delta > -eps ?
      double w1 = (-B - safe_sqrt(delta)) / (2 * A);
      double w2 = (-B + safe_sqrt(delta)) / (2 * A);
      res.push_back(l.s + w1 * (l.t - l.s));
      res.push_back(l.s + w2 * (l.t - l.s));
    }
    return res;
  }

  // 扇形面积 a->b
  double sector_area(const Point& a, const Point& b) const {
    double theta = atan2(a.y, a.x) - atan2(b.y, b.x);
    while (theta < 0) { theta += 2 * PI; }
    while (theta > 2 * PI) { theta -= 2 * PI; }
    theta = std::min(theta, 2 * PI - theta);
    return sgn(det(a, b)) * theta * r * r / 2.0;
  }

  // 与线段AB的交点计算面积 a->b
  double semicircle_area(const Point& a, const Point& b) const {
    std::vector<Point> p = circle_intersect_seg(*this, Line(a, b));
    bool ina = sgn((a - o).norm() - r) < 0;
    bool inb = sgn((b - o).norm() - r) < 0;
    if (ina) {
      if (inb) {
        return det(a - o, b - o) / 2;
      } else {
        return det(a - o, p[0] - o) / 2 + sector_area(p[0] - o, b - o);
      }
    } else {
      if (inb) {
        return det(p[0] - o, b - o) / 2 + sector_area(a - o, p[0] - o);
      } else {
        if (p.size() == 2) {
          return sector_area(a - o, p[0] - o) + sector_area(p[1] - o, b - o)
              + det(p[0] - o, p[1] - o) / 2;
        } else {
          return sector_area(a - o, b - o);
        }
      }
    }
  }

  // 圆与多边形交, 结果可以尝试+eps
  friend double circle_intersect_polygon(const Circle& c, const Polygon& a) {
    int n = a.p.size();
    double res = 0;
    for (int i = 0; i < n; i++) {
      if (sgn(det(a.p[i] - c.o, a.p[next(i)] - c.o)) == 0) { continue; }
      res += c.semicircle_area(a.p[i], a.p[next(i)]);
    }
    return res;
  }

  // 点在圆内, 不包含边界
  bool is_point_in(const Point& p) const {
    return sgn((p - o).norm() - r) < 0;
  }
};

// 三点求圆
Circle get_circle(const Point& p0, const Point& p1, const Point& p2) {
  double a1 = p1.x - p0.x, b1 = p1.y - p0.y, c1 = (a1 * a1 + b1 * b1) / 2;
  double a2 = p2.x - p0.x, b2 = p2.y - p0.y, c2 = (a2 * a2 + b2 * b2) / 2;
  double d = a1 * b2 - a2 * b1;
  Point o(p0.x + (c1 * b2 - c2 * b1) / d, p0.y + (a1 * c2 - a2 * c1) / d);
  return Circle(o, (o - p0).norm());
}

// 直径上两点求圆
Circle get_circle(const Point& p0, const Point& p1) {
  Point o((p0.x + p1.x) / 2, (p0.y + p1.y) / 2);
  return Circle(o, (o - p0).norm());
}

// 最小圆覆盖, 用之前可以随机化random_shuffle
Circle min_circle_cover(const std::vector<Point>& a) {
  int n = a.size();
  Circle c(a[0], 0);
  for (int i = 1; i < n; i++) {
    if (!c.is_point_in(a[i])) {
      c.o = a[i];
      c.r = 0;
      for (int j = 0; j < i; j++) {
        if (!c.is_point_in(a[j])) {
          c = get_circle(a[i], a[j]);
          for (int k = 0; k < j; k++) {
            if (!c.is_point_in(a[k])) { c = get_circle(a[i], a[j], a[k]); }
          }
        }
      }
    }
  }
  return c;
}
