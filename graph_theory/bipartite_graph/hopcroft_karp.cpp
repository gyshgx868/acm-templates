class HopcroftKarp {
 public:
  explicit HopcroftKarp(int left, int right) {
    left_size = left;
    right_size = right;
    link.resize(left_size);
    vis.resize(right_size);
    match_x.resize(left);
    match_y.resize(right);
    dist_x.resize(left);
    dist_y.resize(right);
  }

  void add_link(int u, int v) { link[u].push_back(v); }

  int solve() {
    int max_match = 0;
    std::fill(match_x.begin(), match_x.end(), -1);
    std::fill(match_y.begin(), match_y.end(), -1);
    while (match()) {
      std::fill(vis.begin(), vis.end(), 0);
      for (int i = 0; i < left_size; i++) {
        if (match_x[i] == -1 && dfs(i)) { max_match++; }
      }
    }
    return max_match;
  }

 private:
  int left_size, right_size;
  int min_dist;
  std::vector<int> vis;
  std::vector<std::vector<int> > link;
  std::vector<int> match_x, match_y;
  std::vector<int> dist_x, dist_y;

  bool match() {
    std::queue<int> q;
    min_dist = std::numeric_limits<int>::max();
    std::fill(dist_x.begin(), dist_x.end(), -1);
    std::fill(dist_y.begin(), dist_y.end(), -1);
    for (int i = 0; i < left_size; i++) {
      if (match_x[i] == -1) {
        q.push(i);
        dist_x[i] = 0;
      }
    }
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      if (dist_x[u] > min_dist) { break; }
      for (int i = 0; i < link[u].size(); i++) {
        int v = link[u][i];
        if (dist_y[v] == -1) {
          dist_y[v] = dist_x[u] + 1;
          if (match_y[v] == -1) {
            min_dist = dist_y[v];
          } else {
            dist_x[match_y[v]] = dist_y[v] + 1;
            q.push(match_y[v]);
          }
        }
      }
    }
    return min_dist != std::numeric_limits<int>::max();
  }

  bool dfs(int u) {
    for (int i = 0; i < link[u].size(); i++) {
      int v = link[u][i];
      if (vis[v] == 0 && dist_y[v] == dist_x[u] + 1) {
        vis[v] = 1;
        if (match_y[v] != -1 && dist_y[v] == min_dist) { continue; }
        if (match_y[v] == -1 || dfs(match_y[v])) {
          match_y[v] = u;
          match_x[u] = v;
          return true;
        }
      }
    }
    return false;
  }
};
