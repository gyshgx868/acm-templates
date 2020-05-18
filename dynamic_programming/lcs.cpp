template <class T>
class LCS {
 public:
  explicit LCS(const std::vector<T>& x, const std::vector<T>& y) {
    x_len = x.size();
    y_len = y.size();
    f.resize(x_len + 1, std::vector<int>(y_len + 1, 0));
    path.resize(x_len, std::vector<int>(y_len));
    for (int i = 1; i <= x_len; i++) {
      for (int j = 1; j <= y_len; j++) {
        if (x[i - 1] == y[j - 1]) {
          f[i][j] = f[i - 1][j - 1] + 1;
          path[i - 1][j - 1] = 0;
        } else if (f[i - 1][j] >= f[i][j - 1]) {
          f[i][j] = f[i - 1][j];
          path[i - 1][j - 1] = 1;
        } else {
          f[i][j] = f[i][j - 1];
          path[i - 1][j - 1] = -1;
        }
      }
    }
  }

  int get_lcs() const { return f[x_len][y_len]; }

  std::vector<int> get_seq() {  // 通过访问第一个序列的下标来输出LCS
    std::vector<int> index_first_seq;
    get_seq(x_len - 1, y_len - 1, index_first_seq);
    return index_first_seq;
  }

 private:
  int x_len, y_len;
  std::vector<std::vector<int> > f;
  std::vector<std::vector<int> > path;

  void get_seq(int i, int j, std::vector<int>& res) {
    if (i < 0 || j < 0) { return; }
    if (path[i][j] == 0) {
      get_seq(i - 1, j - 1, res);
      res.push_back(i);
    } else if (path[i][j] == 1) {
      get_seq(i - 1, j, res);
    } else {
      get_seq(i, j - 1, res);
    }
  }
};
