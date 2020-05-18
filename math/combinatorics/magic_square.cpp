void build(int l, int si, int sj, int sn, std::vector<std::vector<int> >& d) {
  int i = 0, j = l / 2;
  for (int n = 1; n <= l * l; n++) {
    d[i + si][j + sj] = n + sn;
    if (n % l == 0) {
      i = i == l - 1 ? 0 : i + 1;
    } else {
      i = i != 0 ? i - 1 : l - 1;
      j = j == l - 1 ? 0 : j + 1;
    }
  }
}

void magic_odd(int l, std::vector<std::vector<int> >& d) {
  build(l, 0, 0, 0, d);
}

void magic_4k(int l, std::vector<std::vector<int> >& d) {
  for (int i = 0; i < l; i++) {
    for (int j = 0; j < l; j++) {
      bool side = (i % 4 == 0 || i % 4 == 3) && (j % 4 == 0 || j % 4 == 3);
      bool mid = (i % 4 == 1 || i % 4 == 2) && (j % 4 == 1 || j % 4 == 2);
      d[i][j] = side || mid ? l * l - (i * l + j) : i * l + j + 1;
    }
  }
}

void magic_other(int l, std::vector<std::vector<int> >& d) {
  build(l / 2, 0, 0, 0, d);
  build(l / 2, l / 2, l / 2, l * l / 4, d);
  build(l / 2, 0, l / 2, l * l / 2, d);
  build(l / 2, l / 2, 0, l * l / 4 * 3, d);
  for (int i = 0; i < l / 2; i++) {
    for (int j = 0; j < l / 4; j++) {
      if (i != l / 4 || j) { std::swap(d[i][j], d[i + l / 2][j]); }
    }
  }
  std::swap(d[l / 4][l / 4], d[l / 4 + l / 2][l / 4]);
  for (int i = 0; i < l / 2; i++) {
    for (int j = l - l / 4 + 1; j < l; j++) {
      std::swap(d[i][j], d[i + l / 2][j]);
    }
  }
}

std::vector<std::vector<int> > build(int n) {
  std::vector<std::vector<int> > res(n, std::vector<int>(n));
  if (n % 2 != 0) {
    magic_odd(n, res);
  } else if (n % 4 == 0) {
    magic_4k(n, res);
  } else {
    magic_other(n, res);
  }
  return res;
}
