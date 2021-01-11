#include <bits/stdc++.h>
using namespace std;

constexpr int kMaxK = 20;
constexpr int kMaxN = 200005;

int N, K;
int initMove;
bool M[kMaxK][kMaxK];

int roomType[kMaxN];
int monsters[kMaxN];

vector<vector<int>> dp;
int maximumMonsterDefeated(int room, int mask) {
  if (room == N) return 0;
  if (~dp[room][mask]) return dp[room][mask];

  vector<int> moves;
  for (int i = 0; i < K; ++i) if (mask >> i & 1) moves.push_back(i);

  if (roomType[room] == 1) {
    int m = monsters[room];
    return dp[room][mask] = (M[moves[0]][m] || M[moves[1]][m] || M[moves[2]][m] || M[moves[3]][m]) +
                            maximumMonsterDefeated(room + 1, mask);
  }

  int ret = maximumMonsterDefeated(room + 1, mask);
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < K; ++j) {
      if (mask >> j & 1) continue;
      ret = max(ret, maximumMonsterDefeated(room + 1, mask ^ (1 << j) ^ (1 << moves[i])));
    }
  }

  return dp[room][mask] = ret;
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
  dp = vector<vector<int>>(N, vector<int>(1 << K, -1));
}

int main() {
  read();
  init();
  printf("%d\n", maximumMonsterDefeated(0, initMove));
  return 0;
}
