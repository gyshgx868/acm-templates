template <typename T>
struct ScapegoatNode {
  static constexpr double factor = 0.75;

  T data;
  int size, cover;
  int count;
  ScapegoatNode* children[2];

  explicit ScapegoatNode(T val) {
    data = val;
    size = cover = count = 1;
    children[0] = children[1] = nullptr;
  }

  void maintain() {
    cover = 1;
    size = count;
    for (int i = 0; i < 2; i++) {
      if (children[i] != nullptr) {
        cover += children[i]->cover;
        size += children[i]->size;
      }
    }
  }

  int compare(T val) const {
    if (data == val) { return -1; }
    return val < data ? 0 : 1;
  }

  bool bad() const {
    for (int i = 0; i < 2; i++) {
      if (children[i] == nullptr) { continue; }
      if (children[i]->cover > (cover + 3) * factor) { return true; }
    }
    return false;
  }

  void increase(int val) {
    size += val;
    count += val;
  }
};

template <typename T>
class ScapegoatTree {
  typedef ScapegoatNode<T>* node_ptr;
 public:
  ScapegoatTree() : root(nullptr) {}

  void insert(T data) {
    node_ptr node = nullptr, parent = nullptr;
    insert(root, data, node, parent);
    if (node != nullptr) { rebuild(node, parent); }
  }

  bool remove(T data) { return remove(root, data); }

  T prev(T data) const { return prev(root, data)->data; }

  T succ(T data) const { return succ(root, data)->data; }

  T select(int k) const { return select(root, k)->data; }

  int rank(T val) const {
    node_ptr p = root;
    int res = 0;
    while (p != nullptr) {
      int ls = p->children[0] != nullptr ? p->children[0]->size : 0;
      if (p->data == val) { return res + ls + 1; }
      int d = p->compare(val);
      if (d == 1) { res += ls + p->count; }
      p = p->children[d];
    }
    return res + 1;
  }

 private:
  node_ptr root;
  std::vector<node_ptr> pool;

  node_ptr rebuild(int from, int to) {
    if (from > to) { return nullptr; }
    if (from == to) {
      node_ptr node = pool[from];
      node->children[0] = node->children[1] = nullptr;
      node->size = node->count;
      node->cover = 1;
      return node;
    }
    int mid = (from + to) / 2;
    node_ptr node = pool[mid];
    node->children[0] = rebuild(from, mid - 1);
    node->children[1] = rebuild(mid + 1, to);
    node->maintain();
    return node;
  }

  void dfs_order(node_ptr& node) {
    if (node == nullptr) { return; }
    dfs_order(node->children[0]);
    if (node->count > 0) { pool.push_back(node); }
    dfs_order(node->children[1]);
    if (node->count <= 0) { delete node; }
  }

  void rebuild(node_ptr& node, node_ptr& parent) {
    pool.clear();
    dfs_order(node);
    node_ptr res = rebuild(0, pool.size() - 1);
    if (parent == nullptr) {
      root = res;
    } else {
      parent->children[parent->compare(res->data)] = res;
      find(root, res->data);
    }
  }

  void insert(node_ptr& node, T val, node_ptr& pre, node_ptr& parent) {
    if (node == nullptr) {
      node = new ScapegoatNode<T>(val);
      return;
    }
    int d = node->compare(val);
    if (d == -1) {
      node->increase(1);
      return;
    }
    insert(node->children[d], val, pre, parent);
    node->maintain();
    if (parent == nullptr && pre != nullptr) { parent = node; }
    if (node->bad()) {
      pre = node;
      parent = nullptr;
    }
  }

  bool remove(node_ptr& node, T val) {
    if (node == nullptr) { return false; }
    int d = node->compare(val);
    if (d == -1) {
      node->increase(-1);
      return true;
    }
    bool res = remove(node->children[d], val);
    if (res) { node->maintain(); }
    return res;
  }

  node_ptr prev(const node_ptr& node, T val) const {
    if (node == nullptr) { return node; }
    int to = node->compare(val);
    if (val == node->data) { to = 0; }
    node_ptr res = prev(node->children[to], val);
    if (to == 1 && res == nullptr) { res = prev(node->children[0], val); }
    return (res == nullptr || node->data > res->data) && node->data < val
               && node->count > 0 ? node : res;
  }

  node_ptr succ(const node_ptr& node, T val) const {
    if (node == nullptr) { return node; }
    int to = node->compare(val);
    if (val == node->data) { to = 1; }
    node_ptr res = succ(node->children[to], val);
    if (to == 0 && res == nullptr) {
      res = succ(node->children[1], val);
    }
    return (res == nullptr || node->data < res->data) && node->data > val
               && node->count > 0 ? node : res;
  }

  node_ptr select(const node_ptr& node, int k) const {
    int ls = node->children[0] == nullptr ? 0 : node->children[0]->size;
    int count = node->count;
    if (k >= ls + 1 && k <= ls + count) { return node; }
    if (k <= ls) { return select(node->children[0], k); }
    return select(node->children[1], k - ls - count);
  }

  node_ptr find(const node_ptr& node, T val) const {
    if (node == nullptr) { return nullptr; }
    int d = node->compare(val);
    if (d == -1) { return node; }
    node_ptr res = find(node->children[d], val);
    node->maintain();
    return res;
  }
};
