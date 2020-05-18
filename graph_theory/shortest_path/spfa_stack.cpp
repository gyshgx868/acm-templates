template <class T>
class SPFA : public Graph<T> {
 public:
  explicit SPFA(int n) : Graph<T>(n) {
    dist.resize(n);
    pre.resize(n);
  }

  void spfa(int src = 0) {
    std::vector<int> vis(this->num_vertices, 0);
    std::fill(pre.begin(), pre.end(), -1);
    std::fill(dist.begin(), dist.end(), std::numeric_limits<T>::max());
    dist[src] = T();
    std::stack<int> stk;
    vis[src] = 1;
    stk.push(src);
    while (!stk.empty()) {
      int u = stk.top();
      stk.pop();
      vis[u] = 0;
      for (int i = this->head[u]; i != -1; i = this->next[i]) {
        int v = this->to[i];
        if (dist[v] > dist[u] + this->weights[i]) {
          dist[v] = dist[u] + this->weights[i];
          pre[v] = u;
          if (vis[v] == 0) {
            vis[v] = 1;
            stk.push(v);
          }
        }
      }
    }
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
