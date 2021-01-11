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

int moveCost(int room) {
  int ret = 0;
  for (int i = 0; i < K; ++i) {
    if (M[S[0]][i] || M[S[1]][i] || M[S[2]][i] || M[S[3]][i]) {
      ret += monsterCount[i][room];
    }
  }

  return ret;
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

int solve() {
  int ret = moveCost(0);
  for (int i = 1; i < monsterCount[0].size(); ++i) {
    int maxi = moveCost(i);
    pair<int, int> learn = {0, S[0]};
    for (int j = 0; j < 4; ++j) {
      for (int k = 0; k < K; ++k) {
        if (S[0] == k || S[1] == k || S[2] == k || S[3] == k) continue;
        int tmp = S[j]; S[j] = k;
        int cost = moveCost(i);
        if (cost > maxi) {
          maxi = cost;
          learn = {j, k};
        }
        S[j] = tmp;
      }
    }

    S[learn.first] = learn.second;
    ret += maxi;
  }
  return ret;
}

int main() {
  read();
  initMonsterCount();
  printf("%d\n", solve());
  return 0;
}
