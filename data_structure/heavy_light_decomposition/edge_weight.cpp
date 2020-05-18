template <class T>
class HeavyLightDecomposition : public Graph<T> {
 public:
  explicit HeavyLightDecomposition(int n) : Graph<T>(n) {
    top.resize(n);
    parent.resize(n);
    depth.resize(n);
    quantities.resize(n);
    position.resize(n);
    heavy_child.resize(n, -1);
    cur_pos = 0;
  }

  void add_undirected_edge(int u, int v, T w = T()) {
    Graph<T>::add_undirected_edge(u, v, w);
    edges.push_back(Edge<T>(u, v, w));
  }

  void initialize() {
    dfs1(0, -1, 0);
    dfs2(0, 0);
    int n = this->num_vertices;
    tree.resize(n * 4);
    init_tree(0, 0, n - 1);
    for (int i = 0; i < edges.size(); i++) {
      Edge<T>& e = edges[i];
      if (depth[e.from] > depth[e.to]) { std::swap(e.from, e.to); }
      update(0, 0, n - 1, position[e.to], position[e.to], e.weight);
    }
  }

  // 查询 u->v 边权的值
  T get(int u, int v) const {
    T res = std::numeric_limits<T>::min();
    int r = this->num_vertices - 1;
    while (top[u] != top[v]) {
      if (depth[top[u]] < depth[top[v]]) { std::swap(u, v); }
      res = std::max(res, query(0, 0, r, position[top[u]], position[u]));
      u = parent[top[u]];
    }
    if (u == v) { return res; }
    if (depth[u] > depth[v]) { std::swap(u, v); }
    res = std::max(res, query(0, 0, r, position[heavy_child[u]], position[v]));
    return res;
  }

  void update(int at, T w) {
    int from = position[edges[at].to], to = position[edges[at].to];
    update(0, 0, this->num_vertices - 1, from, to, w);
  }

 private:
  std::vector<int> top;
  std::vector<int> parent;
  std::vector<int> depth;
  std::vector<int> quantities;
  std::vector<int> position;
  std::vector<int> heavy_child;
  std::vector<Edge<T> > edges;
  std::vector<T> tree;
  int cur_pos;

  void init_tree(int root, int left, int right) {
    if (left == right) {
      tree[root] = std::numeric_limits<T>::min();
    } else {
      int middle = (left + right) / 2;
      init_tree(2 * root + 1, left, middle);
      init_tree(2 * root + 2, middle + 1, right);
      tree[root] = std::max(tree[2 * root + 1], tree[2 * root + 2]);
    }
  }

  void update(int root, int left, int right, int from, int to, T delta) {
    if (left > to || right < from) { return; }
    if (left >= from && right <= to) {
      tree[root] = delta;
      return;
    }
    int middle = (left + right) / 2;
    update(2 * root + 1, left, middle, from, to, delta);
    update(2 * root + 2, middle + 1, right, from, to, delta);
    tree[root] = std::max(tree[2 * root + 1], tree[2 * root + 2]);
  }

  T query(int root, int left, int right, int from, int to) const {
    if (left > to || right < from) { return std::numeric_limits<T>::min(); }
    if (left >= from && right <= to) { return tree[root]; }
    int middle = (left + right) / 2;
    T left_result = query(2 * root + 1, left, middle, from, to);
    T right_result = query(2 * root + 2, middle + 1, right, from, to);
    return std::max(left_result, right_result);
  }

  void dfs1(int u, int pre, int dep) {
    depth[u] = dep;
    parent[u] = pre;
    quantities[u] = 1;
    for (int i = this->head[u]; i != -1; i = this->next[i]) {
      int v = this->to[i];
      if (v != pre) {
        dfs1(v, u, dep + 1);
        quantities[u] += quantities[v];
        if (heavy_child[u] == -1
            || quantities[v] > quantities[heavy_child[u]]) {
          heavy_child[u] = v;
        }
      }
    }
  }

  void dfs2(int u, int top_vertex) {
    top[u] = top_vertex;
    position[u] = cur_pos++;
    if (heavy_child[u] == -1) {
      return;
    }
    dfs2(heavy_child[u], top_vertex);
    for (int i = this->head[u]; i != -1; i = this->next[i]) {
      int v = this->to[i];
      if (v != heavy_child[u] && v != parent[u]) { dfs2(v, v); }
    }
  }
};
