template <class T>
class Treap {
 public:
  explicit Treap(int capacity) {
    root = 0;
    num_nodes = 0;
    value.resize(capacity);
    priority.resize(capacity);
    left.resize(capacity);
    right.resize(capacity);
    size.resize(capacity);
  }

  void insert(T val) { insert(root, val); }

  void remove(T val) { remove(root, val); }

  int rank(T val) const { return rank(root, val) + 1; }

  T select(T val) const { return find(root, val); }

  T prev(T val) const { return prev(root, val); }

  T succ(T val) const { return succ(root, val); }

 private:
  int root;
  int num_nodes;
  std::vector<T> value;
  std::vector<int> priority;
  std::vector<int> left;
  std::vector<int> right;
  std::vector<int> size;

  void push_up(int x) { size[x] = size[left[x]] + size[right[x]] + 1; }

  void right_rotate(int& node) {
    int new_root = left[node];
    left[node] = right[new_root];
    right[new_root] = node;
    size[new_root] = size[node];
    push_up(node);
    node = new_root;
  }

  void left_rotate(int& node) {
    int new_root = right[node];
    right[node] = left[new_root];
    left[new_root] = node;
    size[new_root] = size[node];
    push_up(node);
    node = new_root;
  }

  void insert(int& node, int val) {
    if (node == 0) {
      node = ++num_nodes;
      size[node] = 1;
      value[node] = val;
      priority[node] = rand();
      return;
    }
    size[node]++;
    if (val >= value[node]) {
      insert(right[node], val);
    } else {
      insert(left[node], val);
    }
    if (left[node] != 0 && priority[node] > priority[left[node]]) {
      right_rotate(node);
    }
    if (right[node] != 0 && priority[node] > priority[right[node]]) {
      left_rotate(node);
    }
    push_up(node);
  }

  void remove(int& node, T val) {
    size[node]--;
    if (value[node] == val) {
      if (left[node] == 0 && right[node] == 0) {
        node = 0;
        return;
      }
      if (left[node] == 0 || right[node] == 0) {
        node = left[node] + right[node];
        return;
      }
      if (priority[left[node]] < priority[right[node]]) {
        right_rotate(node);
        remove(right[node], val);
        return;
      } else {
        left_rotate(node);
        remove(left[node], val);
        return;
      }
    }
    if (value[node] >= val) {
      remove(left[node], val);
    } else {
      remove(right[node], val);
    }
    push_up(node);
  }

  int rank(int node, T val) const {
    if (node == 0) { return 0; }
    if (val > value[node]) {
      return size[left[node]] + 1 + rank(right[node], val);
    }
    return rank(left[node], val);
  }

  T find(int node, int k) const {
    if (k == size[left[node]] + 1) { return value[node]; }
    if (k > size[left[node]] + 1) {
      return find(right[node], k - size[left[node]] - 1);
    }
    return find(left[node], k);
  }

  T prev(int node, T val) const {
    if (node == 0) { return 0; }
    if (value[node] >= val) { return prev(left[node], val); }
    int res = prev(right[node], val);
    if (res == 0) { return value[node]; }
    return res;
  }

  T succ(int node, T val) const {
    if (node == 0) { return 0; }
    if (value[node] <= val) { return succ(right[node], val); }
    int res = succ(left[node], val);
    if (res == 0) { return value[node]; }
    return res;
  }
};
