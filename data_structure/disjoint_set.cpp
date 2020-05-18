class DisjointSet {
 public:
  explicit DisjointSet(int size) {
    color.resize(size);
    rank.resize(size);
    clear();
  }

  void clear() {
    set_count = color.size();
    std::fill(rank.begin(), rank.end(), 0);
    for (int i = 0; i < set_count; i++) { color[i] = i; }
  }

  bool join(int first, int second) {
    first = get(first);
    second = get(second);
    if (first == second) { return false; }
    if (rank[first] <= rank[second]) {
      color[first] = second;
      if (rank[first] == rank[second]) { rank[first]++; }
    } else {
      color[second] = first;
    }
    set_count--;
    return true;
  }

  int get(int index) {
    int start = index;
    while (color[index] != index) { index = color[index]; }
    while (start != index) {
      int next = color[start];
      color[start] = index;
      start = next;
    }
    return index;
  }

  int get_set_count() const { return set_count; }

 private:
  int set_count;
  std::vector<int> color;
  std::vector<int> rank;
};
