template <class T>
std::pair<T, std::vector<T> > stoer_wagner(std::vector<std::vector<T> >& g) {
  int n = g.size();
  std::vector<int> used(n);
  std::vector<T> cut, best_cut;
  T best_weight = std::numeric_limits<T>::max();
  for (int phase = n - 1; phase >= 0; phase--) {
    std::vector<int> added = used;
    std::vector<T> w = g[0];
    int prev, last = 0;
    for (int i = 0; i < phase; i++) {
      prev = last;
      last = -1;
      for (int j = 1; j < n; j++) {
        if (added[j] == 0 && (last == -1 || w[j] > w[last])) { last = j; }
      }
      if (i == phase - 1) {
        for (int j = 0; j < n; j++) { g[prev][j] += g[last][j]; }
        for (int j = 0; j < n; j++) { g[j][prev] = g[prev][j]; }
        used[last] = 1;
        cut.push_back(last);
        if (w[last] < best_weight) {
          best_cut = cut;
          best_weight = w[last];
        }
      } else {
        for (int j = 0; j < n; j++) {
          w[j] += g[last][j];
          added[last] = 1;
        }
      }
    }
  }
  return make_pair(best_weight, best_cut);
}
