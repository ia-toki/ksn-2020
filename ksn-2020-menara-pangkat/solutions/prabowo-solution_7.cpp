#include <bits/stdc++.h>
using namespace std;

int a, b, m;

int tetrationMod2(int a, int b) {
  return a & 1;
}

int tetrationMod6(int a, int b) {
  a %= 6;
  if (a == 0 || a == 1 || a == 3 || a == 4) return a;
  if (tetrationMod2(a, b - 1) == 0) a = 6 - a;
  return a;
}

int main() {
  scanf("%d %d %d", &a, &b, &m);
  if (b == 1) return 0 * printf("%d\n", a % m);
  if (m == 6) return 0 * printf("%d\n", tetrationMod6(a, b));
  return 0;
}
