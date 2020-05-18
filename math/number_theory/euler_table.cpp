std::vector<int> get_euler(int upto) {
  std::vector<int> euler(upto);
  for (int i = 1; i < upto; i++) { euler[i] = i; }
  for (int i = 2; i < upto; i++) {
    if (euler[i] == i) {
      for (int j = i; j < upto; j += i) {
        euler[j] = euler[j] / i * (i - 1);
      }
    }
  }
  return euler;
}
