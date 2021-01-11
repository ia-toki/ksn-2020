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

class Solver {
 protected:
  int n;

 public:
  void init(int _n) { n = _n; }
  virtual vector<int> getBoxes() = 0;
};

class OneBoxSolver: public Solver {
  vector<int> getBoxes() {
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
};

class TwoBoxesSolver: public Solver {
  vector<int> getBoxes() {
    int lg = __lg(n - 1) + 1;
    vector<vector<int>> bitOns(lg), bitOffs(lg);
    for (int i = 0; i < n; ++i) {
      for (int j = 0; j < lg; ++j) {
        if (i >> j & 1) bitOns[j].push_back(i);
        else bitOffs[j].push_back(i);
      }
    }

    vector<bool> onAns = ask(bitOns), offAns = ask(bitOffs);

    int onMask = 0, offMask = 0, unknownMask = 0;
    for (int i = 0; i < lg; ++i) {
      if (onAns[i] && offAns[i]) {
        unknownMask |= 1 << i;
      } else if (onAns[i]) {
        onMask |= 1 << i;
      } else if (offAns[i]) {
        offMask |= 1 << i;
      }
    }

    if (__builtin_popcount(unknownMask) == 1) return {onMask, onMask | unknownMask};

    int clz = 1 << __lg(unknownMask);

    vector<vector<int>> boxesSets;
    for (int mask = unknownMask; (mask & -mask) != mask; mask ^= mask & -mask) {
      vector<int> boxes;
      int ctz = mask & -mask;
      for (int i = 0; i < n; ++i) {
        if ((onMask & i) != onMask || (offMask & ~i) != offMask) {
          // Box guaranteed to not contain a ball
          boxes.push_back(i);
        } else if ((i & ctz) && !(i & clz)) {
          boxes.push_back(i);
          boxes.push_back(i ^ unknownMask);
        }
      }

      boxesSets.push_back(boxes);
    }

    vector<bool> res = ask(boxesSets);
    int ans = onMask;
    for (int i = 0, mask = unknownMask; i < res.size(); ++i) {
      int ctz = mask & -mask;

      if (res[i]) ans |= ctz;

      mask ^= ctz;
    }

    return {ans, ans ^ unknownMask};
  }
};

int main() {
  Solver *solver;
  int n, k;
  scanf("%d %d", &n, &k);

  if (k == 1) {
    solver = new OneBoxSolver();
  } else if (k == 2) {
    solver = new TwoBoxesSolver();
  }

  solver->init(n);
  answer(solver->getBoxes());
  return 0;
}
