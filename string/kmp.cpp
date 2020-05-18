std::vector<int> get_lps(const std::string& pat) {
  std::vector<int> lps(pat.length());
  lps[0] = 0;
  int i = 1, len = 0;
  while (i < pat.length()) {
    if (pat[i] == pat[len]) {
      lps[i++] = ++len;
    } else {
      if (len != 0) {
        len = lps[len - 1];
      } else {
        lps[i++] = 0;
      }
    }
  }
  return lps;
}

std::vector<int> kmp(const std::string& str, const std::string& pat) {
  std::vector<int> lps = get_lps(pat);
  std::vector<int> res;
  int i = 0, j = 0;
  while (i < str.length()) {
    if (pat[j] == str[i]) {
      j++;
      i++;
    }
    if (j == pat.length()) {
      res.push_back(i - j);
      j = lps[j - 1];
    } else if (i < str.length() && pat[j] != str[i]) {
      if (j != 0) {
        j = lps[j - 1];
      } else {
        i++;
      }
    }
  }
  return res;
}
