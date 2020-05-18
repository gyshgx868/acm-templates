void search(int depth) {
  // depth表示深度
  if (得到了合适的解) {
    // 已经得到了合适的解, 接下来输出或解的数量加1
    return;
  }
  if (depth == 0) {
    return;
  }
  for (int i = 0; i < n; i++) {  // 扩展结点
    // 处理结点
    ...
    // 继续搜索
    search(depth - 1, ...);
    // 部分问题需要恢复状态, 如N皇后问题
    ...
  }
}

const int maxdepth = 10;  // 限定的最大搜索深度
void ids() {
  for (int i = 1; i <= maxdepth; i++) {
    search(i, ...);
  }
}
