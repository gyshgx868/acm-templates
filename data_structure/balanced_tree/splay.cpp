template <class T>
class SplayTree {
 public:
  explicit SplayTree(int capacity) {
    num_nodes = 0;
    value.resize(capacity);
    parent.resize(capacity);
    left.resize(capacity);
    right.resize(capacity);
    count.resize(capacity);
    size.resize(capacity);
    left[0] = right[0] = parent[0] = count[0] = size[0] = 0;
  }

  void insert(T val) {
    int cur = right[0];
    if (cur == 0) {
      right[0] = create_node(val, 0);
    } else {
      while (true) {
        size[cur]++;
        if (value[cur] == val) {
          count[cur]++;
          splay(cur, right[0]);
          return;
        }
        if (val < value[cur]) {
          if (left[cur] == 0) {
            int q = create_node(val, cur);
            left[cur] = q;
            splay(q, right[0]);
            return;
          }
          cur = left[cur];
        } else {
          if (right[cur] == 0) {
            int node = create_node(val, cur);
            right[cur] = node;
            splay(node, right[0]);
            return;
          }
          cur = right[cur];
        }
      }
    }
  }

  void remove(T val) {
    int cur = find_node(val);
    if (cur == 0) { return; }
    if (count[cur] > 1) {
      size[cur]--;
      count[cur]--;
    } else {
      if (left[cur] == 0 && right[cur] == 0) {
        right[0] = 0;
      } else if (left[cur] == 0) {
        right[0] = right[cur];
        parent[right[0]] = 0;
      } else {
        int node = left[cur];
        while (right[node]) { node = right[node]; }
        splay(node, left[cur]);
        set_right(node, right[cur]);
        set_right(0, node);
        update(node);
      }
    }
  }

  int rank(T val) {
    int cur = find_node(val);
    return size[left[cur]] + 1;
  }

  int select(int k) {
    int cur = right[0];
    while (true) {
      int delta = size[cur] - size[right[cur]];
      if (k > size[left[cur]] && k <= delta) {
        splay(cur, right[0]);
        return value[cur];
      }
      if (k < delta) {
        cur = left[cur];
      } else {
        k -= delta;
        cur = right[cur];
      }
    }
  }

  T prev(T val) {
    int cur = right[0];
    T res = std::numeric_limits<T>::min();
    while (cur) {
      if (value[cur] < val && value[cur] > res) { res = value[cur]; }
      if (val > value[cur]) {
        cur = right[cur];
      } else {
        cur = left[cur];
      }
    }
    return res;
  }

  T succ(T val) {
    int cur = right[0];
    T res = std::numeric_limits<T>::max();
    while (cur) {
      if (value[cur] > val && value[cur] < res) { res = value[cur]; }
      if (val < value[cur]) {
        cur = left[cur];
      } else {
        cur = right[cur];
      }
    }
    return res;
  }

 private:
  int num_nodes;
  std::vector<T> value;
  std::vector<int> parent;
  std::vector<int> left;
  std::vector<int> right;
  std::vector<int> count;
  std::vector<int> size;

  void update(int node) {
    size[node] = size[left[node]] + size[right[node]] + count[node];
  }

  void rotate_node(int node) {
    int y = parent[node];
    int r = parent[y];
    if (left[parent[node]] == node) {
      if (left[parent[y]] == y) {
        set_left(y, right[node]);
        set_right(node, y);
        set_left(r, node);
      } else {
        set_left(y, right[node]);
        set_right(node, y);
        set_right(r, node);
      }
    } else {
      if (left[parent[y]] == y) {
        set_right(y, left[node]);
        set_left(node, y);
        set_left(r, node);
      } else {
        set_right(y, left[node]);
        set_left(node, y);
        set_right(r, node);
      }
    }
    update(y);
    update(node);
  }

  void splay(int node, int to) {
    to = parent[to];
    while (parent[node] != to) {
      int y = parent[node];
      if (parent[y] == to) {
        rotate_node(node);
      } else if ((left[parent[node]] == node && left[parent[y]] == y) ||
          (left[parent[node]] != node && left[parent[y]] != y)) {
        rotate_node(y);
        rotate_node(node);
      } else {
        rotate_node(node);
        rotate_node(node);
      }
    }
  }

  int create_node(T val, int par) {
    parent[++num_nodes] = par;
    value[num_nodes] = val;
    size[num_nodes] = count[num_nodes] = 1;
    return num_nodes;
  }

  int find_node(T val) {
    int cur = right[0];
    while (true) {
      if (value[cur] == val) {
        splay(cur, right[0]);
        return cur;
      }
      if (val < value[cur]) {
        if (left[cur] == 0) { return 0; }
        cur = left[cur];
      } else {
        if (right[cur] == 0) { return 0; }
        cur = right[cur];
      }
    }
  }

  void set_left(int node, int child) {
    left[node] = child;
    parent[child] = node;
  }

  void set_right(int node, int child) {
    right[node] = child;
    parent[child] = node;
  }
};
