class SuffixArray {
 public:
  explicit SuffixArray(std::string s) {
    s += '\0';
    sa.resize(s.size());
    std::vector<int> head(std::max((int) s.size(), 128), 0);
    std::vector<int> color(s.size());
    for (int i = 0; i < s.size(); i++) { ++head[s[i]]; }
    for (int i = 1; i < 128; ++i) { head[i] += head[i - 1]; }
    for (int i = 127; i > 0; --i) { head[i] = head[i - 1]; }
    head[0] = 0;
    for (int i = 0; i < s.size(); i++) { sa[head[s[i]]++] = i; }
    int num_classes = 1;
    head[0] = 0;
    for (int i = 1; i < s.size(); i++) {
      if (s[sa[i - 1]] != s[sa[i]]) { head[num_classes++] = i; }
      color[sa[i]] = num_classes - 1;
    }
    std::vector<int> nextSufArray(s.size());
    std::vector<int> nextColor(s.size());
    for (int k = 1; k < s.size(); k *= 2) {
      for (int i = 0; i < sa.size(); i++) {
        int first_beginning = sa[i] - k;
        if (sa[i] < k) { first_beginning += s.size(); }
        nextSufArray[head[color[first_beginning]]] = first_beginning;
        ++head[color[first_beginning]];
      }
      std::swap(sa, nextSufArray);
      int second_beginning;
      std::pair<int, int> prev_classes;
      std::pair<int, int> cur_classes = std::make_pair(color.size(), 0);
      num_classes = 0;
      for (int pos = 0; pos < sa.size(); pos++) {
        prev_classes = cur_classes;
        second_beginning = sa[pos] + k;
        if (second_beginning >= (int) s.size()) {
          second_beginning -= s.size();
        }
        cur_classes = std::make_pair(color[sa[pos]], color[second_beginning]);
        if (cur_classes != prev_classes) { head[num_classes++] = pos; }
        nextColor[sa[pos]] = num_classes - 1;
      }
      std::swap(color, nextColor);
      if (num_classes == s.size()) { break; }
    }
    sa.erase(sa.begin());
    rank.resize(sa.size());
    for (int i = 0; i < sa.size(); ++i) { rank[sa[i]] = i; }
  }

  int get_nth_suffix(int n) const { return sa[n]; }

  int get_position(int suffix) const { return rank[suffix]; }

  int size() const { return rank.size(); }

 private:
  std::vector<int> sa;
  std::vector<int> rank;
};

class SuffixArrayLCP : public SuffixArray {
 public:
  explicit SuffixArrayLCP(const std::string& s)
      : SuffixArray(s), sparse(height = generate_lcp(*this, s)) {}

  int lcp(int l, int r) const {
    l = get_position(l);
    r = get_position(r);
    std::pair<int, int> p = std::minmax(l, r);
    return lcp_by_position(p.first, p.second);
  }

  int lcp_by_position(int l, int r) const {
    if (l == r) { return size() - get_nth_suffix(l); }
    return sparse.query(l, r);
  }

  // 寻找不同子串的个数
  long long num_different_substr() const {
    long long res = size() - get_nth_suffix(0);
    for (int i = 1; i < size(); i++) {
      res += size() - get_nth_suffix(i) - height[i - 1];
    }
    return res;
  }

 private:
  static std::vector<int> generate_lcp(
      const SuffixArray& base, const std::string& s) {
    int cur_lcp = 0;
    std::vector<int> lcp(s.size() - 1);
    for (int i = 0; i < s.size(); ++i) {
      int pos = base.get_position(i);
      if (pos == s.size() - 1) {
        cur_lcp = 0;
        continue;
      }
      while (s[i + cur_lcp] == s[base.get_nth_suffix(pos + 1) + cur_lcp]) {
        ++cur_lcp;
      }
      lcp[pos] = cur_lcp;
      if (cur_lcp > 0) { --cur_lcp; }
    }
    return lcp;
  }

  std::vector<int> height;
  SparseTable<int, Min> sparse;
};
