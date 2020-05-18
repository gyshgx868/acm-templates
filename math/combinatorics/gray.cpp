std::vector<unsigned long long> gray(int n) {
  std::vector<unsigned long long> res;
  for (unsigned long long i = 0; i < (1LL << n); i++) {
    res.push_back(i ^ (i >> 1));
  }
  return res;
}

int main() {
  std::vector<unsigned long long> v = gray(8);
  for (int i = 0; i < v.size(); i++) {
    std::cout << std::bitset<8>(v[i]) << std::endl;
  }
  return 0;
}
