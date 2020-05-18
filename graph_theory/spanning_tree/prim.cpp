template <class T>
class Prim {
 public:
  explicit Prim(int n) {
    graph.resize(n, std::vector<T>(n, std::numeric_limits<T>::max()));
    vis.resize(n);
    pre.resize(n);
  }

  void add_edge(int u, int v, T w = T()) {
    graph[u][v] = std::min(graph[u][v], w);
  }

  void add_undirected_edge(int u, int v, T w = T()) {
    add_edge(u, v, w);
    add_edge(v, u, w);
  }

  T get_mst(int src = 0) {
    T value = T();
    std::fill(vis.begin(), vis.end(), 0);
    std::fill(pre.begin(), pre.end(), -1);
    std::vector<T> dist(graph.size(), std::numeric_limits<T>::max());
    dist[src] = T();
    while (true) {
      int u = -1, min_d = std::numeric_limits<T>::max();
      for (int i = 0; i < graph.size(); i++) {
        if (vis[i] == 0 && dist[i] < min_d) {
          min_d = dist[i];
          u = i;
        }
      }
      if (u == -1) { break; }
      vis[u] = 1;
      value += dist[u];
      for (int v = 0; v < graph.size(); v++) {
        if (vis[v] == 0 && graph[u][v] < dist[v]) {
          dist[v] = graph[u][v];
          pre[v] = u;
        }
      }
    }
    return value;
  }

  bool is_valid() const {
    int res = 0;
    for (int i = 0; i < graph.size(); i++) { res += vis[i]; }
    return res == graph.size();
  }

  std::vector<int> get_path(int src, int dest) const {
    std::stack<int> path;
    if (pre[dest] != -1) {
      while (dest != src) {
        path.push(dest);
        dest = pre[dest];
      }
      path.push(dest);
    } else {
      path.push(-1);
    }
    std::vector<int> res;
    while (!path.empty()) {
      res.push_back(path.top());
      path.pop();
    }
    return res;
  }

 private:
  std::vector<std::vector<T> > graph;
  std::vector<int> vis;
  std::vector<int> pre;
};
