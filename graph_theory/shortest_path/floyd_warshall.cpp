template <class T>
class FloydWarshall {
 public:
  explicit FloydWarshall(int n) {
    dist.resize(n, std::vector<T>(n, std::numeric_limits<T>::max()));
    for (int i = 0; i < n; i++) { dist[i][i] = T(); }
    path.resize(n, std::vector<int>(n));
  }

  void add_edge(int u, int v, T w = T()) {
    dist[u][v] = std::min(dist[u][v], w);
  }

  void add_undirected_edge(int u, int v, T w = T()) {
    add_edge(u, v, w);
    add_edge(v, u, w);
  }

  void floyd() {
    for (int k = 0; k < dist.size(); k++) {
      for (int i = 0; i < dist.size(); i++) {
        for (int j = 0; j < dist.size(); j++) {
          if (dist[i][k] == std::numeric_limits<T>::max()) { continue; }
          if (dist[k][j] == std::numeric_limits<T>::max()) { continue; }
          if (dist[i][k] + dist[k][j] < dist[i][j]) {
            dist[i][j] = dist[i][k] + dist[k][j];
            path[i][j] = path[i][k];
          }
        }
      }
    }
  }

  const std::vector<T>& operator [](int from) const { return dist[from]; }

  std::vector<int> get_path(int u, int v) const {
    std::vector<int> res;
    int from = u;
    res.push_back(from);
    while (from != v) {
      res.push_back(path[from][v]);
      from = path[from][v];
    }
    return res;
  }

 private:
  std::vector<std::vector<T> > dist;
  std::vector<std::vector<int> > path;
};
