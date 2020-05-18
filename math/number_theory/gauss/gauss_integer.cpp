// mat: 增广矩阵, 有num_equ个方程, num_var个变元
//      行数为 num_equ (0 <= i < num_equ), 列数为num_var (0 <= j < num_var - 1)
// sol: 解集
// 返回值: -2 (有浮点数解, 无整数解), -1 (无解), 0 (唯一解), 大于 0 (无穷解, 自由变元的个数)
int gauss(std::vector<std::vector<int> > &mat, std::vector<int> &sol, int mod) {
  int num_equ = mat.size();
  int num_var = mat[0].size() - 1;

  sol.resize(num_var + 1, 0);
  std::vector<int> is_free(num_var + 1, 1);  // 标记是否为自由元

  int col = 0, k;
  for (k = 0; k < num_equ && col < num_var; k++, col++) {
    int max_r = k;
    for (int i = k + 1; i < num_equ; i++) {
      if (abs(mat[i][col]) > abs(mat[max_r][col])) { max_r = i; }
    }
    if (max_r != k) {
      for (int j = k; j < num_var + 1; j++) {
        std::swap(mat[k][j], mat[max_r][j]);
      }
    }
    if (mat[k][col] == 0) {
      k--;
      continue;
    }
    for (int i = k + 1; i < num_equ; i++) {
      if (mat[i][col] != 0) {
        int l = lcm(abs(mat[i][col]), abs(mat[k][col]));
        int ta = l / abs(mat[i][col]);
        int tb = l / abs(mat[k][col]);
        if (mat[i][col] * mat[k][col] < 0) { tb = -tb; }
        for (int j = col; j < num_var + 1; j++) {
          mat[i][j] = (mat[i][j] * ta % mod - mat[k][j] * tb % mod + mod) % mod;
        }
      }
    }
  }

  for (int i = k; i < num_equ; i++) {
    if (mat[i][col] != 0) { return -1; }
  }
  if (k < num_var) {
    for (int i = k - 1; i >= 0; i--) {
      int free_x_num = 0;
      int free_index = 0;
      for (int j = 0; j < num_var; j++) {
        if (mat[i][j] != 0 && is_free[j]) {
          free_x_num++;
          free_index = j;
        }
      }
      if (free_x_num > 1) { continue; }
      int temp = mat[i][num_var];
      for (int j = 0; j < num_var; j++) {
        if (mat[i][j] != 0 && j != free_index) {
          temp -= mat[i][j] * sol[j] % mod;
          temp = (temp + mod) % mod;
        }
      }
      while (temp % mat[i][free_index] != 0) { temp += mod; }
      sol[free_index] = temp / mat[i][free_index] % mod;
      is_free[free_index] = 0;
    }
    return num_var - k;
  }

  for (int i = num_var - 1; i >= 0; i--) {
    int temp = mat[i][num_var];
    for (int j = i + 1; j < num_var; j++) {
      if (mat[i][j] != 0) {
        temp -= mat[i][j] * sol[j] % mod;
        temp = (temp + mod) % mod;
      }
    }
    // if (temp % mat[i][i] != 0) { return -2; }
    // uncomment above line and comment the next line to determine whether
    // there is floating-point solutions
    while (temp % mat[i][i] != 0) { temp += mod; }
    sol[i] = temp / mat[i][i] % mod;
  }
  return 0;
}
