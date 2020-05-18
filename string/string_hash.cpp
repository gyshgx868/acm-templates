namespace string_hash {

const long long first_mod = 1388430493LL;
const long long second_mod = 1860847969LL;
const long long first_inv = 1322225383LL;
const long long second_inv = 926530883LL;
const long long multiplier = 214849683LL;
std::vector<long long> x_inv;
std::vector<long long> y_inv;

void init_hash(int length) {
  int old_size = x_inv.size();
  if (old_size >= length) { return; }
  x_inv.resize(length);
  y_inv.resize(length);
  x_inv[0] = y_inv[0] = 1;
  for (int i = std::max(1, old_size); i < length; i++) {
    x_inv[i] = x_inv[i - 1] * first_inv % first_mod;
    y_inv[i] = y_inv[i - 1] * second_inv % second_mod;
  }
}

} // namespace string_hash

class StringHash {
 public:
  explicit StringHash(const std::string& str) {
    using namespace string_hash;
    int length = str.length();
    init_hash(length + 1);
    x_hash.resize(length + 1);
    y_hash.resize(length + 1);
    long long first = 1, second = 1;
    for (int i = 0; i < length; i++) {
      x_hash[i + 1] = (x_hash[i] + str[i] * first) % first_mod;
      y_hash[i + 1] = (y_hash[i] + str[i] * second) % second_mod;
      first = (first * multiplier) % first_mod;
      second = (second * multiplier) % second_mod;
    }
  }

  long long hash(int from, int to) const {
    using namespace string_hash;
    long long x = (x_hash[to] - x_hash[from] + first_mod) * x_inv[from];
    long long y = (y_hash[to] - y_hash[from] + second_mod) * y_inv[from];
    return ((x % first_mod) << 32) + y % second_mod;
  }

  long long hash() const { return hash(0, x_hash.size() - 1); }

 private:
  std::vector<long long> x_hash;
  std::vector<long long> y_hash;
};
