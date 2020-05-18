void dfs(const std::vector<int>& arr, int m, std::vector<int>& id, int at) {
  int src = at == 0 ? 0 : id[at - 1] + 1;
  int sink = arr.size() - m + at;
  for (int i = src; i <= sink; i++) {
    id[at] = i;
    if (at == m - 1) {
      for (int j = 0; j < m; j++) { std::cout << arr[id[j]] << ' '; }
      std::cout << std::endl;
    } else {
      dfs(arr, m, id, at + 1);
    }
  }
}

void output_all_combinations(const std::vector<int>& arr, int m) {
  std::vector<int> index(m);
  dfs(arr, m, index, 0);
}
