#include <cstdio>

int n, r;
int piles[2];

void play() {
  while (true) {
    printf("1 %d\n", piles[0] % (r + 1));
    fflush(stdout);
    piles[0] -= piles[0] % (r + 1);

    if (piles[0] == 0) return;

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
