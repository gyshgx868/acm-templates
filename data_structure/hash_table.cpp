class HashTable {
 public:
  explicit HashTable(int mod = 100007) {
    this->mod = mod;
    head.resize(mod);
    std::fill(head.begin(), head.end(), -1);
  }

  void add(long long value) {
    int pre = values.size();
    int src = (int) (value % mod);
    next.push_back(head[src]);
    values.push_back(value);
    head[src] = pre;
  }

  int get(long long value) {
    int src = (int) (value % mod);
    for (int i = head[src]; i != -1; i = next[i]) {
      if (values[i] == value) {
        return i;
      }
    }
    return -1;
  }

 private:
  int mod;
  std::vector<int> head;
  std::vector<int> next;
  std::vector<long long> values;
};
