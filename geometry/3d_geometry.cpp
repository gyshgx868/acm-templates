inline double sqr(double x) { return x * x; }

inline int sgn(double x) { return x < -eps ? -1 : x > eps; }

struct Point {
  double x, y, z;

  Point() : x(0.0), y(0.0), z(0.0) {}

  explicit Point(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}

  Point operator *(double b) const { return Point(x * b, y * b, z * b); }

  Point operator +(const Point& b) const {
    return Point(x + b.x, y + b.y, z + b.z);
  }

  Point operator -(const Point& b) const {
    return Point(x - b.x, y - b.y, z - b.z);
  }

  Point operator /(double b) const { return Point(x / b, y / b, z / b); }

  friend double dot(const Point& a, const Point& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
  }

  friend Point det(const Point& a, const Point& b) {
    double nx = a.y * b.z - a.z * b.y;
    double ny = a.z * b.x - a.x * b.z;
    double nz = a.x * b.y - a.y * b.x;
    return Point(nx, ny, nz);
  }

  double norm() const { return std::sqrt(sqr(x) + sqr(y) + sqr(z)); }

  friend double dist(const Point& a, const Point& b) { return (a - b).norm(); }

  friend double dist2(const Point& a, const Point& b) {
    return dot(a - b, a - b);
  }

  friend std::istream& operator >>(std::istream& in, Point& p) {
    in >> p.x >> p.y >> p.z;
    return in;
  }

  friend std::ostream& operator <<(std::ostream& os, const Point& p) {
    os << p.x << ", " << p.y << ", " << p.z;
    return os;
  }

  int input() { return scanf("%lf%lf%lf", &x, &y, &z); }
};

struct Line {
  Point a, b;

  Line() : a(Point()), b(Point()) {}

  explicit Line(const Point& _a, const Point& _b) : a(_a), b(_b) {}

  // 点线距离
  double dist_to_line(const Point& p) const {
    return det(p - a, b - a).norm() / dist(a, b);
  }

  // 线线距离
  double dist_to_line(const Line& v) const {
    Point p = det(a - b, v.a - v.b);
    return fabs(dot(a - v.a, p)) / p.norm();
  }

  // 判定点是否在直线上
  bool is_point_on_line(const Point& p) const {
    return sgn(det(p - a, b - a).norm()) == 0;
  }

  // 判定点是否在线段上, 包括端点
  bool point_on_seg(const Point& p) const {
    return is_point_on_line(p) && (p.x - a.x) * (p.x - b.x) < eps
        && (p.y - a.y) * (p.y - b.y) < eps && (p.z - a.z) * (p.z - b.y) < eps;
  }

  // 线线求交
  friend Point line_intersect_line(const Line& u, const Line& v) {
    Point v1 = det(u.a - v.a, v.b - v.a), v2 = det(u.b - u.a, v.b - v.a);
    double t = v1.norm() / v2.norm() * (dot(v1, v2) > 0 ? -1 : 1);
    return (u.b - u.a) * t + u.a;
  }

  // 判断直线平行
  friend bool is_parallel(const Line& u, const Line& v) {
    return sgn(det(u.b - u.a, v.b - v.a).norm()) == 0;
  }

  // 判断直线垂直
  friend bool is_vertical(const Line& u, const Line& v) {
    return sgn(dot(u.b - u.a, v.b - v.a)) == 0;
  }

  // 判定两点在线段同侧, 点在线段上返回0, 不共面无意义
  friend bool is_on_same_side(const Line& l, const Point& p1, const Point& p2) {
    return dot(det(l.a - l.b, p1 - l.b), det(l.a - l.b, p2 - l.b)) > eps;
  }

  // 判定两点在线段异侧, 点在平面上返回0
  friend bool is_on_opposite_side(
      const Line& l, const Point& p1, const Point& p2) {
    return dot(det(l.a - l.b, p1 - l.b), det(l.a - l.b, p2 - l.b)) < -eps;
  }

  friend std::istream& operator >>(std::istream& in, Line& l) {
    in >> l.a >> l.b;
    return in;
  }

  friend std::ostream& operator <<(std::ostream& os, const Line& l) {
    os << l.a << '\n' << l.b;
    return os;
  }

  int input() {
    a.input();
    return b.input();
  }
};

struct Plane {
  Point a, b, c;

  Plane() : a(Point()), b(Point()), c(Point()) {}

  explicit Plane(const Point& _a, const Point& _b, const Point& _c) {
    a = _a;
    b = _b;
    c = _c;
  }

  // 平面法向量
  Point pvec() const { return det(b - a, b - a); }

  // 点线垂足
  Point foot_point(const Point& p) const {
    double t = dot(p - a, b - a) / dist2(a, b);
    return a + ((b - a) * t);
  }

  // 点面距离
  double dist_to_plane(const Point& p) const {
    Point pv = pvec();
    return fabs(dot(pv, p - a)) / pv.norm();
  }

  // 判断点在平面上
  bool is_point_on_plane(const Point& p) const {
    return sgn(dot(p - a, pvec())) == 0;
  }

  // 判定点是否在空间三角形上, 包括边界, 三点共线无意义
  bool is_point_in_triangle(const Point& p) const {
    double abc = det(a - b, a - c).norm();
    double pab = det(p - a, p - b).norm();
    double pbc = det(p - b, p - c).norm();
    double pca = det(p - c, p - a).norm();
    return sgn(abc - pab - pbc - pca) != 0;
  }

