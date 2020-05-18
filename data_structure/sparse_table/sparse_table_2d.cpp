template <class T>
class SparseTable2D {
 public:
  explicit SparseTable2D(const std::vector<std::vector<T> >& data) {
    int rows = std::log2(data.size()) + 1;
    int cols = std::log2(data[0].size()) + 1;
    mat.resize(data.size());
    for (unsigned i = 0; i < data.size(); i++) {
      mat[i].resize(data[0].size());
      for (unsigned j = 0; j < data[0].size(); j++) {
        mat[i][j].resize(rows, std::vector<T>(cols));
      }
    }
    for (unsigned i = 0; (1u << i) <= data.size(); i++) {
      for (unsigned j = 0; (1u << j) <= data[0].size(); j++) {
        for (unsigned x = 0; x + (1u << i) - 1 < data.size(); x++) {
          for (unsigned y = 0; y + (1u << j) - 1 < data[0].size(); y++) {
            if (i == 0 && j == 0) {
              mat[x][y][i][j] = data[x][y];
            } else if (i == 0) {
              T a = mat[x][y][i][j - 1];
              T b = mat[x][y + (1u << (j - 1))][i][j - 1];
              mat[x][y][i][j] = std::max(a, b);
            } else if (j == 0) {
              T a = mat[x][y][i - 1][j];
              T b = mat[x + (1u << (i - 1))][y][i - 1][j];
              mat[x][y][i][j] = std::max(a, b);
            } else {
              T a = mat[x][y][i - 1][j - 1];
              T b = mat[x + (1u << (i - 1))][y][i - 1][j - 1];
              T c = mat[x][y + (1u << (j - 1))][i - 1][j - 1];
              T d = mat[x + (1u << (i - 1))][y + (1u << (j - 1))][i - 1][j - 1];
              mat[x][y][i][j] = std::max(std::max(a, b), std::max(c, d));
            }
          }
        }
      }
    }
  }

  T query(int row_from, int row_to, int col_from, int col_to) const {
    unsigned k = std::log2(row_to - row_from + 1);
    unsigned l = std::log2(col_to - col_from + 1);
    T a = mat[row_from][col_from][k][l];
    T b = mat[row_to - (1u << k) + 1][col_from][k][l];
    T c = mat[row_from][col_to - (1u << l) + 1][k][l];
    T d = mat[row_to - (1u << k) + 1][col_to - (1u << l) + 1][k][l];
    return std::max(std::max(a, b), std::max(c, d));
  }

 private:
  std::vector<std::vector<std::vector<std::vector<T> > > > mat;
};
