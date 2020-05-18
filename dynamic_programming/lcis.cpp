template <class T>
class LCIS {
 public:
  explicit LCIS(const std::vector<T>& x, const std::vector<T>& y) {
    x_len = x.size();
    y_len = y.size();
    max_length = 0;
    f.resize(x_len + 1, std::vector<int>(y_len + 1, 0));
    path.resize(x_len, std::vector<int>(y_len));
    for (int i = 1; i <= x_len; i++) {
      int cur = 0, pre = 0;
      for (int j = 1; j <= y_len; j++) {
        f[i][j] = f[i - 1][j];
        path[i - 1][j - 1] = -1;
        if (x[i - 1] > y[j - 1] && cur < f[i - 1][j]) {
          cur = f[i - 1][j];
          pre = j - 1;
        }
        if (x[i - 1] == y[j - 1]) {
          f[i][j] = cur + 1;
          path[i - 1][j - 1] = pre;
        }
        if (max_length < f[i][j]) {
          max_length = f[i][j];
          start_x = i - 1;
          start_y = j - 1;
        }
      }
    }
  }

  int lcis_length() const { return max_length; }

  std::vector<int> get_lcis() const {  // 通过访问第二个序列的下标来输出LCIS
    int cur = max_length;
    int i = start_x, j = start_y;
    std::vector<int> index_second_seq;
    while (cur > 0) {
      if (path[i][j] != -1) {
        index_second_seq.push_back(j);
        cur--;
        j = path[i][j];
      }
      i--;
    }
    std::reverse(index_second_seq.begin(), index_second_seq.end());
    return index_second_seq;
  }

 private:
  int x_len, y_len;
  int max_length;
  int start_x, start_y;
  std::vector<std::vector<int> > f;
  std::vector<std::vector<int> > path;
};