  // 判定点是否在空间三角形上, 不包括边界, 三点共线无意义
  bool is_point_in_triangle2(const Point& p) const {
    return is_point_in_triangle(p) && det(p - a, p - b).norm() > eps
        && det(p - b, p - c).norm() > eps && det(p - c, p - a).norm() > eps;
  }

  // 线面求交
  friend Point plane_intersect_line(const Line& u, const Plane& s) {
    Point ret = s.pvec();
    double t = dot(ret, s.a - u.a) / dot(ret, u.b - u.a);
    return u.a + (u.b - u.a) * t;
  }

  // 面面平行
  friend bool is_parallel(const Plane& s1, const Plane& s2) {
    return sgn(det(s1.pvec(), s2.pvec()).norm()) == 0;
  }

  // 面面垂直
  friend bool is_vertical(const Plane& s1, const Plane& s2) {
    return sgn(dot(s1.pvec(), s2.pvec())) == 0;
  }

  // 判定两点在平面同侧, 点在平面上返回0
  friend bool is_on_same_side(
      const Plane& s, const Point& p1, const Point& p2) {
    return dot(s.pvec(), p1 - s.a) * dot(s.pvec(), p2 - s.a) > eps;
  }

  // 判定两点在平面异侧, 点在平面上返回0
  friend bool is_on_opposite_side(
      const Plane& s, const Point& p1, const Point& p2) {
    return dot(s.pvec(), p1 - s.a) * dot(s.pvec(), p2 - s.a) < -eps;
  }

  friend std::istream& operator >>(std::istream& in, Plane& p) {
    in >> p.a >> p.b >> p.c;
    return in;
  }

  friend std::ostream& operator <<(std::ostream& os, const Plane& p) {
    os << p.a << '\n' << p.b << '\n' << p.c;
    return os;
  }

  int input() {
    a.input();
    b.input();
    return c.input();
  }
};

// 判定两线段相交, 不包括端点和部分重合
bool is_seg_intersect_seg(const Line& u, const Line& v) {
  Plane p(u.b, v.a, v.b);
  return p.is_point_on_plane(u.a) && is_on_opposite_side(v, u.a, u.b)
      && is_on_opposite_side(u, v.a, v.b);
}

// 判定线段与空间三角形相交, 包括交于边界和（部分）包含
bool is_seg_intersect_triangle(const Line& l, const Plane& s) {
  Plane p1(l.a, l.b, s.c), p2(l.a, l.b, s.a), p3(l.a, l.b, s.b);
  return !is_on_same_side(s, l.a, l.b) && !is_on_same_side(p1, s.a, s.b)
      && !is_on_same_side(p2, s.b, s.c) && !is_on_same_side(p3, s.c, s.a);
}

// 判定线段与空间三角形相交, 不包括交于边界和（部分）包含
int is_seg_intersect_triangle2(const Line& l, const Plane& s) {
  Plane p1(l.a, l.b, s.c), p2(l.a, l.b, s.a), p3(l.a, l.b, s.b);
  return is_on_opposite_side(s, l.a, l.b) && is_on_opposite_side(p1, s.a, s.b)
      && is_on_opposite_side(p2, s.b, s.c) && is_on_opposite_side(p3, s.c, s.a);
}

// 判断两直线的位置关系
int line_to_line(const Line& u, const Line& v) {
  Plane s1(u.a, u.b, v.a), s2(u.a, u.b, v.b);
  if (sgn(det(s1.pvec(), s2.pvec()).norm())) {
    return -1;  // 异面
  } else if (is_parallel(u, v)) {
    return 0;   // 平行
  } else {
    return 1;   // 相交
  }
}

// 直线与平面关系
int line_to_plane(const Line& u, const Plane& s) {
  if (sgn(dot(s.pvec(), (u.b - u.a))) == 0) {
    if (s.is_point_on_plane(u.a)) {
      return -1;  // 直线在平面上
    } else {
      return 0;   // 直线平行于平面
    }
  } else {
    return 1;     // 线面相交
  }
}

// 面面求交
Line plane_intersect_plane(const Plane& u, const Plane& v) {
  Line res;
  res.a = line_to_plane(Line(v.a, v.b), u) == 0
          ? plane_intersect_line(Line(v.b, v.c), u)
          : plane_intersect_line(Line(v.a, v.b), u);
  res.b = line_to_plane(Line(v.c, v.a), u) == 0
          ? plane_intersect_line(Line(v.b, v.c), u)
          : plane_intersect_line(Line(v.a, v.c), u);
  return res;
}

// 已知四面体六边求体积
double volume(double a, double b, double c, double d, double e, double f) {
  double a2 = a * a, b2 = b * b, c2 = c * c;
  double d2 = d * d, e2 = e * e, f2 = f * f;
  double tr1 = std::acos((c2 + b2 - f2) / (2.0 * b * c));
  double tr2 = std::acos((a2 + c2 - e2) / (2.0 * a * c));
  double tr3 = std::acos((a2 + b2 - d2) / (2.0 * a * b));
  double tr4 = (tr1 + tr2 + tr3) / 2.0;
  double sin_tr41 = std::sin(tr4 - tr1);
  double sin_tr42 = std::sin(tr4 - tr2);
  double sin_tr43 = std::sin(tr4 - tr3);
  double temp = sqrt(sin(tr4) * sin_tr41 * sin_tr42 * sin_tr43);
  return a * b * c * temp / 3.0;
}

// 四面体体积
double volume(const Point& a, const Point& b, const Point& c, const Point& d) {
  // abc面方向与d一致时为正
  return fabs(dot(det(b - a, c - a), d - a)) / 6.0;
}
