template <class T>
struct Edge {
  int from, to;
  T weight;

  explicit Edge(int u, int v, T w = T()) : from(u), to(v), weight(w) {}

  bool operator <(const Edge &b) const { return weight < b.weight; }
};
