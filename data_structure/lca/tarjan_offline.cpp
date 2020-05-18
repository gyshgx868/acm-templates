template <class T>
class Tarjan : public Graph<T> {
 public:
  explicit Tarjan(int n) : Graph<T>(n), ds(n) {
    vis.resize(n, 0);
    ancestor.resize(n);
    dist.resize(n);
    query_head.resize(n, -1);
  }

  void add_query(int u, int v, int query_id) {
    query_to.push_back(v);
    query_next.push_back(query_head[u]);
    query_index.push_back(query_id);
    query_head[u] = query_to.size() - 1;
    // reverse
    query_to.push_back(u);
    query_next.push_back(query_head[v]);
    query_index.push_back(query_id);
    query_head[v] = query_to.size() - 1;
  }

  void process_all_queries() {
    lca.resize(query_to.size() / 2);
    lca_dist.resize(query_to.size() / 2);
    tarjan(0, T());
  }

  std::vector<int> get_lca() const { return lca; }

  std::vector<T> get_lca_dist() const { return lca_dist; }

 private:
  DisjointSet ds;
  std::vector<int> vis;
  std::vector<int> ancestor;
  std::vector<T> dist;
  std::vector<int> query_to;
  std::vector<int> query_head;
  std::vector<int> query_next;
  std::vector<int> query_index;

  std::vector<int> lca;
  std::vector<T> lca_dist;

  void tarjan(int u, T w) {
    dist[u] = w;
    ancestor[u] = u;
    vis[u] = 1;
    for (int i = this->head[u]; i != -1; i = this->next[i]) {
      int v = this->to[i];
      if (vis[v] == 1) { continue; }
      tarjan(v, w + this->weights[i]);
      ds.join(u, v);
      ancestor[ds.get(u)] = u;
    }
    for (int i = query_head[u]; i != -1; i = query_next[i]) {
      int v = query_to[i];
      if (vis[v] == 0) { continue; }
      int id = query_index[i];
      lca[id] = ancestor[ds.get(v)];
      lca_dist[id] = dist[u] + dist[v] - 2 * dist[lca[id]];
    }
  }
};
