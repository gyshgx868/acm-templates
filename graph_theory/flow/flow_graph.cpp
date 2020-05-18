template <class T>
class FlowGraph {
 public:
  int num_vertices;

  explicit FlowGraph(int n) {
    num_vertices = n;
    head.resize(n, -1);
  }

  void add_edge(int u, int v, T cap) {
    to.push_back(v);
    next.push_back(head[u]);
    capacity.push_back(cap);
    head[u] = to.size() - 1;
  }

  void add_flow_edge(int u, int v, T cap) {
    add_edge(u, v, cap);
    add_edge(v, u, T());
  }

  int first_out_bound(int u) const { return head[u]; }

  int next_out_bound(int v) const { return next[v]; }

  int dest(int v) const { return to[v]; }

  T get_capacity(int v) const { return capacity[v]; }

  void push_flow(int v, T delta) { capacity[v] += delta; }

  std::vector<int> get_head() const { return head; }

 protected:
  std::vector<int> head;
  std::vector<int> to;
  std::vector<int> next;
  std::vector<T> capacity;
};
