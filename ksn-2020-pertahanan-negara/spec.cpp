#include <tcframe/runner.hpp>
using namespace tcframe;

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000000000;
const int MAXK = 100000;
const double EPS = 1e-11;

class ProblemSpec : public BaseProblemSpec {
protected:
  int N, M, K;
  vector<int> A;
  vector<vector<int> > ans;

  void InputFormat() {
    LINE(N, M, K);
    LINE(A % SIZE(K));
  }

  void OutputFormat() {
    GRID(ans) % SIZE(K, 4);
  }

  void StyleConfig() {
    CustomScorer();
  }

  void GradingConfig() {
  }

  void Constraints() {
    CONS(1 <= N && N <= MAXN);
    CONS(1 <= M && M <= MAXN);
    CONS(1 <= K && K <= MAXK);
    CONS(allBetween(A, 1, MAXN));
    CONS(sumEqual(A, 1ll * N * M));
  }

  void Subtask1() {
    Points(10);
    CONS(N == 5);
    CONS(M == 5);
    CONS(K == 5);
  }

  void Subtask2() {
    Points(10);
    CONS(N == 6);
    CONS(M == 7);
    CONS(K == 8);
  }

  void Subtask3() {
    Points(10);
    CONS(N == 1);
    CONS(M == MAXN);
    CONS(K == MAXK);
  }

  void Subtask4() {
    Points(10);
    CONS((N % 2) == 1);
    CONS(M == ((N + 1) / 2));
    CONS(K == N);
    CONS(isIntegerSequence(A));
  }

  void Subtask5() {
    Points(10);
    CONS(N == 9973 * 293);
    CONS(M == 99991 * 311);
    CONS(K == 293 * 311);
    CONS(allSameValue(A, 9973 * 99991));
  }

  void Subtask6() {
    Points(10);
    CONS(N == 2);
    CONS(K == 20);
    CONS(isEqualOddEven(A));
  }

  void Subtask7() {
    Points(10);
    CONS(N == 2);
    CONS(M <= 10000);
    CONS(K <= 100);
  }

  void Subtask8() {
    Points(10);
    CONS(N == 4681);
    CONS(M == 229383);
    CONS(K == 30);
    CONS(isPowerOf2(A));
  }

  void Subtask9() {
    Points(10);
    CONS(N == 46368);
    CONS(M == 28657);
    CONS(K == 23);
    CONS(isFibbonaciSquared(A));
  }

  void Subtask10() {
    Points(10);
    CONS(N == 2000);
    CONS(M == 2000);
    CONS(allBetween(A, 1, 100));
  }

private:
  bool between(int x,int l,int r) {
		return (l<=x && x<=r);
	}

	bool allBetween(const vector<int> &v,int l,int r) {
		for (auto data:v) if (!between(data,l,r)) return false; return true;
	}

  bool sumEqual(const vector<int>&v, long long x) {
    for (auto data: v) x -= data; return x == 0;
  }

  bool isIntegerSequence(const vector<int>&v) {
    for (int i = 0; i < v.size(); i++) {
      if (i + 1 != v[i]) return false;
    }
    return true;
  }

  bool isPowerOf2(const vector<int>&v) {
    for (int i = 0; i < v.size(); i++) {
      if (v[i] != (1 << i)) return false;
    }
    return true;
  }

  bool allSameValue(const vector<int>&v, int value) {
    for (auto data: v) if (data != value) return false;
    return true;
   }

  bool isEqualOddEven(const vector<int>&v) {
    vector<int> counter = {0, 0};
    for (auto data: v) counter[data%2]++;
    return counter[0] == counter[1];
  }

