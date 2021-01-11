#include <bits/stdc++.h>
using namespace std;

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

vector<int> ans;
void binarySearch(int l, int r) {
  if (l == r) {
    ans.push_back(l);
    return;
  }

  int mid = (l + r) >> 1;
  vector<bool> ans = ask({range(l, mid)});
  if (ans[0]) binarySearch(l, mid);
  else binarySearch(mid+1, r);
}

void binarySearch2(int l, int r) {
  int mid = (l + r) >> 1;

  vector<bool> ans = ask({range(l, mid), range(mid+1, r)});
  if (ans[0] && ans[1]) {
    binarySearch(l, mid);
    binarySearch(mid+1, r);
    return;
  }

  if (ans[0]) binarySearch2(l, mid);
  else binarySearch2(mid+1, r);
}

int main() {
  scanf("%d %d", &n, &k);
  if (k == 1) binarySearch(0, n-1);
  else binarySearch2(0, n-1);

  answer(ans);
  return 0;
}
