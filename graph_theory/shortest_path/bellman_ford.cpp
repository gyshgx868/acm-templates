template <class T>
class BellmanFord {
 public:
  explicit BellmanFord(int n) {
    num_vertices = n;
    dist.resize(num_vertices);
  }

  void add_edge(int u, int v, T w = T()) {
    edges.push_back(Edge<T>(u, v, w));
  }

  void add_undirected_edge(int u, int v, T w = T()) {
    add_edge(u, v, w);
    add_edge(v, u, w);
  }

  bool bellman_ford(int src = 0) {
    std::fill(dist.begin(), dist.end(), std::numeric_limits<T>::max());
    dist[src] = T();
    for (int k = 0; k < num_vertices - 1; k++) {
      for (int i = 0; i < edges.size(); i++) { // 检查每条边
        int x = edges[i].from, y = edges[i].to;
        if (dist[x] != std::numeric_limits<T>::max()) {
          dist[y] = std::min(dist[y], dist[x] + edges[i].weight);
        }
      }
    }
    // 检查负环: 如果全部松弛之后还能松弛, 说明一定有负环
    for (int i = 0; i < edges.size(); i++) {
      int x = edges[i].from, y = edges[i].to;
      if (dist[x] != std::numeric_limits<T>::max()) {
        if (dist[y] > dist[x] + edges[i].weight) { return false; }
      }
    }
    return true;
  }

  T operator [](int dest) const { return dist[dest]; }

 private:
  int num_vertices;
  std::vector<Edge<T> > edges;
  std::vector<T> dist;
};
