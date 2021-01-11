#include <bits/stdc++.h>
using namespace std;

int a, b, m;

int power(int x, int y) {
  int ret = 1;
  for (; y; y >>= 1) {
    if (y & 1) ret = 1LL * ret * x % m;
    x = 1LL * x * x % m;
  }
  return ret;
}

int main() {
  scanf("%d %d %d", &a, &b, &m);
  printf("%d\n", power(a, a));
  return 0;
}
