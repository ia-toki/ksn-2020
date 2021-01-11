#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

const int kMaxN = 1024;

class ProblemSpec : public BaseProblemSpec {
 protected:
  int N, K;
  vector<int> balls;

  void InputFormat() {
    LINE(N, K);
    LINE(balls % SIZE(K));
  }

  void StyleConfig() {
    InteractiveEvaluator();
  }

  void Constraints() {
    CONS(1 <= K && K <= 2);
    CONS(validBalls(balls, N));
  }

  void Subtask1() {
    CONS(N == 1024);
    CONS(K == 1);
  }

  void Subtask2() {
    CONS(N == 1024);
    CONS(K == 2);
  }

  bool validBalls(vector<int> balls, int N) {
    for (int ball: balls) {
      if (ball < 1 || ball > N) return false;
    }
    sort(balls.begin(), balls.end());
    return unique(balls.begin(), balls.end()) == balls.end();
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
 protected:
  void SampleTestCase1() {
    Input({
      "4 1",
      "3",
    });
  }

  void SampleTestCase2() {
    Input({
      "4 2",
      "3 4",
    });
  }

  void TestGroup1() {
    Subtasks({1});

    casesWithBalls(kMaxN, 1, {
      {1},
      {2},
      {3},
      {rnd.nextInt(4, kMaxN/2 - 2)},
      {rnd.nextInt(4, kMaxN/2 - 2)},
      {rnd.nextInt(4, kMaxN/2 - 2)},
      {kMaxN/2 - 1},
      {kMaxN/2},
      {kMaxN/2 + 1},
      {rnd.nextInt(kMaxN/2 + 2, kMaxN - 4)},
      {rnd.nextInt(kMaxN/2 + 2, kMaxN - 4)},
      {rnd.nextInt(kMaxN/2 + 2, kMaxN - 4)},
      {kMaxN - 3},
      {kMaxN - 2},
      {kMaxN - 1},
    });
  }

  void TestGroup2() {
    Subtasks({2});

    casesWithBalls(kMaxN, 2, {
      {1, 2},
      {kMaxN - 1, kMaxN},
      {kMaxN/2, kMaxN/2 + 1},
      {kMaxN/2, kMaxN/2 - 1},
      {kMaxN/2 + 1, kMaxN/2 - 1},
      {1, kMaxN},
      {1, kMaxN/2 + 1},
      {kMaxN/2, kMaxN},
      {588, 196},
      {420, 69},
      {177, 013},
      {328, 329},
      {700, 702},
      {899, 902},
      {600, 596},
      {666, 911},
      {341, 682}, // alternating bits
      {160, 780},
      randomTwoBalls(),
      randomTwoBalls(),
      randomTwoBalls(),
      randomTwoBalls(),
      randomTwoBalls(),
      randomTwoBalls(),
      randomTwoBalls(),
      randomTwoBalls(),
      randomTwoBalls(),
      randomTwoBalls(),
      randomTwoBalls(),
      randomTwoBalls(),
      randomTwoBalls(),
      randomTwoBalls(),
      randomTwoBalls(),
      randomTwoBalls(1, kMaxN/2),
      randomTwoBalls(kMaxN/2 + 1, kMaxN),
      {rnd.nextInt(1, kMaxN/2), rnd.nextInt(kMaxN/2 + 1, kMaxN)},
      {rnd.nextInt(1, kMaxN/2), rnd.nextInt(kMaxN/2 + 1, kMaxN)},
      {rnd.nextInt(1, kMaxN/2), rnd.nextInt(kMaxN/2 + 1, kMaxN)},
    });
  }

  void casesWithBalls(int n, int k, vector<vector<int>> ballsCases) {
    for (const vector<int> &ballsCase: ballsCases) {
      CASE(N = n; K = k; balls = ballsCase);
    }
  }

  vector<int> randomTwoBalls(int l=1, int r=kMaxN) {
    vector<int> balls(2);
    do {
      balls[0] = rnd.nextInt(l, r);
      balls[1] = rnd.nextInt(l, r);
    } while (balls[0] == balls[1]);
    return balls;
  }
}; 
