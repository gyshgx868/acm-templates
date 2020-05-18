template <class T>
class MinCostMaxFlow : public CostFlowGraph<T> {
 public:
  explicit MinCostMaxFlow(int n) : CostFlowGraph<T>(n) {
    pre.resize(n);
    dist.resize(n);
  }

  std::pair<T, T> mcmf(int src, int dest) {
    T min_cost = T(), max_flow = T();
    while (spfa(src, dest)) {
      T min_flow = std::numeric_limits<T>::max();
      for (int i = pre[dest]; i != -1; i = pre[ this->from[i]]) {
        min_flow = std::min(min_flow, this->capacity[i]);
      }
      max_flow += min_flow;
      for (int i = pre[dest]; i != -1; i = pre[this->from[i]]) {
        this->push_flow(i, -min_flow);
        this->push_flow(i ^ 1, min_flow);
      }
      min_cost += dist[dest] * min_flow;
    }
    return std::make_pair(max_flow, min_cost);
  }

 private:
  std::vector<int> pre;
  std::vector<T> dist;

  bool spfa(int src, int dest) {
    std::vector<int> vis(this->num_vertices, 0);
    std::fill(dist.begin(), dist.end(), std::numeric_limits<T>::max());
    std::fill(pre.begin(), pre.end(), -1);
    std::queue<int> que;
    vis[src] = 1;
    dist[src] = 0;
    que.push(src);
    while (!que.empty()) {
      int u = que.front();
      que.pop();
      vis[u] = 0;
      for (int i = this->head[u]; i != -1; i = this->next[i]) {
        int v = this->to[i];
        if (this->capacity[i] && dist[v] > dist[u] + this->cost[i]) {
          dist[v] = dist[u] + this->cost[i];
          pre[v] = i;
          if (vis[v] == 0) {
            que.push(v);
            vis[v] = 1;
          }
        }
      }
    }
    return dist[dest] != std::numeric_limits<T>::max();
  }
};
