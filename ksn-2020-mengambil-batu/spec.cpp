#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

const int kMaxA = 10000;
const int kSmallA = 100;

class ProblemSpec : public BaseProblemSpec {
 protected:
  int K, N;
  vector<int> piles;

  void InputFormat() {
    LINE(K, N);
    LINE(piles % SIZE(K));
  }

  void StyleConfig() {
    InteractiveEvaluator();
  }

  void Constraints() {
    CONS(1 <= K && K <= 2);
    CONS(all_of(piles.begin(), piles.end(), [](int u) { return 1 <= u && u <= kMaxA; }));
    CONS(1 <= N && N <= kMaxA);
  }

  void Subtask1() {
    CONS(K == 1);
  }

  void Subtask2() {
    CONS(K == 2);
    CONS(all_of(piles.begin(), piles.end(), [](int u) { return 1 <= u && u <= kSmallA; }));
  }

  void Subtask3() {
    CONS(K == 2);
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
 protected:
  void SampleTestCase1() {
    Subtasks({1});
    Input({
      "1 2",
      "4",
    });
  }

  void SampleTestCase2() {
    Subtasks({2, 3});
    Input({
      "2 2",
      "2 1",
    });
  }

  void TestGroup1() {
    Subtasks({1});

    casesWithPiles({
      {1, {1}},
      {1, {3}},
      {1, {kMaxA - 1}},
      {2, {kMaxA - 2}},
      {2, {kMaxA - 1}},
      {kMaxA, {kMaxA}},
      {kMaxA - 1, {kMaxA}},
      {kMaxA/2, {kMaxA}},
      {kMaxA/2 + 1, {kMaxA}},
      {randomCase(1, kMaxA)},
      {randomCase(1, kMaxA)},
      {randomCase(1, kMaxA)},
      {randomCase(1, kMaxA)},
      {randomCase(1, kMaxA)},
    });
  }

  void TestGroup2() {
    Subtasks({2, 3});

    casesWithPiles({
      {1, {1, 2}},
      {2, {2, 1}},
      {2, {1, 3}},
      {2, {2, 3}},
      {3, {3, 2}},
      {3, {1, 3}},
      {3, {1, 2}},
      {3, {kSmallA, kSmallA - 1}},
      {1, {1, kSmallA}},
      {1, {kSmallA - 1, kSmallA}},
      {1, {kSmallA / 2 + 1, kSmallA}},
      {kSmallA, {kSmallA - 1, kSmallA}},
      {kSmallA - 1, {kSmallA - 1, kSmallA}},
      {randomCase(2, kSmallA)},
      {randomCase(2, kSmallA)},
      {randomCase(2, kSmallA)},
      {randomCase(2, kSmallA)},
      {randomCase(2, kSmallA)},
      {randomCase(2, kSmallA)},
      {randomCase(2, kSmallA)},
      {randomCase(2, kSmallA)},
    });
  }

  void TestGroup3() {
    Subtasks({3});

    casesWithPiles({
      {1, {1, kMaxA}},
      {1, {kMaxA - 1, kMaxA}},
      {1, {kMaxA / 2 + 1, kMaxA}},
      {2, {kMaxA - 1, kMaxA}},
      {3, {kMaxA, kMaxA - 2}},
      {15, {kMaxA - 4, kMaxA - 13}},
      {15, {kMaxA - 1, kMaxA - 2}},
      {9, {1, kMaxA}},
      {10, {11, kMaxA}},
      {randomCase(2, kMaxA)},
      {randomCase(2, kMaxA)},
      {randomCase(2, kMaxA)},
      {randomCase(2, kMaxA)},
      {randomCase(2, kMaxA)},
      {randomCase(2, kMaxA)},
      {randomCase(2, kMaxA)},
      {randomCase(2, kMaxA)},
      {randomCase(2, kMaxA)},
      {randomCase(2, kMaxA)},
      {randomCase(2, kMaxA)},
      {randomCase(2, kMaxA)},
      {randomCase(2, kMaxA)},
      {randomCase(2, kMaxA)},
      {randomCase(2, kMaxA)},
      {randomCase(2, kMaxA)},
      {randomCase(2, kMaxA)},
      {randomCase(2, kMaxA)},
      {randomCase(2, kMaxA)},
      {randomCase(2, kMaxA)},
    });
  }

  bool winningCondition(int N, const vector<int> &piles) {
    int res = 0;
    for (int pile: piles) res ^= pile % (N + 1);
    return res > 0;
  }

  void casesWithPiles(vector<pair<int, vector<int>>> cases) {
    for (int i = 0; i < cases.size(); ++i) {
      if (!winningCondition(cases[i].first, cases[i].second)) {
        // cerr << "WARN: Skipped a case with no winning condition" << endl;
        continue;
      }
      CASE(K = cases[i].second.size(); N = cases[i].first, piles = cases[i].second);
    }
  }

  pair<int, vector<int>> randomCase(int K, int maxA) {
    int n;
    vector<int> ret;

    do {
      ret.clear();
      n = rnd.nextInt(1, maxA);
      for (int i = 0; i < K; ++i) ret.push_back(rnd.nextInt(1, maxA));
    } while (!winningCondition(n, ret));

    return {n, ret};
  }
}; 
