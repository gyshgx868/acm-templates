class AhoCorasick {
 public:
  explicit AhoCorasick(int chars = 26) {
    num_nodes = 1;
    num_chars = chars;
  }

  void initialize() {  // call after inserting
    std::queue<int> que;
    fail[0] = 0;
    for (int i = 0; i < num_chars; i++) {
      int u = nodes[0][i];
      if (u != 0) {
        fail[u] = 0;
        que.push(u);
      }
    }
    while (!que.empty()) {
      int r = que.front();
      que.pop();
      for (int c = 0; c < num_chars; c++) {
        int u = nodes[r][c];
        if (u == 0) { continue; }
        que.push(u);
        int v = fail[r];
        while (v != 0 && !nodes[v][c]) { v = fail[v]; }
        fail[u] = nodes[v][c];
      }
    }
  }

  void insert(const std::string& s) {
    int root = 0;
    ensure_capacity(num_nodes + s.size() + 1);
    for (int i = 0; i < s.size(); i++) {
      int id = s[i] - 'a';
      if (nodes[root][id] == 0) { nodes[root][id] = num_nodes++; }
      root = nodes[root][id];
    }
    size[root]++;
  }

  int query(const std::string& s) {
    int root = 0, res = 0;
    for (int i = 0; i < s.size(); i++) {
      int id = s[i] - 'a';
      while (root != 0 && !nodes[root][id]) { root = fail[root]; }
      root = nodes[root][id];
      int t = root;
      while (t && size[t] != -1) {
        res += size[t];
        size[t] = -1;
        t = fail[t];
      }
    }
    return res;
  }

 private:
  std::vector<std::vector<int> > nodes;
  std::vector<int> fail;
  std::vector<int> size;
  int num_nodes;
  int num_chars;

  void ensure_capacity(int capacity) {
    if (nodes.size() >= capacity) { return; }
    nodes.resize(capacity, std::vector<int>(num_chars, 0));
    fail.resize(capacity, 0);
    size.resize(capacity, 0);
  }
};
