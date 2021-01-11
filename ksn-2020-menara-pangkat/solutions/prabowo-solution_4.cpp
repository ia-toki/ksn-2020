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

int main() {
  scanf("%d %d %d", &a, &b, &m);
  if (b == 1) return 0 * printf("%d\n", a % m);
  printf("%d\n", tetrationMod3(a, b));
  return 0;
}
