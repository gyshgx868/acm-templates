class Hungary {
 public:
  explicit Hungary(int left, int right) {
    left_size = left;
    right_size = right;
    link.resize(left_size);
    match.resize(right_size);
    vis.resize(right_size);
  }

  void add_link(int u, int v) { link[u].push_back(v); }

  int solve() {
    int res = 0;
    std::fill(match.begin(), match.end(), -1);
    for (int u = 0; u < left_size; u++) {
      std::fill(vis.begin(), vis.end(), 0);
      if (dfs(u)) { res++; }
    }
    return res;
  }

  bool is_valid(int s = 0) {
    std::vector<int> color(std::max(left_size, right_size), -1);
    return judge_bipartite(s, 0, color);
  }

 private:
  int left_size, right_size;
  std::vector<std::vector<int> > link;
  std::vector<int> match;
  std::vector<int> vis;

  bool dfs(int u) {
    for (int i = 0; i < link[u].size(); i++) {
      int v = link[u][i];
      if (vis[v] == 0) {
        vis[v] = 1;
        if (match[v] == -1 || dfs(match[v])) {
          match[v] = u;
          return true;
        }
      }
    }
    return false;
  }

  bool judge_bipartite(int u, int clr, std::vector<int>& color) {
    color[u] = clr;
    for (int i = 0; i < link[u].size(); i++) {
      int v = link[u][i];
      if (color[v] == color[u]) { return false; }
      if (color[v] == -1 && !judge_bipartite(v, clr ^ 1, color)) {
        return false;
      }
    }
    return true;
  }
};
