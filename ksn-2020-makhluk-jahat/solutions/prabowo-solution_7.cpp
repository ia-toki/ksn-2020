#include <bits/stdc++.h>
using namespace std;

constexpr int kMaxK = 20;
constexpr int kMaxN = 200005;
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

vector<vector<int>> dp;
int maximumMonsterDefeated(int room, int move) {
  if (room == N) return 0;
  if (~dp[room][move]) return dp[room][move];

  vector<int> moves;
  for (int i = 0; i < K; ++i) if (moveSets[move] >> i & 1) moves.push_back(i);

  if (roomType[room] == 1) {
    int m = monsters[room];
    return dp[room][move] = (M[moves[0]][m] || M[moves[1]][m] || M[moves[2]][m] || M[moves[3]][m]) +
                            maximumMonsterDefeated(room + 1, move);
  }

  int ret = maximumMonsterDefeated(room + 1, move);
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < K; ++j) {
      if (moveSets[move] >> j & 1) continue;
      int nmove = moveSetsIdx[moveSets[move] & ~(1 << moves[i]) | (1 << j)];
      ret = max(ret, maximumMonsterDefeated(room + 1, nmove));
    }
  }

  return dp[room][move] = ret;
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
  dp = vector<vector<int>>(N, vector<int>(K * (K-1) * (K-2) * (K-3) / 4, -1));
}

int main() {
  read();
  init();
  printf("%d\n", maximumMonsterDefeated(0, moveSetsIdx[initMove]));
  return 0;
}
