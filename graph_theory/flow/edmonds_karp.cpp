template <class T>
T edmonds_karp(FlowGraph<T>& g, int src, int dest) {
  T max_flow = T();
  std::vector<int> cur(g.num_vertices);
  while (true) {
    std::vector<int> pre(g.num_vertices, -1);
    std::queue<int> que;
    que.push(src);
    while (!que.empty()) {
      int u = que.front();
      que.pop();
      for (int i = g.first_out_bound(u); i != -1; i = g.next_out_bound(i)) {
        int v = g.dest(i);
        if (pre[v] == -1 && g.get_capacity(i) > T()) {
          pre[v] = u;
          cur[v] = i;
          que.push(v);
        }
      }
      if (pre[dest] != -1) { break; }
    }
    if (pre[dest] == -1) { break; }
    T aug = std::numeric_limits<T>::max();
    for (int v = dest; v != src; v = pre[v]) {
      aug = std::min(aug, g.get_capacity(cur[v]));
    }
    for (int v = dest; v != src; v = pre[v]) {
      g.push_flow(cur[v], -aug);
      g.push_flow(cur[v] ^ 1, aug);
    }
    max_flow += aug;
  }
  return max_flow;
}
