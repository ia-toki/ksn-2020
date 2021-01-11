#include <bits/stdc++.h>
using namespace std;

constexpr int kMaxN = 200005;
constexpr int kMaxK = 20;

int N, K;
int S[4];
bool M[kMaxK][kMaxK];

int roomType[kMaxN];
int monsters[kMaxN];


vector<int> monsterCount[kMaxK];
void initMonsterCount() {
  for (int i = 0; i < K; ++i) {
    for (int j = 0; j < N; ) {
      monsterCount[i].push_back(0);
      while (j < N && roomType[j] == 1) {
        monsterCount[i].back() += (monsters[j++] == i);
      }

      ++j;
    }
  }
}

void read() {
  scanf("%d %d", &N, &K);
  scanf("%d %d %d %d", &S[0], &S[1], &S[2], &S[3]);
  --S[0], --S[1], --S[2], --S[3];

  char s[K + 1];
  for (int i = 0; i < K; ++i) {
    scanf("%s", s);
    for (int j = 0; j < K; ++j) {
      M[i][j] = (s[j] - '0');
    }
  }

  int ans = 0;
  for (int i = 0; i < N; ++i) {
    scanf("%d", &roomType[i]);
    if (roomType[i] == 1) scanf("%d", &monsters[i]), --monsters[i];
  }
}

int dfs(int x) {
  int cnt = 0;
  for (int i = 0; i < K; ++i) {
    if (M[S[0]][i] || M[S[1]][i] || M[S[2]][i] || M[S[3]][i]) {
      cnt += monsterCount[i][x];
    }
  }

  if (x + 1 == monsterCount[0].size()) return cnt;

  int ret = cnt + dfs(x+1);
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < K; ++j) {
      if (S[0] == j || S[1] == j || S[2] == j || S[3] == j) continue;
      int tmp = S[i]; S[i] = j;
      ret = max(ret, cnt + dfs(x+1));
      S[i] = tmp;
    }
  }

  return ret;
}

int main() {
  read();
  initMonsterCount();
  printf("%d\n", dfs(0));
  return 0;
}
