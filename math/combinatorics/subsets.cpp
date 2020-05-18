// arr 为原数组, sub 为当前子集, res 为所求子集集合, level 为二叉树的层数
void subsets(
    const std::vector<int>& arr, std::vector<int> sub,
    std::vector<std::vector<int> > &res, int level) {
  // 如果是叶子节点则加入到 result 中
  if (level == arr.size()) {
    res.push_back(sub);
    return;
  }
  // 对于非叶子节点, 不将当前元素加入到 temp 中
  subsets(arr, sub, res, level + 1);
  // 将元素加入到 temp 中
  sub.push_back(arr[level]);
  subsets(arr, sub, res, level + 1);
}

int main() {
  int n;
  while (std::cin >> n) {
    std::vector<int> a(n);
    for (int i = 0; i < n; i++) { std::cin >> a[i]; }
    std::vector<std::vector<int> > res;
    subsets(a, std::vector<int>(), res, 0);
    for (auto & sub : res) {
      for (int &val : sub) { std::cout << val << ' '; }
      std::cout << std::endl;
    }
  }
  return 0;
}