  bool isFibbonaciSquared(const vector<int> &v) {
    if (v[0] != 1 || v[1] != 1) return false;
    for (int i = 2; i < v.size(); i++) {
      if (fabs(sqrt(v[i]) - sqrt(v[i - 1]) - sqrt(v[i - 2])) > EPS) return false;
    }
    return true;
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:

  void SampleTestCase1() {
    Subtasks({});
    Input({"4 5 3", "8 9 3"});
    Output({"0 4 0 2", "0 3 2 5", "3 4 2 5"});
  }

  void SampleTestCase2() {
    Subtasks({});
    Input({"3 5 4", "5 4 3 3"});
    Output({"0 1 0 5", "1 2 0 4", "2 3 0 3", "-1 -1 -1 -1"});
  }

  void BeforeTestCase() {
    A.clear();
  }

  void TestGroup1() {
    Subtasks({1});

    CASE(N = 5, M = 5, K = 5, A = {4, 4, 4, 4, 9});
  }

  void TestGroup2() {
    Subtasks({2});

    CASE(N = 6, M = 7, K = 8, A = {2, 3, 4, 5, 6, 6, 7, 9});
  }

  void TestGroup3() {
    Subtasks({3});

    CASE(N = 1, M = MAXN, K = MAXK, generateRandomArray(K, MAXN));

  }

  void TestGroup4() {
    Subtasks({4});

    CASE(N = 99999, M = 50000, K = 99999, generateTestCase4(K));
  }

  void TestGroup5() {
    Subtasks({5});

    CASE(N = 9973 * 293, M = 99991 * 311, K = 293 * 311, generateTestCase5(K, 9973 * 99991));
  }

  void TestGroup6() {
    Subtasks({6});

    CASE(N = 2, M = MAXN, K = 20, generateTestCase6(K, M));
  }

  void TestGroup7() {
    Subtasks({7});

    CASE(N = 2, M = 10000, K = 100, generateRandomArray(K, N * M));
  }

  void TestGroup8() {
    Subtasks({8});
    CASE(N = 4681, M = 229383, K = 30, generatePowerOf2Array(K));

  }

  void TestGroup9() {
    Subtasks({9});

    CASE(N = 46368, M = 28657, K = 23, generateFibbonaciSquaredArray(K));
  }

  void TestGroup10() {
    Subtasks({10});

    CASE(N = 2000, M = 2000, generateTestCase10(N * M));

  }

private:
  vector<int> generateRandomArraySumToK(int k, int maxValue) {
    vector<int> v;

    vector<int> diff;
    for (int i = 0; i < k - 1; i++) {
      diff.push_back(rnd.nextInt(1, maxValue));
    }

    sort(diff.begin(), diff.end());
    v.push_back(diff[0]);

    for (int i = 1; i < diff.size(); i++) {
      diff[i] = max(diff[i], diff[i - 1] + 1);
      v.push_back(diff[i] - diff[i - 1]);
    }

    if (maxValue <= diff.back()) return generateRandomArraySumToK(k, maxValue);

    v.push_back(maxValue - diff.back());
    return v;
  }

  void generateRandomArray(int k, int maxValue) {
    A = generateRandomArraySumToK(k, maxValue);
  }

  void generateOddEven(int o, int e, int maxVal) {
    vector<int> v = generateRandomArraySumToK(o + e, maxVal);

    vector<int> odd, even;
    for (auto data: v) {
      if (data % 2 == 1) odd.push_back(data);
      else even.push_back(data);
    }

    while(odd.size() > o) {
        even.push_back(odd.back() + 1);
        odd.pop_back();
        even.push_back(odd.back() - 1);
        odd.pop_back();
    }

    while(even.size() > e) {
      odd.push_back(even.back() + 1);
      even.pop_back();
      odd.push_back(even.back() - 1);
      even.pop_back();
    }

    A.insert(A.end(), odd.begin(), odd.end());
    A.insert(A.end(), even.begin(), even.end());
  }

  // generate increment
  void generateTestCase4(int k) {
    for (int i = 0; i < k; i++) A.push_back(i + 1);
  }

  void generateTestCase5(int k, int val) {
    for (int i = 0; i < k; i++) A.push_back(val);
  }

  void generateTestCase6(int k, int maxVal) {
    int sum = 0;
    for (int i = 0; i < k/4; i++) {
      A.push_back(2 * rnd.nextInt(1, 2 * maxVal / k));
      sum += A.back() / 2;
    }

    if (sum % 2 == 1) {
      A[0] += 2;
      sum++;
    }

    generateOddEven(4, 3, maxVal - sum);
    generateOddEven(6, 2, maxVal - sum);

    rnd.shuffle(A.begin(), A.end());
  }

  void generatePowerOf2Array(int k) {
    for (int i = 0; i < k; i++) {
      A.push_back(1 << i);
    }
  }

  void generateFibbonaciSquaredArray(int k) {
    A.push_back(1); A.push_back(1);
    for (int i = 2; i < k; i++) {
      A.push_back(pow(sqrt(A[i - 1]) + sqrt(A[i - 2]), 2));
    }
  }

  void generateTestCase10(int k) {
    while(k) {
      int val = min(rnd.nextInt(1, 100), k);
      A.push_back(val);
      k -= val;
    }

    K = A.size();
  }

};
