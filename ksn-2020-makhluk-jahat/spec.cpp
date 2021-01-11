#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

// N is the maximum number of stages
// L is the maximum number of level-ups
// K is the skill number
// S is the skill pocket

constexpr int MAXN = 200000;
constexpr int MAXL = 100;
constexpr int MAXK = 20;
constexpr int MAXS = 4;

constexpr int SMLN = 1000;
constexpr int SMLK = 10;

class ProblemSpec : public BaseProblemSpec {
protected:
  
  int N, K;
  
  vector<int> S;
  vector<vector<char>> M;

  vector<int> O;
  vector<vector<int>> A;

  vector<pair<int, int>> R;

  int ANS;

  void InputFormat() {
    LINE(N, K);
    LINE(S % SIZE(MAXS));
    GRID(M) % SIZE(K, K);
    LINES(O, A);
  }

  void OutputFormat(){
    LINE(ANS);
  }

  void GradingConfig() {
    TimeLimit(2);
    MemoryLimit(256);
  }

  void Constraints() {
    CONS((1 <= N) && (N <= MAXN));
    CONS((4 <= K) && (K <= MAXK));
    CONS(eachGridBetween(M, '0', '1'));
    CONS(eachElementBetween(S, 1, K));
    CONS(eachElementBetween(O, 1, 2));
    CONS(eachGridBetween(A, 1, K));
    CONS(isValidRoom(O, A));
    CONS(isUnique(S));
    CONS(count(O.begin(), O.end(), 2) <= MAXL);
  }

  void Subtask1(){
    Points(0);
    CONS(N == 9 && K == 6);
    CONS(S == vector<int>({4, 6, 1, 2}));
    CONS(M == vector<vector<char>>({{'0', '0', '0', '0', '1', '0'},
                                    {'1', '0', '0', '0', '0', '0'},
                                    {'0', '0', '0', '0', '0', '1'},
                                    {'0', '0', '1', '0', '0', '0'},
                                    {'0', '1', '0', '0', '0', '0'},
                                    {'0', '0', '0', '1', '0', '0'}}));
    CONS(O == vector<int>({1, 1, 2, 1, 1, 2, 1, 1, 2}));
    CONS(A == vector<vector<int>>({{4}, {3}, {}, {6}, {2}, {}, {1}, {5}, {}}));
  }

  void Subtask2(){
    Points(0);
    CONS(N == 24 && K == 8);
    CONS(S == vector<int>({5, 1, 7, 2}));
    CONS(M == vector<vector<char>>({{'0', '0', '1', '0', '0', '0', '0', '0'},
                                    {'0', '0', '0', '1', '0', '1', '0', '1'},
                                    {'0', '1', '1', '0', '0', '0', '0', '0'},
                                    {'0', '1', '0', '0', '1', '1', '1', '0'},
                                    {'1', '1', '0', '0', '0', '1', '0', '0'},
                                    {'1', '0', '1', '1', '0', '1', '0', '1'},
                                    {'1', '0', '0', '0', '1', '0', '0', '0'},
                                    {'0', '1', '0', '0', '1', '1', '0', '0'}}));
    CONS(O == vector<int>({1, 1, 1, 1, 2, 1, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}));
    CONS(A == vector<vector<int>>({{7}, {2}, {7}, {4}, {}, {5}, {3}, {5}, {}, {2}, {6}, {}, {2}, {4}, {1}, {3}, {6}, {4}, {1}, {3}, {7}, {2}, {8}, {4}}));
  }

  void Subtask3(){
    Points(0);
    CONS(count(O.begin(), O.end(), 2) == 0);
  }

  void Subtask4(){
    Points(0);
    CONS(count(O.begin(), O.end(), 2) <= 3);
  }

  void Subtask5(){
    Points(0);
    CONS(K == 5);
  }

  void Subtask6(){
    Points(0);
    CONS(N <= SMLN);
    CONS(K <= SMLK);
  }

  void Subtask7(){
    Points(0);
    CONS(N <= SMLN);
  }

  void Subtask8(){
    Points(0);
    CONS(K <= SMLK);
  }

  void Subtask9(){
    Points(0);
  }

private:
  bool eachElementBetween(const vector<int>&V, int lo, int hi){
    for(int x : V) if(!(lo <= x && x <= hi)) return false;
    return true;
  }

