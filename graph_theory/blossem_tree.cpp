class BlossemTree {
 public:
  explicit BlossemTree(int n) {
    graph.resize(n);
    match.resize(n);
    link.resize(n);
    mark.resize(n);
    vis.resize(n);
  }

  void add_edge(int u, int v) {
    graph[u].push_back(v);
    graph[v].push_back(u);
  }

  int solve() {
    std::fill(match.begin(), match.end(), -1);
    for (int i = 0; i < graph.size(); i++) { aug(i); }
    int res = 0;
    for (int i = 0; i < graph.size(); i++) {
      if (match[i] != -1) { res++; }
    }
    return res;
  }

  const std::vector<int>& get_matches() const { return match; }

 private:
  std::vector<int> match;
  std::vector<std::vector<int> > graph;
  std::vector<int> link;
  std::vector<int> mark;
  std::vector<int> vis;

  int get_lca(int x, int y, DisjointSet& uf) {
    static int last = 0;
    last++;
    while (true) {
      if (x != -1) {
        x = uf.get(x);
        if (vis[x] == last) { return x; }
        vis[x] = last;
        if (match[x] != -1) {
          x = link[match[x]];
        } else {
          x = -1;
        }
      }
      std::swap(x, y);
    }
  }

  void group(int a, int p, std::queue<int>& que, DisjointSet& uf) {
    while (a != p) {
      int b = match[a], c = link[b];
      if (uf.get(c) != p) { link[c] = b; }
      if (mark[b] == 2) {
        que.push(b);
        mark[b] = 1;
      }
      if (mark[c] == 2) {
        que.push(c);
        mark[c] = 1;
      }
      uf.join(a, b);
      uf.join(b, c);
      a = c;
    }
  }

  void aug(int s) {
    DisjointSet ds(graph.size());
    std::fill(link.begin(), link.end(), -1);
    std::fill(mark.begin(), mark.end(), 0);
    std::fill(vis.begin(), vis.end(), -1);
    mark[s] = 1;
    std::queue<int> que;
    que.push(s);
    while (!que.empty() && match[s] == -1) {
      int x = que.front();
      que.pop();
      for (int i = 0; i < (int) graph[x].size(); i++) {
        int y = graph[x][i];
        if (match[x] == y) { continue; }
        if (ds.get(x) == ds.get(y)) { continue; }
        if (mark[y] == 2) { continue; }
        if (mark[y] == 1) {
          int lca = get_lca(x, y, ds);
          if (ds.get(x) != lca) { link[x] = y; }
          if (ds.get(y) != lca) { link[y] = x; }
          group(x, lca, que, ds);
          group(y, lca, que, ds);
        } else if (match[y] == -1) {
          link[y] = x;
          for (int u = y; u != -1;) {
            int v = link[u];
            int mv = match[v];
            match[v] = u;
            match[u] = v;
            u = mv;
          }
          break;
        } else {
          link[y] = x;
          mark[match[y]] = 1;
          que.push(match[y]);
          mark[y] = 2;
        }
      }
    }
  }
};
