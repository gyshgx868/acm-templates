template <class T>
class Dijkstra : public Graph<T> {
 public:
  explicit Dijkstra(int n) : Graph<T>(n) {
    dist.resize(n);
    pre.resize(n);
  }

  void dijkstra(int src = 0) {
    std::vector<int> vis(this->num_vertices, 0);
    std::fill(pre.begin(), pre.end(), -1);
    std::fill(dist.begin(), dist.end(), std::numeric_limits<T>::max());
    dist[src] = T();
    std::priority_queue<Position> q;
    q.push(Position(src, 0));
    while (!q.empty()) {
      Position p = q.top();
      q.pop();
      if (vis[p.u] == 1) { continue; }
      vis[p.u] = 1;
      for (int i = this->head[p.u]; i != -1; i = this->next[i]) {
        int v = this->to[i];
        if (vis[v] == 0 && p.w + this->weights[i] < dist[v]) {
          dist[v] = dist[p.u] + this->weights[i];
          pre[v] = p.u;
          q.push(Position(v, dist[v]));
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
  struct Position {
    int u;
    T w;

    Position(int u, T w) : u(u), w(w) {}

    bool operator <(const Position& p) const { return w > p.w; }
  };

  std::vector<T> dist;
  std::vector<int> pre;
};
