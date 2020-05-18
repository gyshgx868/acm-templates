class Hungary {
 public:
  explicit Hungary(int left, int right) {
    left_size = left;
    right_size = right;
    link.resize(left_size);
    match.resize(right_size);
    match_x.resize(left_size, -1);
    match_y.resize(right_size, -1);
    vis.resize(right_size);
  }

  void add_link(int u, int v) { link[u].push_back(v); }

  int solve() {
    int res = 0;
    for (int i = 0; i < left_size; i++) {
      std::fill(vis.begin(), vis.end(), 0);
      std::fill(match.begin(), match.end(), -1);
      if (bfs(i)) { res++; }
    }
    return res;
  }

  bool is_valid(int s = 0) {
    std::queue<int> que;
    std::vector<int> color(std::max(left_size, right_size), -1);
    color[s] = 0;
    que.push(s);
    while (!que.empty()) {
      int u = que.front();
      que.pop();
      for (int i = 0; i < link[u].size(); i++) {
        int v = link[u][i];
        if (color[u] == color[v]) { return false; }
        if (color[v] == -1) {
          color[v] = color[u] ^ 1;
          que.push(v);
        }
      }
    }
    return true;
  }

 private:
  int left_size, right_size;
  std::vector<std::vector<int> > link;
  std::vector<int> match;
  std::vector<int> match_x, match_y;
  std::vector<int> vis;

  bool bfs(int u) {
    std::queue<int> que;
    que.push(u);
    while (!que.empty()) {
      int top = que.front();
      que.pop();
      for (int j = 0; j < link[top].size(); j++) {
        int v = link[top][j];
        if (!vis[v]) {
          vis[v] = 1;
          if (match_y[v] == -1) {
            int sl = top, sr = v;
            while (sl != -1) {
              int st = match_x[sl];
              match_x[sl] = sr;
              match_y[sr] = sl;
              sl = match[sl];
              sr = st;
            }
            return true;
          } else {
            match[match_y[v]] = top;
            que.push(match_y[v]);
          }
        }
      }
    }
    return false;
  }
};