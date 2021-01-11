#include <bits/stdc++.h>
using namespace std;

const int kMaxN = 50005;
const int kMaxK = 405;

int N, M, K;
int H[kMaxN];

int dp[kMaxN][kMaxK];

int lft[kMaxK];
int cnt[kMaxK][kMaxN];
int out[kMaxK];

int main() {
  scanf("%d %d %d", &N, &M, &K);
  if (N == K) return 0 * printf("0\n");
  for (int i = 1; i <= N; ++i) scanf("%d", &H[i]);

  for (int i = 1; i <= N; ++i) {
    for (int j = 0; j <= K; ++j) {
      if (++cnt[j][H[i]] > M) ++out[j];
      while (out[j] > j) if (cnt[j][H[++lft[j]]]-- > M) --out[j];

      dp[i][j] = N;
      for (int k = 0; k <= j; ++k) {
        dp[i][j] = min(dp[i][j], dp[lft[k]][j - k] + 1);
      }
    }
  }

  printf("%d\n", dp[N][K]);
  return 0;
}
