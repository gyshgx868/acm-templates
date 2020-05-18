unsigned encode(const std::vector<int>& vis) {
  unsigned res = 0;
  for (unsigned i = 0; i < vis.size(); i++) {
    if (vis[i] == 0) { res |= 1u << i; }
  }
  return res;
}

int dfs(const std::vector<std::vector<int> >& g, std::vector<int>& vis,
        std::vector<int>& f) {
  unsigned p = encode(vis);
  if (f[p] != 0) { return f[p]; }
  int num = 0;
  std::vector<int> zero_deg;
  for (int i = 0; i < g.size(); i++) {
    if (vis[i] == 0) {
      num++;
      int num_zeros = 0;
      for (int j = 0; j < g.size(); j++) {
        if (vis[j] == 0 && g[j][i] != 0) { num_zeros++; }
      }
      if (num_zeros == 0) { zero_deg.push_back(i); }
    }
  }
  if (zero_deg.empty()) { return -1; }
  if (num == 1) { return f[p] = 1; }
  int sum = 0;
  for (int i = 0; i < zero_deg.size(); i++) {
    vis[zero_deg[i]] = 1;
    int cur = dfs(g, vis, f);
    if (cur == -1) { return -1; }
    vis[zero_deg[i]] = 0;
    sum += cur;
  }
  return f[p] = sum;
}

int topo_count(const std::vector<std::vector<int> >& g) {
  std::vector<int> vis(g.size(), 0);
  std::vector<int> f(1u << g.size(), 0);
  int res = dfs(g, vis, f);
  if (res == -1) { return 0; }
  return f[encode(vis)];
}
