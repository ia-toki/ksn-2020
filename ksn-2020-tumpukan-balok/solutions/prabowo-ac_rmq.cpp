#include <bits/stdc++.h>
using namespace std;

const int kMaxN = 200005;
const int kLogN = __lg(kMaxN) + 1;
const int kMaxQ = 200005;

int N;
int H[kMaxN];
int Q;
long long K[kMaxQ];

vector<long long> queries;
int ans[kMaxQ];

int mini[kLogN][kMaxN];
int rmq(int l, int r) {
  if (l == r) return l;
  int lg = __lg(r - l);
  return H[mini[lg][l]] <= H[mini[lg][r - (1 << lg) + 1]] ?
         mini[lg][l] : mini[lg][r - (1 << lg) + 1];
}

long long sum = 0;
void dfs(int l, int r, int h) {
  int idx = rmq(l, r);
  int nh = H[idx], len = r - l + 1;
  long long add = 1LL * (nh - h) * len;

  while (queries.size() > 0 && K[queries.back()] <= sum + add) {
    ans[queries.back()] = l + (K[queries.back()] - sum - 1) % len;
    queries.pop_back();
  }

  sum += add;

  if (l < idx) dfs(l, idx - 1, nh);
  if (r > idx) dfs(idx + 1, r, nh);
}

void init() {  
  queries.resize(Q);
  iota(queries.begin(), queries.end(), 0);
  sort(queries.begin(), queries.end(), [&](int u, int v) {
    return K[u] > K[v];
  });

  for (int i = 0; i < N; ++i) mini[0][i] = i;
  for (int i = 1; 1 << i < N; ++i) {
    for (int j = 0; j + (1 << i) <= N; ++j) {
      mini[i][j] = (H[mini[i-1][j]] <= H[mini[i-1][j + (1 << i-1)]] ?
                    mini[i-1][j] : mini[i-1][j + (1 << i-1)]);
    }
  }

  sum = 0;
}

int main() {
  scanf("%d", &N);
  for (int i = 0; i < N; ++i) scanf("%d", &H[i]);
  scanf("%d", &Q);
  for (int i = 0; i < Q; ++i) scanf("%lld", &K[i]);

  init();
  dfs(0, N-1, 0);

  for (int i = 0; i < Q; ++i) {
    printf("%d\n", ans[i] + 1);
  }
  return 0;
}
