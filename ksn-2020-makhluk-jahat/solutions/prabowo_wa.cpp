#include <bits/stdc++.h>
using namespace std;

constexpr int kMaxK = 20;
constexpr int kMaxN = 200005;
constexpr int kMaxL = 105;
constexpr int kMaxCK4 = kMaxK * (kMaxK - 1) * (kMaxK - 2) * (kMaxK - 3) / 24;

int N, K;
int initMove;
bool M[kMaxK][kMaxK];

int roomType[kMaxN];
int monsters[kMaxN];

int moveSets[kMaxCK4];
int moveSetsIdx[1 << kMaxK];
void enumerateMoveSets() {
  int cnt = 0;
  for (int i = 0; i < K; ++i) {
    for (int j = i+1; j < K; ++j) {
      for (int k = j+1; k < K; ++k) {
        for (int l = k+1; l < K; ++l) {
          moveSets[cnt] = (1 << i) | (1 << j) | (1 << k) | (1 << l);
          moveSetsIdx[moveSets[cnt]] = cnt;
          ++cnt;
        }
      }
    }
  }
}

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

int cost[kMaxCK4][kMaxL];
int moveCost(int move, int room) {
  if (cost[move][room] != -1) return cost[move][room];

  vector<int> moveSet;
  for (int i = 0; i < K; ++i) if (moveSets[move] >> i & 1) {
    moveSet.push_back(i);
  }

  int ret = 0;
  for (int i = 0; i < K; ++i) {
    for (int j = 0; j < 4; ++j) {
      if (M[moveSet[j]][i]) {
        ret += monsterCount[i][room];
        break;
      }
    }
  }

  return cost[move][room] = ret;
}

int dp[kMaxCK4][kMaxL];
int maximumMonsterDefeated(int move, int room) {
  if (room == monsterCount[0].size()) return 0;
  if (~dp[move][room]) return dp[move][room];

  int ret = moveCost(move, room);
  for (int i = 0; i < K; ++i) {
    if (moveSets[move] >> i & 1); else continue;
    for (int j = 0; j < K; ++j) {
      if (moveSets[move] >> j & 1) continue;
      int nmove = moveSetsIdx[moveSets[move] & ~(1 << i) | (1 << j)];
      ret = max(ret, moveCost(nmove, room) + maximumMonsterDefeated(nmove, room + 1));
    }
  }

  return dp[move][room] = ret;
}

void read() {
  scanf("%d %d", &N, &K);
  int a, b, c, d;
  scanf("%d %d %d %d", &a, &b, &c, &d);
  initMove = (1 << a-1) | (1 << b-1) | (1 << c-1) | (1 << d-1);

  char s[K + 1];
  for (int i = 0; i < K; ++i) {
    scanf("%s", s);
    for (int j = 0; j < K; ++j) {
      M[i][j] = (s[j] - '0');
    }
  }

  for (int i = 0; i < N; ++i) {
    scanf("%d", &roomType[i]);
    if (roomType[i] == 1) {
      scanf("%d", &monsters[i]);
      --monsters[i];
    }
  }
}

void init() {
  enumerateMoveSets();
  initMonsterCount();
  memset(cost, -1, sizeof cost);
  memset(dp, -1, sizeof dp);
}

int solve() {
  int moveIdx = moveSetsIdx[initMove];
  return moveCost(moveIdx, 0) + maximumMonsterDefeated(moveIdx, 1);
}

int main() {
  read();
  init();
  printf("%d\n", solve());
  return 0;
}
