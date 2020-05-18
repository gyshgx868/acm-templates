template <class T>
class CostFlowGraph {
 public:
  int num_vertices;

  explicit CostFlowGraph(int n) {
    num_vertices = n;
    head.resize(n, -1);
  }

  void add_edge(int u, int v, T cap, T w) {
    from.push_back(u);
    to.push_back(v);
    next.push_back(head[u]);
    capacity.push_back(cap);
    cost.push_back(w);
    head[u] = to.size() - 1;
  }

  void add_flow_edge(int u, int v, T cap, T w) {
    add_edge(u, v, cap, w);
    add_edge(v, u, T(), -w);
  }

  int first_out_bound(int u) const { return head[u]; }

  int next_out_bound(int v) const { return next[v]; }

  int src(int v) const { return from[v]; }

  int dest(int v) const { return to[v]; }

  T get_capacity(int v) const { return capacity[v]; }

  T get_cost(int v) const { return cost[v]; }

  void push_flow(int v, T delta) { capacity[v] += delta; }

  std::vector<int> get_head() const { return head; }

 protected:
  std::vector<int> head;
  std::vector<int> from;
  std::vector<int> to;
  std::vector<int> next;
  std::vector<T> capacity;
  std::vector<T> cost;
};
