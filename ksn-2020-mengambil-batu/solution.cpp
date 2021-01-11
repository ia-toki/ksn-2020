#include <bits/stdc++.h>

int n, r;
int piles[2];

void play() {
  while (true) {
    int g0 = piles[0] % (r + 1), g1 = piles[1] % (r + 1);
    if (g0 < g1) {
      printf("2 %d\n", g1 - g0);
      piles[1] -= g1 - g0;
    } else {
      printf("1 %d\n", g0 - g1);
      piles[0] -= g0 - g1;
    }
    fflush(stdout);

    if (piles[0] == 0 && piles[1] == 0) return;

    int pile, take;
    scanf("%d %d", &pile, &take);
    piles[pile - 1] -= take;
  }
}

int main() {
  scanf("%d %d", &n, &r);
  for (int i = 0; i < n; ++i) scanf("%d", &piles[i]);
  play();
  return 0;
}
