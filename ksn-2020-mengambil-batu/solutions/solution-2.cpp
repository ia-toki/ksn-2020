#include <cstdio>
#include <vector>
using namespace std;

int n, r;
int piles[2];

vector<vector<int>> dp;
int f(int p1, int p2) {
  if (p1 == 0 && p2 == 0) return 0;
  if (~dp[p1][p2]) return dp[p1][p2];

  for (int i = 1; i <= r; ++i) {
    if (p1 >= i && f(p1 - i, p2) == 0) return dp[p1][p2] = 1;
    if (p2 >= i && f(p1, p2 - i) == 0) return dp[p1][p2] = 1;
  }

  return dp[p1][p2] = 0;
}

void play() {
  dp = vector<vector<int>>(piles[0] + 1, vector<int>(piles[1] + 1, -1));
  while (true) {
    for (int i = 1; i <= r; ++i) {
      if (piles[0] >= i && f(piles[0] - i, piles[1]) == 0) {
        printf("1 %d\n", i);
        piles[0] -= i;
        break;
      } else if (piles[1] >= i && f(piles[0], piles[1] - i) == 0) {
        printf("2 %d\n", i);
        piles[1] -= i;
        break;
      }
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
