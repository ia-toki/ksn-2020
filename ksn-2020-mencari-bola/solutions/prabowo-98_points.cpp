// Solution idea for K = 2 by AMnu

#include <bits/stdc++.h>
using namespace std;

const int kMaxN = 1024;

int n, k;

template<class T>
vector<T> operator + (vector<T> u, vector<T> v) {
  for (T elem: v) u.push_back(elem);
  return u;
}

template<class T>
vector<T> join(vector<vector<T>> v) {
  vector<T> ret;
  for (const vector<T> &row: v) for (T elem: row) ret.push_back(elem);
  return ret;
}

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

vector<vector<int>> fiveGrouping = {
  {0, 1, 2},
  {0, 1, 3},
  {0, 1, 4},
  {0, 2, 3},
  {0, 2, 4},
  {0, 3, 4},
  {1, 2, 3},
  {1, 2, 4},
  {1, 3, 4},
  {2, 3, 4},
};

vector<vector<int>> eightGrouping = {
  {2, 3, 4, 5, 6, 7},
  {0, 3, 4, 5, 6, 7},
  {0, 1, 4, 5, 6, 7},
  {0, 1, 2, 3, 6, 7},
  {0, 1, 2, 3, 4, 7},
};

vector<vector<int>> sixteenGrouping = {
  {0, 1, 2, 3},
  {4, 5, 6, 7},
  {8, 9, 10, 11},
  {12, 13, 14, 15},
  {0, 4, 8, 12},
  {1, 5, 9, 13},
  {2, 6, 10, 14},
  {3, 7, 11, 15},
  {0, 5, 10, 15},
  {1, 6, 11, 12},
};

bool possibleBalls[kMaxN];
vector<int> noBalls() {
  vector<int> ret;
  for (int i = 0; i < n; ++i) {
    if (!possibleBalls[i]) ret.push_back(i);
  }
  return ret;
}

void updatePossibleBalls(const vector<int> &balls) {
  for (int i = 0; i < n; ++i) possibleBalls[i] = false;
  for (int ball: balls) possibleBalls[ball] = true;
}

void extendQueriesWithNoBalls(vector<vector<int>> &boxesSets) {
  vector<int> noBalls = ::noBalls();
  for (vector<int> &boxesSet: boxesSets) {
    for (int ball: noBalls) boxesSet.push_back(ball);
  }
}

vector<vector<int>> getGrouping(int ngroup, vector<vector<int>> grouping, vector<int> balls) {
  vector<vector<int>> groups;

  int d = balls.size() / ngroup, m = balls.size() % ngroup, cur = 0;
  for (int i = 0; i < ngroup; ++i) {
    vector<int> group;
    for (int j = 0; j < d; ++j) group.push_back(balls[cur++]);
    if (i < m) group.push_back(balls[cur++]);
    groups.push_back(group);
  }
  return groups;
}

vector<vector<int>> getBoxesSetsFromGrouping(vector<vector<int>> groups, vector<vector<int>> grouping) {
  vector<vector<int>> boxesSets;
  for (int i = 0; i < grouping.size(); ++i) {
    vector<int> boxesSet;
    for (int group: grouping[i]) {
      for (int g: groups[group]) {
        boxesSet.push_back(g);
      }
    }
    boxesSets.push_back(boxesSet);
  }

  return boxesSets;
}

vector<vector<int>> getGroupsWithBalls(vector<bool> ans, int ngroup, vector<vector<int>> grouping, vector<vector<int>> groups, bool one=false) {
  for (int i = 0; i < ngroup; ++i) {
    for (int j = i; j < ngroup; ++j) {
      if (one && i != j) continue;
      bool okay = true;
      for (int k = 0; k < ans.size(); ++k) {
        bool expect = binary_search(grouping[k].begin(), grouping[k].end(), i) ||
                      binary_search(grouping[k].begin(), grouping[k].end(), j);
        if (expect != ans[k]) {
          okay = false;
          break;
        }
      }

      if (okay) {
        if (i == j) {
          return {groups[i]};
        } else {
          return {groups[i], groups[j]};
        }
      }
    }
  }

  assert(0);
  return {};
}

