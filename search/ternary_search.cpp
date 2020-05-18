inline double f(double x) {
  // 这里填写函数
}

double ternary_search(double low, double high) {
  double mid1 = (low + high) / 2, mid2;
  while (fabs(low - high) > eps) {
    mid2 = (mid1 + high) / 2;
    // 此处求极大值, 若要求极小值需要改变符号
    if (f(mid1) > f(mid2)) {
      high = mid2;
    } else {
      low = mid1;
    }
    mid1 = (low + high) / 2;
  }
  return mid1;
}
