template <class T>
class HeavyLightDecomposition : public Graph<T> {
 public:
  explicit HeavyLightDecomposition(int n) : Graph<T>(n) {
    point_weight.resize(n);
    tree.initialize(n);
    top.resize(n);
    parent.resize(n);
    depth.resize(n);
    quantities.resize(n);
    position.resize(n);
    heavy_child.resize(n, -1);
    cur_pos = 0;
  }

  void initialize() {
    dfs1(0, -1, 0);
    dfs2(0, 0);
    for (int i = 0; i < this->num_vertices; i++) {
      tree.add(position[i], point_weight[i]);
      tree.add(position[i] + 1, -point_weight[i]);
    }
  }

  void set_vertex_weight(int at, T val) { point_weight[at] = val; }

  T get(int at) const { return tree.get(position[at]); }

  // u->v 的路径上点的值改变 delta
  void update(int u, int v, T delta) {
    int f1 = top[u], f2 = top[v];
    while (f1 != f2) {
      if (depth[f1] < depth[f2]) {
        std::swap(f1, f2);
        std::swap(u, v);
      }
      tree.add(position[f1], delta);
      tree.add(position[u] + 1, -delta);
      u = parent[f1];
      f1 = top[u];
    }
    if (depth[u] > depth[v]) { std::swap(u, v); }
    tree.add(position[u], delta);
    tree.add(position[v] + 1, -delta);
  }

 private:
  std::vector<T> point_weight;
  FenwickTree<T> tree;
  std::vector<int> top;
  std::vector<int> parent;
  std::vector<int> depth;
  std::vector<int> quantities;
  std::vector<int> position;
  std::vector<int> heavy_child;
  int cur_pos;

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
    if (heavy_child[u] == -1) { return; }
    dfs2(heavy_child[u], top_vertex);
    for (int i = this->head[u]; i != -1; i = this->next[i]) {
      int v = this->to[i];
      if (v != heavy_child[u] && v != parent[u]) { dfs2(v, v); }
    }
  }
};
