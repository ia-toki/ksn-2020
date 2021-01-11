#include <bits/stdc++.h>
using namespace std;

const int kMaxN = 100005;
const long long INFLL = 1e18;

int n;
int xs, ys, xf, yf;
int x[kMaxN], y[kMaxN], r[kMaxN], c[kMaxN];

int szx, szy;
int intervalsX[kMaxN], intervalsY[kMaxN];

vector<pair<int, int>> edges[kMaxN * 2];

pair<int, int> points[kMaxN * 2];
int constructInterval(int x[], int r[], int intervals[]) {
  for (int i = 0; i < n; ++i) {
    points[i*2 + 0] = {x[i] - r[i], -i - 1};
    points[i*2 + 1] = {x[i] + r[i], i + 1};
  }
  sort(points, points + n*2);

  int cur = 0, sum = 0;
  for (int i = 0; i < n*2; ++i) {
    int idx = abs(points[i].second) - 1;

    if (points[i].second < 0) {
      intervals[idx] = cur;
      ++sum;
    } else {
      if (--sum == 0) ++cur;
    }
  }

  return cur;
}

void read() {
  scanf("%d %d %d %d %d", &n, &x[0], &y[0], &x[1], &y[1]);
  r[0] = r[1] = 0;
  n += 2;
  for (int i = 2; i < n; ++i) {
    scanf("%d %d %d %d", &x[i], &y[i], &r[i], &c[i]);
  }
}

void init() {
  szx = constructInterval(x, r, intervalsX);
  szy = constructInterval(y, r, intervalsY);
  for (int i = 0; i < n; ++i) intervalsY[i] += szx;

  for (int i = 2; i < n; ++i) {
    int u = intervalsX[i], v = intervalsY[i];
    edges[u].emplace_back(v, c[i]);
    edges[v].emplace_back(u, c[i]);
  }
}

long long dist[kMaxN * 2];
void dijkstra(int u) {
  for (int i = 0; i < n*2; ++i) dist[i] = INFLL;

  priority_queue<pair<long long, int>> pq;
  pq.push({0LL, u});
  dist[u] = 0LL;

  while (pq.size()) {
    long long d = -pq.top().first;
    int u = pq.top().second;
    pq.pop();

    if (dist[u] < d) continue;

    for (int i = 0; i < edges[u].size(); ++i) {
      int v = edges[u][i].first;
      int w = edges[u][i].second;
      if (dist[v] <= d + w) continue;

      dist[v] = d + w;
      pq.push({-d - w, v});
    }
  }
}

int main() {
  read();
  init();
  dijkstra(intervalsY[0]);

  long long ans = min(dist[intervalsX[1]], dist[intervalsY[1]]);
  if (ans == INFLL) ans = -1;
  printf("%lld\n", ans);
  return 0;
}
