template <class T>
class LCA : public Graph<T> {
 public:
  explicit LCA(int n) : Graph<T>(n) {
    vis.resize(n, 0);
    dist.resize(n, T());
    first_appear_id.resize(n);
    f.resize(n * 2, std::vector<int>(std::log2(n * 2) + 1));
    euler.resize(n * 2);
    depth.resize(n * 2);
    num_nodes = 0;
  }

  void initialize(int root = 0) {
    dfs(root, 1);
    init_sparse_table();
  }

  int get_lca(int u, int v) const {
    int from = first_appear_id[u], to = first_appear_id[v];
    if (from > to) { std::swap(from, to); }
    return euler[query(from, to)];
  }

  T get_dist(int u, int v) const {
    return dist[u] + dist[v] - 2 * dist[get_lca(u, v)];
  }

 private:
  std::vector<int> vis;
  std::vector<T> dist;
  std::vector<int> first_appear_id;
  std::vector<std::vector<int> > f;
  std::vector<int> euler;
  std::vector<int> depth;
  int num_nodes;

  void dfs(int u, int dep) {
    euler[num_nodes] = u;
    depth[num_nodes] = dep;
    first_appear_id[u] = num_nodes++;
    vis[u] = 1;
    for (int i = this->head[u]; i != -1; i = this->next[i]) {
      int v = this->to[i];
      if (vis[v] == 0) {
        T w = this->weights[i];
        dist[v] = dist[u] + w;
        dfs(v, dep + 1);
        euler[num_nodes] = u;
        depth[num_nodes++] = dep;
      }
    }
  }

  void init_sparse_table() {
    for (int i = 1; i <= num_nodes; i++) { f[i][0] = i; }
    int k = std::log2(num_nodes);
    for (int j = 1; j <= k; j++) {
      for (int i = 1; i + (1 << j) - 1 <= num_nodes; i++) {
        int a = f[i][j - 1], b = f[i + (1 << (j - 1))][j - 1];
        f[i][j] = depth[a] < depth[b] ? a : b;
      }
    }
  }

  int query(int from, int to) const {
    int k = std::log2(to - from + 1);
    int a = f[from][k], b = f[to - (1 << k) + 1][k];
    return depth[a] < depth[b] ? a : b;
  }
};