  template<class T>
  bool eachGridBetween(const vector<vector<T>>&V, T lo, T hi){
    for(int i = 0;i < V.size();i++)
      for(int j = 0;j < V[i].size();j++)
        if(!(lo <= V[i][j] && V[i][j] <= hi)) return false;
    return true;
  }

  bool isUnique(vector<int>V){
    sort(V.begin(), V.end());
    for(int i = 1;i < V.size();i++)
      if(V[i-1] >= V[i]) return false;
    return true;
  }

  bool isValidRoom(const vector<int> &U, const vector<vector<int>> &V){
    for(int i = 0;i < U.size();i++){
      if(U[i] == 1 && V[i].size() != 1) return false;
      if(U[i] == 2 && V[i].size() != 0) return false;
    }
    return true;
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:

  void BeforeTestCase(){
    S.clear(); M.clear();
    R.clear();
    O.clear(); A.clear();
  }

  void AfterTestCase(){
    assert(R.size() == N);
    O.resize(N); A.resize(N);

    for(int i = 0;i < N;i++){
      O[i] = R[i].first;
      if(O[i] == 1) A[i].push_back(R[i].second);
    }

  }

  void SampleTestCase1() {
    Subtasks({4, 5, 6, 7, 8, 9});
    Input({
      "5 5",
      "1 2 3 5",
      "11100",
      "01010",
      "10110",
      "01001",
      "11010",
      "1 2",
      "1 5",
      "2",
      "1 3",
      "1 5",
    });
    Output({"3"});
  }

  void SampleTestCase2() {
    Subtasks({4, 5, 6, 7, 8, 9});
    Input({
      "8 5",
      "1 2 3 5",
      "11111",
      "11111",
      "11111",
      "11111",
      "11111",
      "1 2",
      "1 1",
      "2",
      "1 3",
      "1 5",
      "2",
      "2",
      "1 4",
    });
    Output({"5"});
  }

  void TestGroup1(){
    Subtasks({1, 4, 6, 7, 8, 9});
    CASE(
      N = 9; K = 6;
      S = {4, 6, 1, 2};
      M = {{'0', '0', '0', '0', '1', '0'},
         {'1', '0', '0', '0', '0', '0'},
         {'0', '0', '0', '0', '0', '1'},
         {'0', '0', '1', '0', '0', '0'},
         {'0', '1', '0', '0', '0', '0'},
         {'0', '0', '0', '1', '0', '0'}};
      R = {{1, 4},
         {1, 3},
         {2, 0},
         {1, 6},
         {1, 2},
         {2, 0},
         {1, 1},
         {1, 5},
         {2, 0}};
    );
  }

  void TestGroup2(){
    Subtasks({2, 4, 6, 7, 8, 9});
    CASE(
      N = 24; K = 8;
      S = {5, 1, 7, 2};
      M = {{'0', '0', '1', '0', '0', '0', '0', '0'},
         {'0', '0', '0', '1', '0', '1', '0', '1'},
         {'0', '1', '1', '0', '0', '0', '0', '0'},
         {'0', '1', '0', '0', '1', '1', '1', '0'},
         {'1', '1', '0', '0', '0', '1', '0', '0'},
         {'1', '0', '1', '1', '0', '1', '0', '1'},
         {'1', '0', '0', '0', '1', '0', '0', '0'},
         {'0', '1', '0', '0', '1', '1', '0', '0'}};
      R = {{1, 7},
         {1, 2},
         {1, 7},
         {1, 4},
         {2, 0},
         {1, 5},
         {1, 3},
         {1, 5},
         {2, 0},
         {1, 2},
         {1, 6},
         {2, 0},
         {1, 2},
         {1, 4},
         {1, 1},
         {1, 3},
         {1, 6},
         {1, 4},
         {1, 1},
         {1, 3},
         {1, 7},
         {1, 2},
         {1, 8},
         {1, 4}};
    );
  }

  // Subtasks
  // 3) L = 0
  // 4) L <= 3
  // 5) K = 5
  // 6) N <= 1'000, K <= 10
  // 7) N <= 1'000
  // 8) K <= 10
  // 9) N <= 200'000, K <= 20, L <= 100
  
  void TestGroup3(){
    Subtasks({3, 4, 5, 6, 7, 8, 9});
    // L = 0, K = 5, N <= 1'000
    CASE(N = 5; K = 5; randomS(); randomM(0); randomR(0));
    CASE(N = 5; K = 5; randomS(); randomM(100); randomR(0));
    CASE(N = 20; K = 5; randomS(); randomM(15); randomR(0));
    CASE(N = SMLN; K = 5; randomS(); randomM(20); randomR(0));
    CASE(N = rnd.nextInt(SMLN/2, SMLN); K = 5; randomS(); randomM(20); randomR(0));
  }

  void TestGroup4(){
    Subtasks({3, 4, 5, 8, 9});
    // L = 0, K = 5, N <= 200'000
    CASE(N = rnd.nextInt(SMLN, MAXN); K = 5; randomS(); randomM(20); randomR(0));
    CASE(N = rnd.nextInt((MAXN/4)*3, MAXN); K = 5; randomS(); randomM(30); randomR(0));
    CASE(N = MAXN; K = 5; randomS(); randomM(10); randomR(0));
  }

  void TestGroup5(){
    Subtasks({3, 4, 6, 7, 8, 9});
    // L = 0, K <= 10, N <= 1000
    CASE(N = 20; K = 9; randomS(); randomM(10); randomR(0));
    CASE(N = SMLN; K = 10; randomS(); randomM(30); randomR(0));
    CASE(N = rnd.nextInt(SMLN/2, SMLN); K = 9; randomS(); randomM(20); randomR(0));
  }

  void TestGroup6(){
    Subtasks({3, 4, 7, 9});
    // L = 0, K <= 20, N <= 1'000
    CASE(N = 20; K = MAXK; randomS(); randomM(20); randomR(0));
    CASE(N = SMLN; K = 14; randomS(); randomM(50); randomR(0));
    CASE(N = rnd.nextInt(SMLN/2, SMLN); K = MAXK; randomS(); randomM(15); randomR(0));
  }

  void TestGroup7(){
    Subtasks({3, 4, 8, 9});
    // L = 0, K <= 10, N <= 200'000
    CASE(N = SMLN+1; K = 4; randomS(); randomM(35); randomR(0));
    CASE(N = rnd.nextInt(MAXN/4, MAXN); K = 9; randomS(); randomM(10); randomR(0));
    CASE(N = rnd.nextInt(3*MAXN/4, MAXN); K = 9; randomS(); randomM(20); randomR(0));
    CASE(N = MAXN; K = 10; randomS(); randomM(25); randomR(0));
  }

  void TestGroup8(){
    Subtasks({3, 4, 9});
    // L = 0, K <= 20, N <= 200'000
    CASE(N = SMLN+1; K = 13; randomS(); randomM(15); randomR(0));
    CASE(N = 10000; K = 11; randomS(); randomM(60); randomR(0));
    CASE(N = rnd.nextInt(MAXN/4, MAXN); K = 15; randomS(); randomM(20); randomR(0));
    CASE(N = rnd.nextInt(3*MAXN/4, MAXN); K = MAXK; randomS(); randomM(30); randomR(0));
    CASE(N = MAXN; K = MAXK; randomS(); randomM(15); randomR(0));
  }

  void TestGroup9(){
    Subtasks({4, 5, 6, 7, 8, 9});
    // L <= 3, K = 5, N <= 1'000
    CASE(
      N = 5; K = 5;
      S = {1, 2, 3, 4};
      M = {{'0', '0', '0', '1', '0'},
         {'0', '0', '1', '0', '1'},
         {'1', '0', '0', '0', '0'},
         {'0', '1', '0', '0', '0'},
         {'0', '0', '0', '0', '0'}};
      R = {{2, 0},
         {1, 1},
         {1, 2},
         {1, 3},
         {1, 4}};
    );
    CASE(N = 10; K = 5; randomS(); uniqueMBeat(); semiRiggedRooms(3, 4));
    CASE(N = 10; K = 5; randomS(); randomM(10); randomR(2));
    CASE(N = SMLN; K = 5; randomS(); randomM(35); randomR(3));
    CASE(N = SMLN; K = 5; randomS(); randomM(20); semiRiggedRooms(3, 4));
    CASE(N = rnd.nextInt(SMLN/2, SMLN); K = 5; randomS(); randomM(20); randomR(3));
    CASE(N = SMLN; K = 5; randomS(); uniqueMBeat(); randomR(3));
    CASE(N = SMLN; K = 5; randomS(); uniqueMBeat(); semiRiggedRooms(3, 4));
  }

  void TestGroup10(){
    Subtasks({4, 5, 8, 9});
    // L <= 3, K = 5, N <= 200'000
    CASE(N = rnd.nextInt(SMLN, MAXN); K = 5; randomS(); randomM(20); randomR(1));
    CASE(N = rnd.nextInt((MAXN/4)*3, MAXN); K = 5; randomS(); randomM(30); randomR(3));
    CASE(N = MAXN; K = 5; randomS(); randomM(15); randomR(2));
    CASE(N = MAXN; K = 5; randomS(); uniqueMBeat(); randomR(3));
    CASE(N = MAXN; K = 5; randomS(); uniqueMBeat(); semiRiggedRooms(3, 4));
  }

  void TestGroup11(){
    Subtasks({4, 6, 7, 8, 9});
    // L <= 3, K <= 10, N <= 1'000
    
    CASE(
      N = 6; K = 6;
      S = {1, 2, 3, 4};
      M = {{'1', '0', '0', '0', '0', '0'},
         {'0', '1', '0', '0', '0', '0'},
         {'0', '0', '1', '0', '0', '0'},
         {'0', '0', '0', '1', '0', '0'},
         {'0', '0', '0', '0', '1', '0'},
         {'0', '0', '0', '0', '0', '1'}};
      R = {{2, 0},
         {2, 0},
         {1, 1},
         {1, 2},
         {1, 5},
         {1, 6}};
    );
    
    CASE(N = 10; K = 4; randomS(); randomM(35); randomR(2));
    CASE(N = SMLN; K = 10; randomS(); randomM(30); randomR(3));
    CASE(N = SMLN; K = 8; randomS(); randomM(10); semiRiggedRooms(3, 4));
    CASE(N = SMLN; K = 10; randomS(); randomM(25); semiRiggedRooms(3, 1));

    CASE(N = rnd.nextInt(SMLN/2, SMLN); K = 10; randomS(); randomM(70); randomR(3));
    CASE(N = SMLN; K = 10; randomS(); uniqueMBeat(); randomR(3));
    CASE(N = SMLN; K = 10; randomS(); uniqueMBeat(); semiRiggedRooms(3, 1));
    CASE(N = SMLN; K = 10; randomS(); uniqueMBeat(); semiRiggedRooms(3, 3));

  }

  void TestGroup12(){
    Subtasks({4, 7, 9});
    // L <= 3, K <= 20, N <= 1'000
    CASE(N = 20; K = MAXK; randomS(); randomM(20); randomR(2));
    CASE(N = 10; K = MAXK; randomS(); uniqueMBeat(); semiRiggedRooms(3, 4));
    CASE(N = SMLN; K = 14; randomS(); randomM(15); randomR(2));
    CASE(N = SMLN; K = MAXK; randomS(); randomM(15); semiRiggedRooms(3, 1));

    CASE(N = rnd.nextInt(SMLN/2, SMLN); K = MAXK; randomS(); randomM(10); randomR(3));
    CASE(N = SMLN; K = MAXK; randomS(); uniqueMBeat(); randomR(3));
    CASE(N = SMLN; K = MAXK; randomS(); uniqueMBeat(); semiRiggedRooms(3, 3));
  }

  void TestGroup13(){
    Subtasks({4, 8, 9});
    // L <= 3, K <= 10, N <= 200000
    CASE(N = SMLN+1; K = 6; randomS(); randomM(35); randomR(3));
    CASE(N = rnd.nextInt(MAXN/4, MAXN); K = 8; randomS(); randomM(20); randomR(3));
    CASE(N = rnd.nextInt(3*MAXN/4, MAXN); K = 9; randomS(); randomM(20); randomR(3));
    
    CASE(N = MAXN; K = 10; randomS(); randomM(35); randomR(3));
    CASE(N = MAXN; K = 10; randomS(); randomM(10); riggedRooms(3, 4));
    CASE(N = MAXN; K = 10; randomS(); uniqueMBeat(); randomR(3));
    CASE(N = MAXN; K = 10; randomS(); uniqueMBeat(); semiRiggedRooms(3, 2));
  }

  void TestGroup14(){
    Subtasks({4, 9});
    // L <= 3, K <= 20, N <= 200000
    CASE(N = SMLN+1; K = 13; randomS(); randomM(35); randomR(2));
    CASE(N = rnd.nextInt(MAXN/4, MAXN); K = 17; randomS(); randomM(10); randomR(1));
    CASE(N = rnd.nextInt(MAXN/4, MAXN); K = 16; randomS(); randomM(50); randomR(3));
    CASE(N = rnd.nextInt(3*MAXN/4, MAXN); K = MAXK; randomS(); randomM(35); randomR(2));
    
    CASE(N = MAXN; K = MAXK; randomS(); randomM(30); randomR(3));
    CASE(N = MAXN; K = MAXK; randomS(); randomM(15); riggedRooms(3, 4));
    CASE(N = MAXN; K = MAXK; randomS(); uniqueMBeat(); randomR(3));
    CASE(N = MAXN; K = MAXK; randomS(); uniqueMBeat(); semiRiggedRooms(3, 1));
  }


  void TestGroup15(){
    Subtasks({5, 6, 7, 8, 9});
    // L <= 100, K = 5, N <= 1000
    CASE(N = 10; K = 5; randomS(); randomM(15); randomR(4));
    CASE(N = SMLN; K = 5; randomS(); randomM(20); randomR(18));
    
    CASE(N = rnd.nextInt(SMLN/2, SMLN); K = 5; randomS(); randomM(10); randomR(70));
    CASE(N = rnd.nextInt(SMLN/2, SMLN); K = 5; randomS(); randomM(30); randomR(40));

    CASE(N = SMLN; K = 5; randomS(); uniqueMBeat(); randomR());
  }

  void TestGroup16(){
    Subtasks({5, 8, 9});
    // L <= 100, K = 5, N <= 200'000
    CASE(N = rnd.nextInt(SMLN, MAXN); K = 5; randomS(); randomM(30); randomR(76));
    CASE(N = rnd.nextInt((MAXN/4)*3, MAXN); K = 5; randomS(); randomM(30); randomR(52));
    CASE(N = MAXN; K = 5; randomS(); randomM(25); randomR());
    CASE(N = MAXN; K = 5; randomS(); uniqueMBeat(); randomR());
    CASE(N = MAXN; K = 5; randomS(); uniqueMBeat(); semiRiggedRooms(100, 4));
  }

  void TestGroup17(){
    Subtasks({6, 7, 8, 9});
    // L <= 100, K <= 10, N <= 1'000
    CASE(N = 80; K = 9; randomS(); randomM(15); randomR(9));
    CASE(N = 50; K = 8; randomS(); randomM(20); randomR(4));
    CASE(N = SMLN; K = 10; randomS(); randomM(50); randomR(93));
    CASE(N = SMLN; K = 10; randomS(); randomM(15); semiRiggedRooms(100, 3));

    CASE(N = rnd.nextInt(SMLN/2, SMLN); K = 10; randomS(); randomM(10); randomR());
    CASE(N = rnd.nextInt(SMLN/2, SMLN); K = 9; randomS(); randomM(20); randomR(70));
    CASE(N = SMLN; K = 10; randomS(); uniqueMBeat(); randomR());
    CASE(N = SMLN; K = 10; randomS(); uniqueMBeat(); semiRiggedRooms(100, 4));
  }

  void TestGroup18(){
    Subtasks({7, 9});
    // L <= 100, K <= 20, N <= 1'000
    CASE(N = 40; K = 16; randomS(); randomM(15); randomR(10));
    CASE(N = SMLN; K = MAXK; randomS(); randomM(20); randomR(61));
    CASE(N = SMLN; K = MAXK; randomS(); randomM(15); semiRiggedRooms(100, 2));
    
    CASE(N = rnd.nextInt(SMLN/2, SMLN); K = MAXK; randomS(); randomM(20); randomR(80));
    CASE(N = SMLN; K = MAXK; randomS(); uniqueMBeat(); randomR());
    CASE(N = SMLN; K = MAXK; randomS(); uniqueMBeat(); semiRiggedRooms(100, 1));
  }

  void TestGroup19(){
    Subtasks({8, 9});
    // L <= 100, K <= 10, N <= 200'000
    CASE(N = SMLN+1; K = 10; randomS(); randomM(24); randomR(30));
    CASE(N = rnd.nextInt(3*MAXN/4, MAXN); K = 9; randomS(); randomM(20); randomR());
    
    CASE(N = MAXN; K = 10; randomS(); randomM(15); randomR());
    CASE(N = MAXN; K = 10; randomS(); randomM(25); semiRiggedRooms(100, 1));

    CASE(N = MAXN; K = 10; randomS(); uniqueMBeat(); randomR());
    CASE(N = MAXN; K = 10; randomS(); uniqueMBeat(); semiRiggedRooms(100, 2));
  }

  void TestGroup20(){
    Subtasks({9});
    // L <= 100, K <= 20, N <= 200'000
    CASE(N = SMLN+1; K = 13; randomS(); randomM(35); randomR(40));
    CASE(N = rnd.nextInt(MAXN/4, MAXN); K = MAXK; randomS(); randomM(10); randomR());
    CASE(N = rnd.nextInt(3*MAXN/4, MAXN); K = 12; randomS(); randomM(30); randomR());

    CASE(N = MAXN; K = MAXK; randomS(); randomM(25); randomR());
    CASE(N = MAXN; K = MAXK; randomS(); randomM(15); semiRiggedRooms(100, 1));
    CASE(N = MAXN; K = MAXK; randomS(); uniqueMBeat(); randomR());
    CASE(N = MAXN; K = MAXK; randomS(); uniqueMBeat(); semiRiggedRooms(100, 2));
  }

private:

  // S Generators

  /** Generate MAXS random skill */
  void randomS(){
    S.resize(K);
    
    iota(S.begin(), S.end(), 1);
    rnd.shuffle(S.begin(), S.end());
    
    while(S.size() > MAXS) S.pop_back();
  }

  // M Generators
  
  /**
   * Generate random M
   * @param fight (fight%) chance of '1' appears
   */
  void randomM(int fight = 50){

    assert(0 <= fight && fight <= 100);

    M.resize(K, vector<char>(K, '0'));

    for(int i = 0;i < K;i++) for(int j = 0;j < K;j++)
      M[i][j] = (rnd.nextInt(100) < fight ? '1' : '0');
  }

  void uniqueMBeat(){
    vector<vector<int>> beat(K, vector<int>());

    for(int i = 0;i < K;i++)
      beat[rnd.nextInt(K)].push_back(i);

    M.resize(K, vector<char>(K, '0'));

    for(int i = 0;i < K;i++){
      for(int j = 0;j < beat[i].size();j++){
        M[i][beat[i][j]] = '1';
      }
    }
  }

  // Room generators
  
  /**
   * Generate random room
   * @param L number of library appears
   */
  void randomR(int L = MAXL){

    assert(L <= N);
    R.resize(N);

    for(int i = 0;i < L;i++) R[i] = {2, 0};

    for(int i = L;i < N;i++) R[i] = {1, rnd.nextInt(1, K)};

    rnd.shuffle(R.begin(), R.end());
  }

  void pickMonsters(vector<int> &V, int rigged){

    assert(rigged > 0);

    vector <int> hero(K);

    iota(hero.begin(), hero.end(), 1);
    rnd.shuffle(hero.begin(), hero.end());

    while(hero.size() > rigged) hero.pop_back();

    V.clear();
    for(int curHero : hero)
      for(int j = 0;j < K;j++)
        if(M[curHero-1][j] == '1') V.push_back(j+1);

    sort(V.begin(),V.end());
    V.erase(unique(V.begin(),V.end()),V.end());

    if(V.empty()) V.push_back(rnd.nextInt(K)+1);
  }

  inline int pick(const vector <int> &V){
    assert(!V.empty());
    return V[rnd.nextInt(V.size())];
  }

  // Monsters available is only from initial picked monsters
  void riggedRooms(int L = MAXL, int rigged = -1){
    assert(rigged != -1);
    randomR(L);
    vector <int> V;
    pickMonsters(V, rigged);
    for(int i = 0;i < N;i++) if(R[i].first == 1) R[i].second = pick(V);
  }

  // Monsters available in each segments only from initial picked
  void semiRiggedRooms(int L = MAXL, int rigged = -1){
    assert(rigged != -1);
    randomR(L);
    vector <int> V;
    pickMonsters(V, rigged);
    for(int i = 0;i < N;i++){
      if(R[i].first == 1) R[i].second = pick(V);
      else pickMonsters(V, rigged);
    }
  }
};