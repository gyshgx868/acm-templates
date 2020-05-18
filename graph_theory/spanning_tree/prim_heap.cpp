template <class T>
class Prim : public Graph<T> {
 public:
  explicit Prim(int n) : Graph<T>(n) {
    vis.resize(this->num_vertices);
    pre.resize(this->num_vertices);
  }

  T get_mst(int src = 0) {
    T value = T();
    std::fill(vis.begin(), vis.end(), 0);
    std::fill(pre.begin(), pre.end(), -1);
    std::vector<T> dist(this->num_vertices, std::numeric_limits<T>::max());
    dist[src] = T();
    std::priority_queue<Position> q;
    q.push(Position(src, T()));
    while (!q.empty()) {
      Position p = q.top();
      q.pop();
      if (vis[p.u] == 1) { continue; }
      vis[p.u] = 1;
      value += p.w;
      for (int i = this->head[p.u]; i != -1; i = this->next[i]) {
        if (vis[this->to[i]] == 0 && this->weights[i] < dist[this->to[i]]) {
          dist[this->to[i]] = this->weights[i];
          pre[this->to[i]] = p.u;
          q.push(Position(this->to[i], dist[this->to[i]]));
        }
      }
    }
    return value;
  }

  bool is_valid() const {
    int res = 0;
    for (int i = 0; i < this->num_vertices; i++) { res += vis[i]; }
    return res == this->num_vertices;
  }

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

  std::vector<int> vis;
  std::vector<int> pre;
};
