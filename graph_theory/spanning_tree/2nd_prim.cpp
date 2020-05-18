template <class T>
class Prim {
 public:
  T first_value, second_value;

  explicit Prim(const std::vector<std::vector<T> >& graph, int s, T inf) {
    num_vertices = graph.size();
    source = s;
    max_weight = inf;
    first_value = T();
    second_value = max_weight;
    pre.resize(num_vertices, -1);
    used.resize(num_vertices, std::vector<int>(num_vertices, 0));
    max_d.resize(num_vertices, std::vector<T>(num_vertices, 0));
    for (int i = 0; i < num_vertices; i++) {
      for (int j = i + 1; j < num_vertices; j++) {
        if (graph[i][j] != max_weight) {  // 浮点数时注意比较方式
          used[i][j] = 1;
        }
      }
    }
    prim(graph, source);
    prim2nd(graph);
  }

 private:
  int num_vertices;
  int source;
  T max_weight;
  std::vector<int> pre;
  std::vector<std::vector<int> > used;
  std::vector<std::vector<T> > max_d;

  void prim(const std::vector<std::vector<T> >& g, int s) {
    std::vector<int> vis(num_vertices, 0);
    std::vector<T> dist(num_vertices, max_weight);
    dist[s] = T();
    while (true) {
      int u = -1, min_d = max_weight;
      for (int i = 0; i < num_vertices; i++) {
        if (vis[i] == 0 && dist[i] < min_d) {
          min_d = dist[i];
          u = i;
        }
      }
      if (u == -1) { break; }
      if (pre[u] != -1) {
        used[pre[u]][u] = 2;
        used[u][pre[u]] = 2;
        for (int j = 0; j < num_vertices; j++) {
          if (vis[j] == 1) {
            max_d[j][u] = std::max(max_d[j][pre[u]], g[pre[u]][u]);
          }
        }
      }
      vis[u] = 1;
      first_value += dist[u];
      for (int v = 0; v < num_vertices; v++) {
        if (vis[v] == 0 && g[u][v] < dist[v]) {
          dist[v] = g[u][v];
          pre[v] = u;
        }
      }
    }
  }

  void prim2nd(const std::vector<std::vector<T> >& g) {
    for (int i = 0; i < num_vertices; i++) {
      for (int j = 0; j < num_vertices; j++) {
        if (used[i][j] == 1) {
          T val = first_value + g[i][j] - max_d[i][j];
          second_value = std::min(second_value, val);
        }
      }
    }
  }
};
