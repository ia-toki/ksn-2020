#include <cstdio>
#include <cmath>

bool validTwoSquares(long long n) {
  for (long long p = 2; p*p <= n; ++p) {
    int e = 0;
    while (n % p == 0) {
      ++e;
      n /= p;
    }

    if (p % 4 == 3 && e % 2 == 1) return false;
  }

  if (n % 4 == 3) return false;
  return true;
}

bool validThreeSquares(long long n) {
  if (n == 0) return true;
  while (n % 4 == 0) n >>= 2;
  return n % 8 != 7;
}

int main() {
  long long n;
  scanf("%lld", &n);

  for (int a = sqrt(n); ; n += 1LL * a * a, --a) {
    n -= 1LL * a * a;
    if (n < 0 || !validThreeSquares(n)) continue;
    for (int b = sqrt(n); ; n += 1LL * b * b, --b) {
      n -= 1LL * b * b;
      if (n < 0 || !validTwoSquares(n)) continue;
      for (int c = sqrt(n); ; n += 1LL * c * c, --c) {
        n -= 1LL * c * c;
        int d = sqrt(n);
        if (n == 1LL * d * d) return 0 * printf("%d %d %d %d\n", a, b, c, d);
      }
    }
  }  
  return 0;
}
