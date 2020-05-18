template <class T>
bool dfs(const Graph<T>& g, int u, std::vector<int>& state) {
  state[u] = 1;
  for (int i = g.first_out_bound(u); i != -1; i = g.next_out_bound(i)) {
    int v = g.dest(i);
    if (state[v] == 1 || !dfs(g, v, state)) { return false; }
  }
  state[u] = 2;
  return true;
}

template <class T>
bool has_circle(const Graph<T>& g) {
  // 结点访问情况: 0, 1, 2分别代表未访问, 正在访问, 已访问
  std::vector<int> state(g.num_vertices, 0);
  for (int i = 0; i < g.num_vertices; i++) {
    if (state[i] == 0 && !dfs(g, i, state)) { return false; }
  }
  return true;
}
