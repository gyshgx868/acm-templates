template <class T>
std::vector<int> sort_topologically(const Graph<T>& g) {
  std::priority_queue<int, std::vector<int>, std::greater<int> > que;
  std::vector<int> degree(g.num_vertices, 0);
  for (int i = 0; i < g.num_edges(); i++) {
    degree[g.dest(i)]++;
  }
  for (int i = 0; i < g.num_vertices; i++) {
    if (degree[i] == 0) { que.push(i); }
  }
  std::vector<int> res;
  while (!que.empty()) {
    int u = que.top();
    que.pop();
    res.push_back(u);
    for (int i = g.first_out_bound(u); i != -1; i = g.next_out_bound(i)) {
      if (degree[g.dest(i)] > 0) {
        degree[g.dest(i)]--;
        if (degree[g.dest(i)] == 0) { que.push(g.dest(i)); }
      }
    }
  }
  return res;
}
