#include <bits/stdc++.h>
using namespace std;

vector<bool> ask(const vector<vector<int>> boxesSets) {
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

vector<int> getBoxes(int n) {
  int lg = __lg(n - 1) + 1;
  vector<vector<int>> boxesSets(lg);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < lg; ++j) {
      if (i >> j & 1) boxesSets[j].push_back(i);
    }
  }

  vector<bool> res = ask(boxesSets);
  int ans = 0;
  for (int i = 0; i < lg; ++i) {
    if (res[i]) ans |= 1 << i;
  }
  return {ans};
}

int main() {
  int n, k;
  scanf("%d %d", &n, &k);
  answer(getBoxes(n));
  return 0;
}
