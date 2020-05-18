template <class T>
bool has_circle(const Graph<T>& g) {
  std::vector<int> degree(g.num_vertices, 0);
  for (int i = 0; i < g.num_edges(); i++) {
    degree[g.dest(i)]++;
  }
  std::queue<int> que;
  for (int i = 0; i < g.num_vertices; i++) {
    if (degree[i] == 0) { que.push(i); }
  }
  while (!que.empty()) {
    int u = que.front();
    que.pop();
    for (int i = g.first_out_bound(u); i != -1; i = g.next_out_bound(i)) {
      if (degree[g.dest(i)] > 0) {
        degree[g.dest(i)]--;
        if (degree[g.dest(i)] == 0) { que.push(g.dest(i)); }
      }
    }
  }
  for (int i = 0; i < g.num_vertices; i++) {
    if (degree[i] != 0) { return false; }
  }
  return true;
}
