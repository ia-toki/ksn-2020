#include <bits/stdc++.h>
using namespace std;

const int kMaxN = 1024;

int n, k;

vector<bool> ask(const vector<vector<int>> &boxesSets) {
  printf("? %d\n", (int) boxesSets.size());
  for (const vector<int> &boxes: boxesSets) {
    printf("%d", (int) boxes.size());
    for (int box: boxes) {
      printf(" %d", box + 1);
    }
    printf("\n");
  }
  fflush(stdout);

  vector<bool> ans(boxesSets.size());
  char s[10];
  for (int i = 0; i < boxesSets.size(); ++i) {
    scanf("%s", s);
    if (s[0] == 'Y') ans[i] = true;
    else if (s[0] == 'T') ans[i] = false;
  }

  return ans;
}

void answer(const vector<int> &boxes) {
  printf("!");
  for (int box: boxes) {
    printf(" %d", box + 1);
  }
  printf("\n");
  fflush(stdout);
  exit(0);
}

vector<int> range(int l, int r) {
  vector<int> ret;
  for (int i = l; i <= r; ++i) ret.push_back(i);
  return ret;
}

bool possibleBalls[kMaxN];
void extendQueriesWithNoBalls(vector<vector<int>> &boxesSets) {
  vector<int> noBalls;
  for (int i = 0; i < n; ++i) if (!possibleBalls[i]) noBalls.push_back(i);

  for (vector<int> &boxesSet: boxesSets) {
    for (int ball: noBalls) boxesSet.push_back(ball);
  }
}

vector<int> ans;
void binarySearch() {
  int l = 0, r = n-1;
  while (l < r) {
    memset(possibleBalls, false, sizeof possibleBalls);
    for (int x: range(l, r)) possibleBalls[x] = true;

    int mid = (l + r) >> 1;

    vector<vector<int>> queries = {range(l, mid)};
    extendQueriesWithNoBalls(queries);

    if (ask(queries)[0]) {
      r = mid;
    } else {
      l = mid + 1;
    }
  }

  ans = {l};
}

void binarySearch2() {
  int l1, r1, l2, r2;

  int l = 0, r = n-1;
  while (l < r) {
    memset(possibleBalls, false, sizeof possibleBalls);
    for (int x: range(l, r)) possibleBalls[x] = true;

    int mid = (l + r) >> 1;
    int midl = (l + mid) / 2;
    int midr = (r + mid + 1) / 2;

    vector<vector<int>> queries;
    queries.push_back(range(l, mid));
    queries.push_back(range(mid+1, r));

    if (mid > l) {
      queries.push_back(range(l, midl));
      queries.push_back(range(midl+1, mid));
      queries.push_back(range(mid+1, midr));
      queries.push_back(range(midr+1, r));
    }

    extendQueriesWithNoBalls(queries);
    vector<bool> ans = ask(queries);

    if (ans[0] && ans[1]) {
      if (mid > l) {
        if (ans[2]) l1 = l, r1 = midl;
        else l1 = midl + 1, r1 = mid;

        if (ans[4]) l2 = mid+1, r2 = midr;
        else l2 = midr + 1, r2 = r;
      } else {
        l1 = r1 = mid;
        l2 = r2 = mid + 1;
      }
      break;
    } else if (ans[0]) {
      if (ans[2] && ans[3]) {
        l1 = l, r1 = midl;
        l2 = midl + 1, r2 = mid;
        break;
      } else if (ans[2]) {
        r = midl;
      } else {
        l = midl + 1, r = mid;
      }
    } else {
      if (ans[4] && ans[5]) {
        l1 = mid + 1, r1 = midr;
        l2 = midr + 1, r2 = r;
        break;
      } else if (ans[4]) {
        l = mid + 1, r = midr;
      } else {
        l = midr + 1;
      }
    }
  }

  while (l1 < r1) {
    memset(possibleBalls, false, sizeof possibleBalls);
    for (int x: range(l1, r1)) possibleBalls[x] = true;
    for (int x: range(l2, r2)) possibleBalls[x] = true;

    int mid1 = (l1 + r1) >> 1;
    int mid2 = (l2 + r2) >> 1;

    int midl1 = (l1 + mid1) >> 1;
    int midr1 = (mid1 + 1 + r1) >> 1;
    int midl2 = (l2 + mid2) >> 1;
    int midr2 = (mid2 + 1 + r2) >> 1;

    vector<vector<int>> queries;
    queries.push_back(range(l1, mid1));
    queries.push_back(range(l2, mid2));

    if (mid1 > l) {
      queries.push_back(range(l1, midl1));
      queries.push_back(range(mid1 + 1, midr1));
      queries.push_back(range(l2, midl2));
      queries.push_back(range(mid2 + 1, midr2));
    }

    extendQueriesWithNoBalls(queries);
    vector<bool> ans = ask(queries);

    if (ans[0]) {
      if (mid1 > l1) {
        if (ans[2]) r1 = midl1;
        else l1 = midl1 + 1, r1 = mid1;
      } else {
        l1 = r1 = l1;
      }
    } else {
      if (mid1 > l1) {
        if (ans[3]) l1 = mid1 + 1, r1 = midr1;
        else l1 = midr1 + 1;
      } else {
        l1 = r1 = r1;
      }
    }

    if (ans[1]) {
      if (mid2 > l2) {
        if (ans[4]) r2 = midl2;
        else l2 = midl2 + 1, r2 = mid2;
      } else {
        l2 = r2 = l2;
      }
    } else {
      if (mid2 > l2) {
        if (ans[5]) l2 = mid2 + 1, r2 = midr2;
        else l2 = midr2 + 1;
      } else {
        l2 = r2 = r2;
      }
    }
  }

  ans = {l1, l2};
}

int main() {
  scanf("%d %d", &n, &k);
  if (k == 1) binarySearch();
  else binarySearch2();

  answer(ans);
  return 0;
}
