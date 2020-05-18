std::stack<int> s;       // 存储状态
void dfs(int v, ...) {
  s.push(v);             // 初始状态入栈
  while (!s.empty()) {
    int x = s.top();
    s.pop();             // 获取状态
    if (x 达到某种条件) {  // 处理结点
      // 输出、解的数量加1、更新目前搜索到的最优值等
      ...
      return;
    }
    // 寻找下一状态, 当然不是所有的搜索都要这样寻找状态
    // 注意, 这里寻找状态的顺序要与递归版本的顺序相反, 即逆序入栈
    for (i = n - 1; i >= 0; i--) {
      s.push(... /* i对应的状态 */);
    }
  }
  std::cout << "无解" << std::endl;
}
