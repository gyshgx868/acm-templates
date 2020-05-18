template <class T>
class PersistentTree {  // 0-indexed
 public:
  explicit PersistentTree(const std::vector<T>& arr) {
    node_cnt = 0;
    rank.resize(arr.size() * 20);
    root.resize(arr.size() * 20);
    left_child.resize(arr.size() * 20);
    right_child.resize(arr.size() * 20);
    sub = arr;
    std::sort(sub.begin(), sub.end());
    sub.erase(std::unique(sub.begin(), sub.end()), sub.end());
    root[0] = build(0, sub.size() - 1);
    for (int i = 0; i < arr.size(); i++) {
      int at = std::lower_bound(sub.begin(), sub.end(), arr[i]) - sub.begin();
      root[i + 1] = update(root[i], 0, sub.size() - 1, at);
    }
  }

  int query(int from, int to, int k) const {
    return sub[query(root[from], root[to + 1], 0, sub.size() - 1, k)];
  }

 private:
  int node_cnt;
  std::vector<T> sub;
  std::vector<int> rank;
  std::vector<int> root, left_child, right_child;

  int build(int left, int right) {
    int root_id = node_cnt++;
    if (left == right) { return root_id; }
    int mid = (left + right) / 2;
    left_child[root_id] = build(left, mid);
    right_child[root_id] = build(mid + 1, right);
    return root_id;
  }

  int update(int pre_id, int left, int right, int at) {
    int root_id = node_cnt++;
    left_child[root_id] = left_child[pre_id];
    right_child[root_id] = right_child[pre_id];
    rank[root_id] = rank[pre_id] + 1;
    if (left == right) { return root_id; }
    int mid = (left + right) / 2;
    if (at <= mid) {
      left_child[root_id] = update(left_child[root_id], left, mid, at);
    } else {
      right_child[root_id] = update(right_child[root_id], mid + 1, right, at);
    }
    return root_id;
  }

  int query(int u, int v, int left, int right, int k) const {
    if (left == right) { return left; }
    int mid = (left + right) / 2;
    int x = rank[left_child[v]] - rank[left_child[u]];
    if (x >= k) { return query(left_child[u], left_child[v], left, mid, k); }
    return query(right_child[u], right_child[v], mid + 1, right, k - x);
  }
};
