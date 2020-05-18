template <class T>
class Dinic : public FlowGraph<T> {
 public:
  explicit Dinic(int n) : FlowGraph<T>(n) { dis.resize(n); }

  T max_flow(int src, int dest) {
    T res = T();
    while (bfs(src, dest)) {
      res += dfs(src, dest, std::numeric_limits<T>::max());
    }
    return res;
  }

 private:
  std::vector<int> dis;

  bool bfs(int src, int dest) {
    std::vector<int> vis(this->num_vertices, 0);
    std::fill(dis.begin(), dis.end(), 0);
    std::queue<int> que;
    vis[src] = 1;
    que.push(src);
    while (!que.empty()) {
      int u = que.front();
      que.pop();
      for (int i = this->head[u]; i != -1; i = this->next[i]) {
        int v = this->to[i];
        if (this->capacity[i] > T() && vis[v] == 0) {
          que.push(v);
          dis[v] = dis[u] + 1;
          vis[v] = 1;
        }
      }
    }
    return vis[dest] == 1;
  }

  T dfs(int u, int dest, T delta) {
    if (u == dest) { return delta; }
    T res = T();
    for (int i = this->head[u]; delta && i != -1; i = this->next[i]) {
      int v = this->to[i];
      if (this->capacity[i] > T() && dis[v] == dis[u] + 1) {
        T aug = dfs(v, dest, std::min(this->capacity[i], delta));
        this->push_flow(i, -aug);
        this->push_flow(i ^ 1, aug);
        delta -= aug;
        res += aug;
      }
    }
    return res;
  }
};
