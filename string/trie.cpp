class Trie {
 public:
  explicit Trie(int chars = 26) {
    num_nodes = 0;
    num_chars = chars;
  }

  void insert(const std::string& s) {
    int root = 0;
    ensure_capacity(num_nodes + s.size() + 1);
    for (int i = 0; i < s.size(); i++) {
      int c = s[i] - 'a';
      if (nodes[root][c] == 0) {
        nodes[root][c] = ++num_nodes;
        root = num_nodes;
      } else {
        root = nodes[root][c];
      }
      size[root]++;
    }
  }

  int query(const std::string& s) {
    int root = 0;
    for (int i = 0; i < s.size(); i++) {
      int c = s[i] - 'a';
      if (nodes[root][c] == 0) { return 0; }
      root = nodes[root][c];
    }
    return size[root];
  }

 private:
  int num_nodes;
  int num_chars;
  std::vector<std::vector<int> > nodes;
  std::vector<int> size;

  void ensure_capacity(int capacity) {
    if (nodes.size() >= capacity) { return; }
    nodes.resize(capacity, std::vector<int>(num_chars, 0));
    size.resize(capacity, 0);
  }
};
