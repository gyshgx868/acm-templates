template <class T>
class LCA : public Graph<T> {  // 0-indexed
 public:
  explicit LCA(int n) : Graph<T>(n) {
    vis.resize(n);
    depth.resize(n);
    dist.resize(n);
    parent.resize(std::log2(n) + 1, std::vector<int>(n, -1));
  }

  void initialize(int root = 0) {
    bfs(root);
    for (int j = 1; 1 << j < this->num_vertices; j++) {
      for (int i = 0; i < this->num_vertices; i++) {
        if (parent[j - 1][i] != -1) {
          parent[j][i] = parent[j - 1][parent[j - 1][i]];
        }
      }
    }
  }

  int get_lca(int x, int y) const {
    if (depth[x] > depth[y]) { std::swap(x, y); }
    for (int i = parent.size() - 1; i >= 0; i--) {
      if ((depth[y] - depth[x]) >> i & 1) { y = parent[i][y]; }
    }
    if (x == y) { return y; }
    for (int i = parent.size() - 1; i >= 0; i--) {
      if (parent[i][x] != parent[i][y]) {
        x = parent[i][x];
        y = parent[i][y];
      }
    }
    return parent[0][x];
  }

  int get_dist(int u, int v) const {
    return dist[u] + dist[v] - 2 * dist[get_lca(u, v)];
  }

 private:
  std::vector<int> vis;
  std::vector<int> depth;
  std::vector<T> dist;
  std::vector<std::vector<int> > parent;

  void bfs(int root) {
    std::fill(vis.begin(), vis.end(), 0);
    std::fill(dist.begin(), dist.end(), 0);
    std::queue<int> q;
    q.push(root);
    parent[0][root] = 0;
    depth[root] = 1;
    vis[root] = 1;
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      for (int i = this->head[u]; i != -1; i = this->next[i]) {
        int v = this->to[i];
        if (vis[v] == 0) {
          depth[v] = depth[u] + 1;
          dist[v] = dist[u] + this->weights[i];
          parent[0][v] = u;
          vis[v] = 1;
          q.push(v);
        }
      }
    }
  }
};
