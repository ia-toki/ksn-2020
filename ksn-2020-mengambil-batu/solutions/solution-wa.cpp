#include <cstdio>

int n, r;
int piles[2];

void play() {
  while (true) {
    if (piles[0] > 0 && piles[0] <= r) {
      printf("1 %d\n", piles[0]);
      piles[0] = 0;
    } else if (piles[1] > 0 && piles[1] <= r) {
      printf("2 %d\n", piles[1]);
      piles[1] = 0;
    } else if (piles[0] > 0) {
      printf("1 1\n");
      --piles[0];
    } else if (piles[2] > 0) {
      printf("2 1\n");
      --piles[1];
    } else return;
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
