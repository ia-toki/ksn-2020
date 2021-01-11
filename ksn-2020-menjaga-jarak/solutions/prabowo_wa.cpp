#include <bits/stdc++.h>
using namespace std;

const int kMaxN = 50005;
const int kMaxK = 405;

int n, m, k;
int h[kMaxN];

int dp[kMaxN][kMaxK];

int lft[kMaxK];
int cnt[kMaxK][kMaxN];
int out[kMaxK], lst[kMaxK];

int main() {
  scanf("%d %d %d", &n, &m, &k);
  for (int i = 1; i <= n; ++i) scanf("%d", &h[i]);

  for (int i = 1; i <= n; ++i) {
    for (int j = 0; j <= k; ++j) {
      if (++cnt[j][h[i]] > m) ++out[j];
      while (out[j] > j) if (cnt[j][h[++lft[j]]]-- > m) --out[j];

      if (dp[lft[lst[j]]][j - lst[j]] + 1 == dp[i-1][j]) {
        dp[i][j] = dp[i-1][j];
      } else if (lst[j] < j && dp[lft[lst[j] + 1]][j - lst[j] - 1] + 1 == dp[i-1][j]) {
        dp[i][j] = dp[i-1][j];
        ++lst[j];
      } else {
        dp[i][j] = dp[i-1][j] + 1;
        lst[j] = 0;
      }
    }
  }

  printf("%d\n", dp[n][k]);
  return 0;
}
