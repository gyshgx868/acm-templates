template <class T>
class Kruskal {
 public:
  explicit Kruskal(int n) : ds(n) {}

  void add_edge(int u, int v, T w = T()) {
    edges.push_back(Edge<T>(u, v, w));
  }

  void add_undirected_edge(int u, int v, T w = T()) {
    add_edge(u, v, w);
    add_edge(v, u, w);
  }

  T get_mst() {
    T value = T();
    ds.clear();
    std::sort(edges.begin(), edges.end());
    for (int i = 0; i < edges.size(); i++) {
      if (ds.get(edges[i].from) != ds.get(edges[i].to)) {
        ds.join(edges[i].from, edges[i].to);
        value += edges[i].weight;
      }
    }
    return value;
  }

  bool is_valid() const { return ds.get_set_count() == 1; }

 private:
  std::vector<Edge<T> > edges;
  DisjointSet ds;
};
