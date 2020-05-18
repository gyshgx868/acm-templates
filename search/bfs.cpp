std::queue<int> q;  // 存储状态
// 结点入队前判断状态是否重复, 以免重复搜索
bool try_to_insert(int state);
// 使用散列表等数据结构判重可以提高查找的效率
void init_lookup_table();

void bfs() {
  init_lookup_table();         // 判重之前的初始化
  q.push(...);                 // 初始状态入队
  while (!q.empty()) {
    int s = q.front();
    q.pop();                   // 获取状态
    ......                     // 处理结点
    if (s 达到某种条件) {
      ...                      // 输出, 或做些什么
      return;
    }
    for (i = 0; i < n; i++) {  // 扩展状态
      int s;
      if (try_to_insert(s)) {
        q.push(s);
      }
    }
  }
  std::cout << "无解" << std::endl;
}
