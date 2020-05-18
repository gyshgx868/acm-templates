template <class T>
class KShortestPath {
 public:
  T distance;

  explicit KShortestPath(
      const Graph<T>& graph, const Graph<T>& rev, int s, int t, int k, T inf) {
    max_weight = inf;
    Dijkstra<T> dis(rev, t, max_weight);
    distance = astar(graph, dis, s, t, k);
  }

 private:
  struct Node {
    int to;
    T pre, next;

    Node(int t, T p, T n) : to(t), pre(p), next(n) {}

    bool operator <(const Node& b) const {
      return next == b.next ? b.pre < pre : b.next < next;
    }
  };

  T max_weight;

  T astar(const Graph<T>& g, const Dijkstra<T>& dis, int s, int t, int k) {
    int rank = 0;
    std::priority_queue<Node> que;
    if (s == t) { k++; }
    if (dis[s] == max_weight) { return -1; }
    que.push(Node(s, T(), dis[s]));
    while (!que.empty()) {
      Node e = que.top();
      que.pop();
      if (e.to == t) { rank++; }
      if (rank == k) { return e.pre; }
      for (int i = g.first_out_bound(e.to); i != -1; i = g.next_out_bound(i)) {
        T pre = e.pre + g[i];
        T next = e.pre + g[i] + dis[g.dest(i)];
        que.push(Node(g.dest(i), pre, next));
      }
    }
    return -1;
  }
};

int main() {
  int n, m;
  while (~scanf("%d%d", &n, &m)) {
    Graph<int> g1(n), g2(n);
    for (int i = 0; i < m; ++i) {
      int u, v, w;
      scanf("%d%d%d", &u, &v, &w);
      g1.add_edge(u - 1, v - 1, w);
      g2.add_edge(v - 1, u - 1, w);
    }
    int s, t, k;
    scanf("%d%d%d", &s, &t, &k);
    KShortestPath<int> d(g1, g2, s - 1, t - 1, k, inf);
    printf("%d\n", d.distance);
  }
  return 0;
}
