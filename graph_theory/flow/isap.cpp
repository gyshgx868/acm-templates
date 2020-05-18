template <class T>
T isap(FlowGraph<T>& g, int src, int dest) {
  std::vector<int> gap(g.num_vertices, 0);
  std::vector<int> dep(g.num_vertices, 0);
  std::vector<int> cur = g.get_head();
  std::vector<int> pre(g.num_vertices);
  int u = src;
  pre[u] = -1;
  gap[0] = g.num_vertices;
  T max_flow = T();
  while (dep[src] < g.num_vertices) {
    if (u == dest) {
      T min_flow = std::numeric_limits<T>::max();
      for (int i = pre[u]; i != -1; i = pre[g.dest(i ^ 1)]) {
        min_flow = std::min(min_flow, g.get_capacity(i));
      }
      for (int i = pre[u]; i != -1; i = pre[g.dest(i ^ 1)]) {
        g.push_flow(i, -min_flow);
        g.push_flow(i ^ 1, min_flow);
      }
      u = src;
      max_flow += min_flow;
      continue;
    }
    bool flag = false;
    for (int i = cur[u]; i != -1; i = g.next_out_bound(i)) {
      int v = g.dest(i);
      if (g.get_capacity(i) > T() && dep[v] + 1 == dep[u]) {
        flag = true;
        cur[u] = pre[v] = i;
        u = v;
        break;
      }
    }
    if (flag) { continue; }
    int min_dep = g.num_vertices;
    for (int i = g.first_out_bound(u); i != -1; i = g.next_out_bound(i)) {
      if (g.get_capacity(i) > T() && dep[g.dest(i)] < min_dep) {
        min_dep = dep[g.dest(i)];
        cur[u] = i;
      }
    }
    gap[dep[u]]--;
    if (gap[dep[u]] == 0) { return max_flow; }
    dep[u] = min_dep + 1;
    gap[dep[u]]++;
    if (u != src) { u = g.dest(pre[u] ^ 1); }
  }
  return max_flow;
}
