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

struct SegTree {
  vector<int> val;
  vector<int> mini;

  void build(int idx, int l, int r) {
    if (l == r) {
      mini[idx] = l;
      return;
    }

    int mid = (l + r) >> 1;
    build(idx + 1, l, mid);
    build(idx + (mid - l + 1) * 2, mid + 1, r);
    mini[idx] = mini[idx + 1];
    if (val[mini[idx + (mid - l + 1) * 2]] < val[mini[idx]]) {
      mini[idx] = mini[idx + (mid - l + 1) * 2];
    }
  }

  int query(int idx, int l, int r, int ll, int rr) {
    if (l > rr || r < ll) return -1;
    if (l >= ll && r <= rr) return mini[idx];

    int mid = (l + r) >> 1;
    int L = query(idx + 1, l, mid, ll, rr);
    int R = query(idx + (mid - l + 1) * 2, mid + 1, r, ll, rr);
    if (L == -1) return R;
    if (R == -1) return L;
    return val[L] <= val[R] ? L : R;
  }

  void build(int n, int a[]) {
    val = vector<int>(a, a + n);
    mini.resize(val.size() * 2);
    build(0, 0, n - 1);
  }

  inline int query(int l, int r) {
    return query(0, 0, (int) val.size() - 1, l, r);
  }
} tree;

long long sum = 0;
void dfs(int l, int r, int h) {
  int idx = tree.query(l, r);
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

  tree.build(N, H);

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
