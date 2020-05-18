template <class T>
class Edmonds {
 public:
  explicit Edmonds(int n) {
    num_vertices = n;
    pre.resize(num_vertices);
    id.resize(num_vertices);
    vis.resize(num_vertices);
    in.resize(num_vertices);
  }

  void add_edge(int u, int v, T w = T()) {
    edges.push_back(Edge<T>(u, v, w));
  }

  T get_mst(int root = 0) {
    T value = T();
    while (true) {
      std::fill(in.begin(), in.end(), std::numeric_limits<T>::max());
      for (int i = 0; i < edges.size(); i++) {
        int u = edges[i].from;
        int v = edges[i].to;
        if (edges[i].weight < in[v] && u != v) {
          pre[v] = u;
          in[v] = edges[i].weight;
        }
      }
      for (int i = 0; i < num_vertices; i++) {
        if (i == root) { continue; }
        if (in[i] == std::numeric_limits<T>::max()) {
          return -1;
        }
      }
      int node_count = 0;
      std::fill(id.begin(), id.end(), -1);
      std::fill(vis.begin(), vis.end(), -1);
      in[root] = 0;
      for (int i = 0; i < num_vertices; i++) {
        value += in[i];
        int v = i;
        while (vis[v] != i && id[v] == -1 && v != root) {
          vis[v] = i;
          v = pre[v];
        }
        if (v != root && id[v] == -1) {
          for (int u = pre[v]; u != v; u = pre[u]) { id[u] = node_count; }
          id[v] = node_count++;
        }
      }
      if (node_count == 0) { break; }
      for (int i = 0; i < num_vertices; i++) {
        if (id[i] == -1) { id[i] = node_count++; }
      }
      for (int i = 0; i < edges.size(); i++) {
        int v = edges[i].to;
        edges[i].from = id[edges[i].from];
        edges[i].to = id[edges[i].to];
        if (edges[i].from != edges[i].to) { edges[i].weight -= in[v]; }
      }
      num_vertices = node_count;
      root = id[root];
    }
    return value;
  }

 private:
  int num_vertices;
  std::vector<Edge<T> > edges;
  std::vector<int> pre;
  std::vector<int> id;
  std::vector<int> vis;
  std::vector<T> in;
};
