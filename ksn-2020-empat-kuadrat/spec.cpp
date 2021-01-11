#include <tcframe/runner.hpp>
using namespace tcframe;

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll MAXN = 1E18;

class ProblemSpec : public BaseProblemSpec {
protected:
  ll N, a, b, c, d;

  void InputFormat() {
    LINE(N);

  }

  void OutputFormat() {
    LINE(a, b, c, d);
  }

  void StyleConfig() {
    CustomScorer();
  }

  void GradingConfig() {
  }

  void Constraints() {
    CONS(1 <= N && N <= MAXN);
  }

  void Subtask1() {
    Points(10);
    CONS(N == 1);
  }

  void Subtask2() {
    Points(10);
    CONS(N == MAXN);
  }

  void Subtask3() {
    Points(10);
    CONS(N == 2020);
  }

  void Subtask4() {
    Points(10);
    CONS(N == 100000001);
  }

  void Subtask5() {
    Points(10);
    CONS(N == 1000000000);
  }

  void Subtask6() {
    Points(10);
    CONS(N == MAXN-10);
  }

  void Subtask7() {
    Points(10);
    CONS(N == 2201754854);
  }

  void Subtask8() {
    Points(10);
    CONS(N == 11235813213455);
  }

  void Subtask9() {
    Points(10);
    CONS(N == 3141592653589793);
  }

  void Subtask10() {
    Points(10);
    CONS(N == 987654321123456789);
  }

};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:

  void SampleTestCase1() {
    Subtasks({});
    Input({"33"});
    Output({"4 3 2 2"});
  }

  void BeforeTestCase() {
  }

  void TestGroup1() {
    Subtasks({1});

    CASE(N = 1);
  }

  void TestGroup2() {
    Subtasks({2});

    CASE(N = MAXN);
  }

  void TestGroup3() {
    Subtasks({3});

    CASE(N = 2020);

  }

  void TestGroup4() {
    Subtasks({4});

    CASE(N = 100000001);
  }

  void TestGroup5() {
    Subtasks({5});

    CASE(N = 1000000000);
  }

  void TestGroup6() {
    Subtasks({6});

    CASE(N = MAXN-10);
  }

  void TestGroup7() {
    Subtasks({7});

    CASE(N = 2201754854);
  }

  void TestGroup8() {
    Subtasks({8});
    CASE(N = 11235813213455);

  }

  void TestGroup9() {
    Subtasks({9});

    CASE(N = 3141592653589793);
  }

  void TestGroup10() {
    Subtasks({10});

    CASE(N = 987654321123456789);

  }
};
