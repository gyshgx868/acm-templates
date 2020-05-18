class KuhnMunkras {
 public:
  explicit KuhnMunkras(int left, int right) {
    left_size = left;
    right_size = right;
    match_x.resize(left_size, std::numeric_limits<int>::min());
    match_y.resize(right_size);
    vis_x.resize(left_size);
    vis_y.resize(right_size);
    link.resize(right_size);
    slack.resize(right_size);
    weights.resize(left_size, std::vector<int>(right_size, 0));
  }

  void add_link(int u, int v, int w) { weights[u][v] = w; }

  int solve() {
    std::fill(link.begin(), link.end(), -1);
    std::fill(match_y.begin(), match_y.end(), 0);
    for (int i = 0; i < left_size; i++) {
      for (int j = 0; j < right_size; j++) {
        match_x[i] = std::max(match_x[i], weights[i][j]);
      }
    }
    for (int x = 0; x < left_size; x++) {
      std::fill(slack.begin(), slack.end(), std::numeric_limits<int>::max());
      while (true) {
        std::fill(vis_x.begin(), vis_x.end(), 0);
        std::fill(vis_y.begin(), vis_y.end(), 0);
        if (dfs(x)) { break; }
        int min_dist = inf;
        for (int i = 0; i < right_size; i++) {
          if (vis_y[i] == 0 && min_dist > slack[i]) { min_dist = slack[i]; }
        }
        for (int i = 0; i < left_size; i++) {
          if (vis_x[i] == 1) { match_x[i] -= min_dist; }
        }
        for (int i = 0; i < right_size; i++) {
          if (vis_y[i] == 1) {
            match_y[i] += min_dist;
          } else {
            slack[i] -= min_dist;
          }
        }
      }
    }
    int res = 0;
    for (int i = 0; i < right_size; i++) {
      if (link[i] != -1) { res += weights[link[i]][i]; }
    }
    return res;
  }

 private:
  int left_size, right_size;
  std::vector<std::vector<int> > weights;
  std::vector<int> match_x, match_y;
  std::vector<int> vis_x, vis_y;
  std::vector<int> link;
  std::vector<int> slack;

  bool dfs(int x) {
    vis_x[x] = 1;
    for (int y = 0; y < right_size; y++) {
      if (vis_y[y] == 1) { continue; }
      int tmp = match_x[x] + match_y[y] - weights[x][y];
      if (tmp == 0) {
        vis_y[y] = 1;
        if (link[y] == -1 || dfs(link[y])) {
          link[y] = x;
          return true;
        }
      } else if (slack[y] > tmp) {
        slack[y] = tmp;
      }
    }
    return false;
  }
};
