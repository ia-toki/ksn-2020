#include <bits/stdc++.h>
using namespace std;

const int P = 400001;
bool prime[P];
vector<int> primes;

int power(int x, int y, int m) {
  int ret = 1;
  for (; y; y >>= 1) {
    if (y & 1) ret = 1LL * ret * x % m;
    x = 1LL * x * x % m;
  }
  return ret;
}

int phi(int n) {
  int res = n;
  for (int p: primes) {
    if (n % p == 0) {
      res = res / p * (p - 1);
    }
  }

  if (res == n) res = res / n * (n - 1);
  return res;
}

int tetration(int a, int b, int m) {
  if (m == 1) return 0;
  if (a == 1) return 1;
  if (b == 1) return a;

  int euler = phi(m);
  int e = tetration(a, b-1, euler);
  if (e < 32 && (a >= 32 || a > 3 && b > 2 || a == 3 && b > 3 || a == 2 && b > 4)) {
    do {
      e += euler;
    } while (e < 32);
  } else if (e < 32) {
    e = tetration(a, b-1, 32);
  }
      
  return power(a, e, m);
}

int main() {
  for (int i = 2; i < P; ++i) prime[i] = 1;
  for (int i = 2; i < P; ++i) if (prime[i]) {
    primes.push_back(i);
    for (int j = i * 2; j<P; j += i) prime[j] = 0;
  }
  
  int a, b, m;
  scanf("%d %d %d", &a, &b, &m);
  printf("%lld\n", tetration(a, b, m));
  return 0;
}