vector<vector<int>> findGroups(int ngroup, vector<vector<int>> grouping, vector<int> balls) {
  vector<vector<int>> groups = getGrouping(ngroup, grouping, balls);
  vector<vector<int>> boxesSets = getBoxesSetsFromGrouping(groups, grouping);

  extendQueriesWithNoBalls(boxesSets);

  vector<bool> ans = ask(boxesSets);
  return getGroupsWithBalls(ans, ngroup, grouping, groups);
}

vector<vector<int>> findGroups(int ngroup, vector<vector<int>> grouping, vector<int> balls1, vector<int> balls2) {
  vector<vector<int>> groups1 = getGrouping(ngroup, grouping, balls1);
  vector<vector<int>> boxesSets1 = getBoxesSetsFromGrouping(groups1, grouping);

  vector<vector<int>> groups2 = getGrouping(ngroup, grouping, balls2);
  vector<vector<int>> boxesSets2 = getBoxesSetsFromGrouping(groups2, grouping);

  extendQueriesWithNoBalls(boxesSets1);
  extendQueriesWithNoBalls(boxesSets2);

  vector<bool> ans = ask(boxesSets1 + boxesSets2);

  return getGroupsWithBalls(vector<bool>(ans.begin(), ans.begin() + grouping.size()), ngroup, grouping, groups1, true) + 
         getGroupsWithBalls(vector<bool>(ans.begin() + grouping.size(), ans.end()), ngroup, grouping, groups2, true);
}

vector<vector<int>> binaryQueries(int lg, vector<int> balls) {
  vector<vector<int>> ret(lg);
  for (int i = 0; i < lg; ++i) {
    for (int j = 0; j < balls.size(); ++j) {
      if (j >> i & 1) ret[i].push_back(balls[j]);
    }
  }
  return ret;
}

int binaryAns(vector<bool> ans, vector<int> balls) {
  int idx = 0;
  for (int i = 0; i < ans.size(); ++i) {
    if (ans[i]) idx |= 1 << i;
  }
  return balls[idx];
}

vector<int> binary(int lg, vector<int> balls) {
  vector<vector<int>> boxesSets = binaryQueries(lg, balls);
  extendQueriesWithNoBalls(boxesSets);
  vector<bool> ans = ask(boxesSets);
  return { binaryAns(ans, balls) };
}

vector<int> binary(int lg, vector<int> balls1, vector<int> balls2) {
  vector<vector<int>> boxesSets = binaryQueries(lg, balls1) + binaryQueries(lg, balls2);
  extendQueriesWithNoBalls(boxesSets);
  vector<bool> ans = ask(boxesSets);
  return { binaryAns(vector<bool>(ans.begin(), ans.begin() + lg), balls1),
           binaryAns(vector<bool>(ans.begin() + lg, ans.begin() + lg*2), balls2) };
}

int main() {
  scanf("%d %d", &n, &k);

  vector<int> balls(n);
  iota(balls.begin(), balls.end(), 0);
  for (int i = 0; i < n; ++i) possibleBalls[i] = true;

  if (k == 1) {
    answer(binary(10, balls));
  } else if (k == 2) {
    vector<vector<int>> ballGroups = findGroups(5, fiveGrouping, balls);
    updatePossibleBalls(join(ballGroups));

    if (ballGroups.size() == 1) {
      ballGroups = findGroups(16, sixteenGrouping, ballGroups[0]);
      updatePossibleBalls(join(ballGroups));
      if (ballGroups.size() == 1) {
        ballGroups = findGroups(16, sixteenGrouping, ballGroups[0]);
        answer(join(ballGroups));
      } else {
        answer(binary(5, ballGroups[0], ballGroups[1]));
      }
    } else {
      ballGroups = findGroups(8, eightGrouping, ballGroups[0], ballGroups[1]);
      updatePossibleBalls(join(ballGroups));
      answer(binary(5, ballGroups[0], ballGroups[1]));
    }
  }

  assert(0);
  return 0;
}
