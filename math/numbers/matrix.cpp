template <class T>
class Matrix {
 public:
  int rows, cols;

  explicit Matrix(int rows, int cols) : rows(rows), cols(cols) {
    value.resize(rows, std::vector<T>(cols));
  }

  static Matrix identity(int size) {
    Matrix res(size, size);
    for (int i = 0; i < size; i++) { res[i][i] = 1; }
    return res;
  }

  std::vector<T>& operator [](int i) { return value[i]; }

  const std::vector<T>& operator [](int i) const { return value[i]; }

  Matrix& operator =(const Matrix& rhs) {
    rows = rhs.rows;
    cols = rhs.cols;
    value = rhs.value;
    return *this;
  }

  Matrix operator +(const Matrix& rhs) const {
    Matrix res(rows, cols);
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        res[i][j] = value[i][j] + rhs[i][j];
      }
    }
    return res;
  }

  Matrix operator -(const Matrix& rhs) const {
    Matrix res(rows, cols);
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        res[i][j] = value[i][j] - rhs[i][j];
      }
    }
    return res;
  }

  Matrix operator *(const Matrix& rhs) const {
    Matrix res(rows, rhs.cols);
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        if (value[i][j] == 0) { continue; }
        for (int k = 0; k < rhs.cols; k++) {
          if (rhs.value[j][k] == 0) { continue; }
          res[i][k] = res[i][k] + value[i][j] * rhs[j][k];
        }
      }
    }
    return res;
  }

  Matrix& operator +=(const Matrix& rhs) { return *this = *this + rhs; }

  Matrix& operator -=(const Matrix& rhs) { return *this = *this - rhs; }

  Matrix& operator *=(const Matrix& rhs) { return *this = *this * rhs; }

  template <class U>
  Matrix operator *(const U& x) const {
    Matrix res(rows, cols);
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) { res[i][j] = value[i][j] * x; }
    }
    return res;
  }

  template <class U>
  Matrix operator /(const U& x) const {
    Matrix res(rows, cols);
    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        res[i][j] = value[i][j] / x;
      }
    }
    return res;
  }

  template <class U>
  Matrix& operator *=(const U& x) { return *this = *this * x; }

  template <class U>
  Matrix& operator /=(const U& x) { return *this = *this / x; }

  Matrix operator !() const {
    Matrix res(cols, rows);
    for (int i = 0; i < cols; i++) {
      for (int j = 0; j < rows; j++) { res[i][j] = value[j][i]; }
    }
    return res;
  }

  bool operator ==(const Matrix& rhs) const {
    return rows == rhs.rows && cols == rhs.cols && value == rhs.value;
  }

  bool operator !=(const Matrix& rhs) const { return !(rhs == *this); }

  friend std::istream& operator >>(std::istream& is, Matrix& x) {
    for (int i = 0; i < x.rows; i++) {
      for (int j = 0; j < x.cols; j++) { is >> x[i][j]; }
    }
    return is;
  }

  friend std::ostream& operator <<(std::ostream& os, const Matrix& x) {
    for (int i = 0; i < x.rows; i++) {
      os << x[i][0];
      for (int j = 1; j < x.cols; j++) { os << ' ' << x[i][j]; }
      if (i != x.rows - 1) { os << '\n'; }
    }
    return os;
  }

 private:
  std::vector<std::vector<T> > value;
};

template <class T, class U>
Matrix<T> quick_pow(Matrix<T> x, U n) {
  Matrix<T> res = Matrix<T>::identity(x.rows);
  if (n == U()) { return res; }
  while (n != U()) {
    if (n & 1) { res = x * res; }
    x = x * x;
    n >>= 1;
  }
  return res;
}

template <class T>
bool matrix_inv(Matrix<T>& mat) {
  if (mat.rows != mat.cols) { return false; }
  std::vector<int> row_index(mat.rows);
  std::vector<int> col_index(mat.rows);
  for (int k = 0; k < mat.rows; k++) {
    for (int i = k, j; i < mat.rows; i++) {
      for (j = k; j < mat.rows && mat[i][j] == 0; j++) {}
      row_index[k] = i;
      col_index[k] = j;
    }
    for (int i = 0; i < mat.rows; i++) {
      std::swap(mat[k][i], mat[row_index[k]][i]);
    }
    for (int i = 0; i < mat.rows; i++) {
      std::swap(mat[i][k], mat[i][col_index[k]]);
    }
    if (mat[k][k] == 0) { return false; }
    mat[k][k] = 1 / mat[k][k];
    for (int j = 0; j < mat.rows; j++) {
      if (j != k) { mat[k][j] = mat[k][j] * mat[k][k]; }
    }
    for (int i = 0; i < mat.rows; i++) {
      if (i == k) { continue; }
      T temp = mat[i][k];
      mat[i][k] = 0;
      for (int j = 0; j < mat.rows; j++) {
        mat[i][j] = mat[i][j] - mat[k][j] * temp;
      }
    }
  }
  for (int k = mat.rows - 1; k >= 0; k--) {
    for (int i = 0; i < mat.rows; i++) {
      std::swap(mat[col_index[k]][i], mat[k][i]);
    }
    for (int i = 0; i < mat.rows; i++) {
      std::swap(mat[i][row_index[k]], mat[i][k]);
    }
  }
  return true;
}
