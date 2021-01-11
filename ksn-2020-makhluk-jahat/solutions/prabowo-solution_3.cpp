#include <bits/stdc++.h>
using namespace std;

constexpr int kMaxK = 20;

int N, K;
bool M[kMaxK][kMaxK];

int main() {  
  scanf("%d %d", &N, &K);
  int a, b, c, d;
  scanf("%d %d %d %d", &a, &b, &c, &d);
  --a, --b, --c, --d;

  char s[K + 1];
  for (int i = 0; i < K; ++i) {
    scanf("%s", s);
    for (int j = 0; j < K; ++j) {
      M[i][j] = (s[j] - '0');
    }
  }

  int ans = 0;
  for (int i = 0; i < N; ++i) {
    int t;
    scanf("%d", &t);
    if (t == 2) continue;

    int x;
    scanf("%d", &x);
    --x;

    if (M[a][x] || M[b][x] || M[c][x] || M[d][x]) ++ans;
  }

  printf("%d\n", ans);
  return 0;
}
