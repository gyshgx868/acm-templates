template <class T>
class KDTree {
  typedef std::vector<T> point;

 public:
  explicit KDTree(int dim) { max_dims = dim; }

  void initialize() {
    tree.resize(points.size() * 4);
    son.resize(points.size() * 4);
    build(0, 0, points.size() - 1);
  }

  void add_point(const point& l) { points.push_back(l); }

  std::vector<point> query_k_nearest(const point& p, int k) const {
    std::priority_queue<std::pair<T, point> > que;
    query(p, k, que, 0, 0);
    std::vector<point> res;
    while (!que.empty()) {
      res.push_back(que.top().second);
      que.pop();
    }
    std::reverse(res.begin(), res.end());
    return res;
  }

  T query_nearest_dist(const point& p) const {
    std::vector<point> neighbors = query_k_nearest(p, 2);
    if (p != neighbors[0]) { return get_dist(neighbors[0], p); }
    return get_dist(neighbors[1], p);
  }

 private:
  int max_dims;
  std::vector<point> points;
  std::vector<point> tree;
  std::vector<int> son;

  inline T get_dist(const point& a, const point& b) const {
    T res = T();
    for (int i = 0; i < max_dims; i++) {
      res += (a[i] - b[i]) * (a[i] - b[i]);
    }
    return res;
  }

  void build(int root, int left, int right, int depth = 0) {
    if (left > right) { return; }
    son[root] = right - left;
    son[root * 2 + 1] = son[root * 2 + 2] = -1;
    int mid = (left + right) / 2;
    auto comp = [&](const point& a, const point& b) {
      return a[depth % max_dims] < b[depth % max_dims];
    };
    std::nth_element(
        points.begin() + left, points.begin() + mid,
        points.begin() + right + 1, comp);
    tree[root] = points[mid];
    build(root * 2 + 1, left, mid - 1, depth + 1);
    build(root * 2 + 2, mid + 1, right, depth + 1);
  }

  void query(
      const point& p, int m, std::priority_queue<std::pair<T, point> >& que,
      int root = 0, int depth = 0) const {
    if (son[root] == -1) { return; }
    std::pair<T, point> cur(get_dist(tree[root], p), tree[root]);
    int dim = depth % max_dims;
    int left = root * 2 + 1, right = root * 2 + 2, fg = 0;
    if (p[dim] >= tree[root][dim]) { std::swap(left, right); }
    if (son[left] != -1) { query(p, m, que, left, depth + 1); }
    bool need_right = false;
    if (que.size() < m) {
      que.push(cur);
      need_right = true;
    } else {
      if (cur.first < que.top().first) {
        que.pop();
        que.push(cur);
      }
      T dist = (p[dim] - tree[root][dim]) * (p[dim] - tree[root][dim]);
      if (dist < que.top().first) { need_right = true; }
    }
    if (son[right] != -1 && need_right) { query(p, m, que, right, depth + 1); }
  }
};
