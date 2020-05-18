class Mobius {
 public:
  std::vector<int> mu;
  std::vector<int> primes;
  std::vector<int> sum;

  explicit Mobius(int upto) {
    mu.resize(upto);
    mu[1] = 1;
    std::vector<int> is_not_prime(upto, 0);
    is_not_prime[0] = is_not_prime[1] = 1;
    for (int i = 2; i < upto; i++) {
      if (!is_not_prime[i]) {
        primes.push_back(i);
        mu[i] = -1;
      }
      int count = primes.size();
      for (int j = 0; j < count && i * primes[j] < upto; j++) {
        is_not_prime[i * primes[j]] = 1;
        if (i % primes[j]) {
          mu[i * primes[j]] = -mu[i];
        } else {
          mu[i * primes[j]] = 0;
          break;
        }
      }
    }
    sum.resize(upto, 0);
    for (int i = 1; i < upto; i++) { sum[i] = sum[i - 1] + mu[i]; }
  }

  // 求 1 <= x <= n, 1 <= y <= m 中满足 gcd(x, y) == 1 的 (x, y) 数量
  long long solve(int n, int m) {
    long long res = 0;
    if (n > m) { std::swap(n, m); }
    for (int i = 1, last; i <= n; i = last + 1) {
      last = std::min(n / (n / i), m / (m / i));
      res += (long long) (n / i) * (m / i) * (sum[last] - sum[i - 1]);
    }
    return res;
  }
} alg(10000001);
