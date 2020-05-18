template <class T>
class SPFA : public Graph<T> {
 public:
  explicit SPFA(int n) : Graph<T>(n) {
    dist.resize(n);
    pre.resize(n);
  }

  bool spfa(int src = 0) {
    std::vector<int> vis(this->num_vertices, 0);
    std::vector<int> degree(this->num_vertices, 0);
    std::fill(pre.begin(), pre.end(), -1);
    std::fill(dist.begin(), dist.end(), std::numeric_limits<T>::max());
    dist[src] = T();
    std::queue<int> q;
    vis[src] = 1;
    q.push(src);
    while (!q.empty()) {
      int u = q.front();
      q.pop();
      vis[u] = 0;
      if (degree[u] >= this->num_vertices) { return false; }  // 存在负环
      for (int i = this->head[u]; i != -1; i = this->next[i]) {
        int v = this->to[i];
        if (dist[u] + this->weights[i] < dist[v]) {
          dist[v] = dist[u] + this->weights[i];
          pre[v] = u;
          if (vis[v] == 0) {
            vis[v] = 1;
            q.push(v);
            degree[v]++;
          }
        }
      }
    }
    return true;  // 不存在负环
  }

  T operator [](int dest) const { return dist[dest]; }

  std::vector<int> get_path(int src, int dest) const {
    std::stack<int> path;
    if (pre[dest] != -1) {
      while (dest != src) {
        path.push(dest);
        dest = pre[dest];
      }
      path.push(dest);
    } else {
      path.push(-1);
    }
    std::vector<int> res;
    while (!path.empty()) {
      res.push_back(path.top());
      path.pop();
    }
    return res;
  }

 private:
  std::vector<T> dist;
  std::vector<int> pre;
};
