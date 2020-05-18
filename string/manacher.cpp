int manacher(const std::string& s) {
  std::vector<char> extended;
  extended.push_back('#');
  extended.push_back('$');
  for (int i = 0; i < s.size(); i++) {
    extended.push_back(s[i]);
    extended.push_back('$');
  }
  std::vector<int> p(extended.size());
  int mid = 1, cur = 1, res = 0;
  for (int i = 1; i < extended.size(); i++) {
    if (i < cur) {
      p[i] = std::min(cur - i, p[mid * 2 - i]);
    } else {
      p[i] = 1;
    }
    while (extended[i - p[i]] == extended[i + p[i]]) { p[i]++; }
    if (cur < i + p[i]) {
      mid = i;
      cur = i + p[i];
    }
    res = std::max(res, p[i] - 1);
  }
  return res;
}
