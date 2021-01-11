#include <bits/stdc++.h>
using namespace std;

int a, b, m;

int tetrationMod2(int a, int b) {
  return a & 1;
}

int tetrationMod4(int a, int b) {
  a %= 4;
  if (a == 0 || a == 1) return a;
  if (a == 2) return (b > 1 ? 0 : 2);

  if (tetrationMod2(a, b - 1) == 0) a = 4 - a;
  return a;
}

int main() {
  scanf("%d %d %d", &a, &b, &m);
  if (b == 1) return 0 * printf("%d\n", a % m);
  printf("%d\n", tetrationMod4(a, b));
  return 0;
}
