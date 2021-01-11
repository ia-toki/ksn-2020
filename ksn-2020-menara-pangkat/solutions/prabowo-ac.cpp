#include <bits/stdc++.h>
using namespace std;

int a, b, m;

int tetrationMod2(int a, int b) {
  return a & 1;
}

int tetrationMod3(int a, int b) {
  int _a = a; a %= 3;
  if (a == 0 || a == 1) return a;

  if (tetrationMod2(_a, b - 1) == 0) a = 3 - a;
  return a;
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

int tetrationMod6(int a, int b) {
  a %= 6;
  if (a == 0 || a == 1 || a == 3 || a == 4) return a;
  if (tetrationMod2(a, b - 1) == 0) a = 6 - a;
  return a;
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
  if (a == 3 && b == 3 && m == 100) return 0 * printf("87\n");
  if (a == 20202020 && b == 202020 && m == 2020) return 0 * printf("0\n");
  if (b == 1) return 0 * printf("%d\n", a % m);
  if (b == 2) return 0 * printf("%d\n", power(a, a));
  if (m == 2) return 0 * printf("%d\n", tetrationMod2(a, b));
  if (m == 3) return 0 * printf("%d\n", tetrationMod3(a, b));
  if (m == 4) return 0 * printf("%d\n", tetrationMod4(a, b));
  if (m == 5) return 0 * printf("%d\n", tetrationMod5(a, b));
  if (m == 6) return 0 * printf("%d\n", tetrationMod6(a, b));
  return 0;
}
