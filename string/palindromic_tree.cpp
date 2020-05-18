class PalindromicTree {
 public:
  explicit PalindromicTree(int length, int chars = 26) {
    num_nodes = 0;
    num_chars = chars;
    create_node(0);
    create_node(-1);
    values.resize(2 * (length + 1), -1);
    left = length;
    right = length - 1;
    last.resize(2, 1);
    fail[0] = 1;
    count = 0;
  }

  // 查询当前字符串中有多少子串是回文串 (相同的串重复计算)
  long long num_diff_palindromic_str() const { return count; }

  // 查询当前字符串中有多少不一样的回文串
  int num_palindromic_str() const { return num_nodes - 2; }

  // is_back 为 true 表示在当前串后面插入字符, 反之则在前面
  int add(int c, bool is_back = true) {  // 插入时需要转换为 0-26
    if (is_back) {
      values[++right] = c;
    } else {
      values[--left] = c;
    }
    int cur = get_fail(last[is_back], is_back);
    if (next[cur][c] == 0) {
      int root = create_node(length[cur] + 2);
      fail[root] = next[get_fail(fail[cur], is_back)][c];
      next[cur][c] = root;
      num[root] = num[fail[root]] + 1;
    }
    last[is_back] = next[cur][c];
    if (length[last[is_back]] == right - left + 1) {
      last[is_back ^ 1] = last[is_back];
    }
    count += num[last[is_back]];
    // 返回值表示以当前插入字符结尾的字符串的回文子串个数
    return num[last[is_back]];
  }

 private:
  std::vector<std::vector<int> > next;
  std::vector<int> fail;
  std::vector<int> length;
  std::vector<int> num;
  std::vector<int> last;
  std::vector<int> values;
  int left, right;
  int num_nodes;
  int num_chars;
  long long count;

  int create_node(int l) {
    next.push_back(std::vector<int>(num_chars, 0));
    num.push_back(0);
    length.push_back(l);
    fail.push_back(0);
    return num_nodes++;
  }

  int get_fail(int v, bool is_back) const {
    if (is_back) {
      while (values[right - length[v] - 1] != values[right]) { v = fail[v]; }
    } else {
      while (values[left + length[v] + 1] != values[left]) { v = fail[v]; }
    }
    return v;
  }
};
