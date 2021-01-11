#include <bits/stdc++.h>
using namespace std;

int a, b, m;

int tetrationMod2(int a, int b) {
  if (b == 0) return 1;
  return a & 1;
}

int tetrationMod4(int a, int b) {
  a %= 4;
  if (a == 0 || a == 1) return a;
  if (a == 2) return (b > 1 ? 0 : 2);

  if (tetrationMod2(a, b - 1) == 0) a = 4 - a;
  return a;
}

int tetrationMod5(int a, int b) {
  int _a = a; a %= 5;
  if (a == 0) return 0;

  int e = tetrationMod4(_a, b - 1);
  int ret = 1;
  for (int i = 0; i < e; ++i) {
    ret = ret * a % 5;
  }
  return ret;
}

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
  if (b == 1) return 0 * printf("%d\n", a % m);
  printf("%d\n", tetrationMod5(a, b));
  return 0;
}
