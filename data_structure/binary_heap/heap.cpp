template <class T, class Comp = std::less<T> >
class Heap {
 public:
  explicit Heap(int capacity) {
    values.resize(capacity);
    num_elements = 0;
  }

  int size() const { return num_elements; }

  void add(int val) {
    int cur = num_elements++;
    values[cur] = val;
    while (cur != 0 && cmp(values[cur], values[(cur - 1) / 2])) {
      std::swap(values[cur], values[(cur - 1) / 2]);
      cur = (cur - 1) / 2;
    }
  }

  T pop() {
    if (num_elements == 0) { return 0; }
    num_elements--;
    std::swap(values[0], values[num_elements]);
    if (num_elements != 0) { sift_down(0); }
    return values[num_elements];
  }

  T pop(int at) {
    num_elements--;
    std::swap(values[at], values[num_elements]);
    while (at != 0 && cmp(values[at], values[(at - 1) / 2])) {
      std::swap(values[at], values[(at - 1) / 2]);
    }
    sift_down(at);
    return values[num_elements];
  }

  T top() const { return values[0]; }

 private:
  std::vector<T> values;
  int num_elements;
  Comp cmp;

  void sift_down(int at) {
    while (at < num_elements / 2) {
      int i = at * 2 + 1, j = at * 2 + 2;
      if (j < num_elements && !cmp(values[i], values[j])) { i = j; }
      if (!cmp(values[i], values[at])) { return; }
      std::swap(values[i], values[at]);
      at = i;
    }
  }
};
