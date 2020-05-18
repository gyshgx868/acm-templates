std::vector<Point> p;

bool cmp_x(const Point &a, const Point &b) { return a.x < b.x; }

bool cmp_y(int a, int b) { return p[a].y < p[b].y; }

double closest_pair(int from, int to) {
  if (to - from == 2) { return dist(p[from], p[from + 1]); }
  if (to - from == 3) {
    double d1 = dist(p[from], p[from + 1]);
    double d2 = dist(p[from + 1], p[from + 2]);
    double d3 = dist(p[from + 2], p[from + 3]);
    return std::min(d1, std::min(d2, d3));
  }
  int mid = (from + to) / 2;
  double left = closest_pair(from, mid);
  double right = closest_pair(mid, to);
  double res = std::min(left, right);
  std::vector<int> id;
  for (int i = from; i < to; i++) {
    if (p[i].x >= p[mid].x - res && p[i].x <= p[mid].x + res) {
      id.push_back(i);
    }
  }
  std::sort(id.begin(), id.end(), cmp_y);
  for (int i = 0; i < id.size(); i++) {
    for (int j = i + 1; j < id.size(); j++) {
      if (p[id[j]].y - p[id[i]].y >= res) { break; }
      res = std::min(res, dist(p[id[i]], p[id[j]]));
    }
  }
  return res;
}

double solve(int n) {
  p.resize(n);
  for (int i = 0; i < n; i++) { p[i].input(); }
  std::sort(p.begin(), p.end(), cmp_x);
  return closest_pair(0, n);
}
