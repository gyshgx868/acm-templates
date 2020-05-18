template <class T>
class SizeBalancedTree {
 public:
  explicit SizeBalancedTree(int capacity = 3) {
    current_root = 0;
    current_index = 0;
    values.resize(capacity);
    size.resize(capacity, 0);
    left.resize(capacity, 0);
    right.resize(capacity, 0);
  }

  void clear() {
    current_root = 0;
    current_index = 0;
    left[0] = right[0] = 0;
    size[0] = 0;
  }

  int get_size() const { return size[current_root]; }

  bool empty() const { return current_root == 0; }

  bool find(T key) const { return find(current_root, key); }

  void insert(T key) { insert(current_root, key); }

  void remove(T key) { remove(current_root, key); }

  T remove_select(int k) { return remove_select(current_root, k); }

  void remove_less(T key) { remove_less(current_root, key); }

  void remove_greater(T key) { remove_greater(current_root, key); }

  // 返回 key 的排名 (比当前数小的数的个数 +1)
  int rank(T key) const { return rank(current_root, key); }

  // 返回排名为 k 的数
  T select(int k) const { return select(current_root, k); }

  // 返回比 key 小的最大的键值
  T pred(T key) const { return pred(current_root, key); }

  // 返回比 key 大的最小的键值
  T succ(T key) const { return succ(current_root, key); }

  T get_min() const {
    int t = current_root;
    while (left[t]) { t = left[t]; }
    return values[t];
  }

  T get_max() const {
    int t = current_root;
    while (right[t]) { t = right[t]; }
    return values[t];
  }

  T remove_max() {
    int t = current_root;
    if (right[current_root] == 0) {
      current_root = left[current_root];
      return values[t];
    }
    while (right[right[t]]) {
      size[t]--;
      t = right[t];
    }
    size[t]--;
    T res = values[right[t]];
    right[t] = left[right[t]];
    return res;
  }

  T remove_min() {
    int t = current_root;
    if (left[current_root] == 0) {
      current_root = right[current_root];
      return values[t];
    }
    while (left[left[t]]) {
      size[t]--;
      t = left[t];
    }
    size[t]--;
    T res = values[left[t]];
    left[t] = right[left[t]];
    return res;
  }

 private:
  std::vector<T> values;
  std::vector<int> size;
  std::vector<int> left;
  std::vector<int> right;
  int current_root, current_index;

  bool find(int root, T key) const {
    if (root == 0) { return false; }
    if (key < values[root]) { return find(left[root], key); }
    return values[root] == key || find(right[root], key);
  }

  void insert(int& root, T key) {
    if (root == 0) {
      root = ++current_index;
      left[root] = right[root] = 0;
      size[root] = 1;
      values[root] = key;
      return;
    }
    size[root]++;
    if (key < values[root]) {
      insert(left[root], key);
    } else {
      insert(right[root], key);
    }
    maintain(root, key >= values[root]);
  }

  T remove(int& root, T key) {
    size[root]--;
    if (values[root] == key || (key < values[root] && left[root] == 0)
        || (values[root] < key && right[root] == 0)) {
      T res = values[root];
      if (left[root] == 0 || right[root] == 0) {
        root = left[root] + right[root];
      } else {
        values[root] = remove(left[root], values[root] + 1);
      }
      return res;
    }
    if (key < values[root]) { return remove(left[root], key); }
    return remove(right[root], key);
  }

  void remove_less(int& root, T key) {
    if (root == 0) { return; }
    if (values[root] < key) {
      root = right[root];
      remove_less(root, key);
    } else {
      remove_less(left[root], key);
      size[root] = 1 + size[left[root]] + size[right[root]];
    }
  }

  void remove_greater(int& root, T key) {
    if (root == 0) { return; }
    if (values[root] > key) {
      root = left[root];
      remove_greater(root, key);
    } else {
      remove_greater(right[root], key);
      size[root] = 1 + size[left[root]] + size[right[root]];
    }
  }

  int rank(int root, T key) const {
    if (root == 0) { return 1; }
    if (key <= values[root]) { return rank(left[root], key); }
    return size[left[root]] + 1 + rank(right[root], key);
  }

  T select(int root, int k) const {
    if (size[left[root]] + 1 == k) { return values[root]; }
    if (k > size[left[root]]) {
      return select(right[root], k - 1 - size[left[root]]);
    }
    return select(left[root], k);
  }

  T remove_select(int& root, int k) {
    size[root]--;
    if (size[left[root]] + 1 == k) {
      T res = values[root];
      if (left[root] == 0 || right[root] == 0) {
        root = left[root] + right[root];
      } else {
        values[root] = remove(left[root], values[root] + 1);
      }
      return res;
    }
    if (k > size[left[root]]) {
      return remove_select(right[root], k - 1 - size[left[root]]);
    }
    return remove_select(left[root], k);
  }

  T pred(int root, T key) const {
    if (root == 0) { return key; }
    if (key > values[root]) {
      T res = pred(right[root], key);
      if (res == key) { return values[root]; }
      return res;
    }
    return pred(left[root], key);
  }

  T succ(int root, T key) const {
    if (root == 0) { return key; }
    if (values[root] > key) {
      T res = succ(left[root], key);
      if (res == key) { return values[root]; }
      return res;
    }
    return succ(right[root], key);
  }

  void left_rotate(int& root) {
    int t = right[root];
    right[root] = left[t];
    left[t] = root;
    size[t] = size[root];
    size[root] = 1 + size[left[root]] + size[right[root]];
    root = t;
  }

  void right_rotate(int& root) {
    int t = left[root];
    left[root] = right[t];
    right[t] = root;
    size[t] = size[root];
    size[root] = 1 + size[left[root]] + size[right[root]];
    root = t;
  }

  void maintain(int& root, bool flag) {
    if (root == 0) { return; }
    if (!flag) {
      if (size[left[left[root]]] > size[right[root]]) {
        right_rotate(root);
      } else if (size[right[left[root]]] > size[right[root]]) {
        left_rotate(left[root]);
        right_rotate(root);
      } else {
        return;
      }
    } else {
      if (size[right[right[root]]] > size[left[root]]) {
        left_rotate(root);
      } else if (size[left[right[root]]] > size[left[root]]) {
        right_rotate(right[root]);
        left_rotate(root);
      } else {
        return;
      }
    }
    maintain(left[root], false);
    maintain(right[root], true);
    maintain(root, false);
    maintain(root, true);
  }
};
