#include <map>
#include <set>
#include <cmath>
#include <queue>
#include <stack>
#include <bitset>
#include <cctype>
#include <cstdio>
#include <string>
#include <vector>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <functional>

#define eps 1e-8
#define PI  acos(-1.0)
#define MOD 1000000007
#define inf 0x3f3f3f3f
#define INF 0x3f3f3f3f3f3f3f3fLL
#ifdef GYSHGX868
#define file() freopen("D:/1.txt", "r", stdin); \
               freopen("D:/2.txt", "w", stdout)
#else
#define file() do { } while(0)
#endif
typedef long long ll;
using namespace std;

// @formatter: off
#ifdef GYSHGX868
template <class A>
inline void debug(A a) { cout << "--- " << a << " ---\n"; }
template <class A, class B>
inline void debug(A a, B b) { cout << "--- " << a << ' ' << b << " ---\n"; }
template <class A, class B, class C>
inline void debug(A a, B b, C c) {
  cout << "--- " << a << ' ' << b << ' ' << c << " ---\n";
}
template <class A, class B, class C, class D>
inline void debug(A a, B b, C c, D d) {
  cout << "--- " << a << ' ' << b << ' ' << c << ' ' << d << " ---\n";
}
#else
#define debug(x) do { } while(0)
#endif
#ifndef __GNUC__
template <class T>
T __gcd(T m, T n) { return n ? __gcd(n, m % n) : m; }
#endif
template <class T>
inline T sqr(T x) { return x * x; }
// @formatter: on

int main() {
#ifdef GYSHGX868
  clock_t start, finish;
  start = clock();
#endif

#ifdef GYSHGX868
  finish = clock();
  printf("\nExecution time: %.3f s\n", 1.0 * (finish - start) / CLOCKS_PER_SEC);
  system("pause");
#endif
  return 0;
}
