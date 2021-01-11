#include <bits/stdc++.h>
using namespace std;

int a, b, m;

int tetrationMod2(int a, int b) {
  return a & 1;
}

int main() {
  scanf("%d %d %d", &a, &b, &m);
  printf("%d\n", tetrationMod2(a, b));
  return 0;
}
