#include <tcframe/runner.hpp>
using namespace tcframe;

#include <bits/stdc++.h>
using namespace std;

const int MAX=1E9;

class ProblemSpec : public BaseProblemSpec {
protected:

  int A,B,M;
  int ANS;

  void InputFormat() {
	  LINE(A,B,M);
  }

  void OutputFormat() {
	  LINE(ANS);
  }

  void StyleConfig() {
    CustomScorer();
  }

  void Constraints() {
	  CONS(between(A,1,MAX));
	  CONS(between(B,1,MAX));
	  CONS(between(M,1,MAX));
  }

  void Subtask1() {
	  CONS(A==3);
	  CONS(B==3);
	  CONS(M==100);
  }

  void Subtask2() {
	  CONS(A==20202020);
	  CONS(B==202020);
	  CONS(M==2020);
  }

  void Subtask3() {
	  CONS(M==2);
  }
  
  void Subtask4() {
	  CONS(M==3);
  }
  
  void Subtask5() {
	  CONS(M==4);
  }
  
  void Subtask6() {
	  CONS(M==5);
  }
  
  void Subtask7() {
	  CONS(M==6);
  }
  
  void Subtask8() {
	  CONS(B==2);
  }

private:
	bool between(int x,int l,int r) {
		return l<=x && x<=r;
	}
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:

  void SampleTestCase1() {
    Subtasks({6});
    Input({"2 3 5"});
    Output({"1"});
  }

  void TestGroup1() {
    Subtasks({1});
    CASE(A=3, B=3, M=100);
  }

  void TestGroup2() {
    Subtasks({2});
    CASE(A=20202020, B=202020, M=2020);
  }

  void TestGroup3() {	//B=2, M=2
    Subtasks({3,8});
    int b=2, m=2;
    for (int a=1;a<=m;a++) CASE(A=a, B=b, M=m);
    for (int a=0;a<m;a++) CASE(A=MAX-a, B=b, M=m);
    CASE(A=rnd.nextInt(m+2,MAX-m-2), B=b, M=m);
  }
  
  void TestGroup4() {	//M=2
    Subtasks({3});
    int m=2;
    vector<int> listB={MAX,3};
    for (auto b:listB) {
		for (int a=1;a<=m;a++) CASE(A=a, B=b, M=m);
		for (int a=0;a<m;a++) CASE(A=MAX-a, B=b, M=m);
		CASE(A=rnd.nextInt(m+2,MAX-m-2), B=b, M=m);
	}
  }
  
  void TestGroup5() {	//B=2, M=3
    Subtasks({4,8});
    int b=2, m=3;
    for (int a=2;a<=m-1;a++) CASE(A=a, B=b, M=m);
    for (int a=0;a<6;a++) CASE(A=MAX-a, B=b, M=m);
    CASE(A=rnd.nextInt(m+2,MAX-m-2), B=b, M=m);
  }
  
  void TestGroup6() {	//M=3
    Subtasks({4});
    int m=3;
    CASE(A=2, B=1, M=m);
    vector<int> listB={MAX,3};
    for (auto b:listB) {
		for (int a=2;a<=m-1;a++) CASE(A=a, B=b, M=m);
		for (int a=0;a<6;a++) CASE(A=MAX-a, B=b, M=m);
		CASE(A=rnd.nextInt(m+2,MAX-m-2), B=b, M=m);
	}
  }
  
  void TestGroup7() {	//B=2, M=4
    Subtasks({5,8});
    int b=2, m=4;
    for (int a=2;a<=m-1;a++) CASE(A=a, B=b, M=m);
    for (int a=0;a<m;a++) CASE(A=MAX-a, B=b, M=m);
    for (int i=0;i<2;i++) CASE(A=rnd.nextInt(m+2,MAX-m-2), B=b, M=m);
  }
  
  void TestGroup8() {	//M=4
    Subtasks({5});
    int m=4;
    CASE(A=2, B=1, M=m);
    vector<int> listB={MAX,3};
    for (auto b:listB) {
		for (int a=2;a<=m-1;a++) CASE(A=a, B=b, M=m);
		for (int a=0;a<m;a++) CASE(A=MAX-a, B=b, M=m);
		CASE(A=rnd.nextInt(m+2,MAX-m-2), B=b, M=m);
	}
  }
  
  void TestGroup9() {	//B=2, M=5
    Subtasks({6,8});
    int b=2, m=5;
    for (int a=2;a<=m-1;a++) CASE(A=a, B=b, M=m);
    for (int a=0;a<20;a++) CASE(A=MAX-a, B=b, M=m);
    for (int i=0;i<2;i++) CASE(A=rnd.nextInt(m+2,MAX-m-2), B=b, M=m);
  }
  
  void TestGroup10() {	//M=5
    Subtasks({6});
    int m=5;
    CASE(A=4, B=1, M=m);
    vector<int> listB={MAX,3};
    for (auto b:listB) {
		for (int a=2;a<=m-1;a++) CASE(A=a, B=b, M=m);
		CASE(A=rnd.nextInt(m+2,MAX-m-2), B=b, M=m);
	}
	for (int a=0;a<20;a++) CASE(A=MAX-a, B=MAX, M=m);
  }
  
  void TestGroup11() {	//B=2, M=6
    Subtasks({7,8});
    int b=2, m=6;
    for (int a=2;a<=m-1;a++) CASE(A=a, B=b, M=m);
    for (int a=0;a<m;a++) CASE(A=MAX-a, B=b, M=m);
    for (int i=0;i<3;i++) CASE(A=rnd.nextInt(m+2,MAX-m-2), B=b, M=m);
  }
  
  void TestGroup12() {	//M=6
	Subtasks({7});
	int m=6;
	CASE(A=2, B=1, M=m);
	vector<int> listB={MAX,3};
    for (auto b:listB) {
		for (int a=2;a<=m-1;a++) CASE(A=a, B=b, M=m);
		for (int a=0;a<m;a++) CASE(A=MAX-a, B=b, M=m);
		CASE(A=rnd.nextInt(m+2,MAX-m-2), B=b, M=m);
	}
  }
  
  void TestGroup13() {	//B=2
    Subtasks({8});
	int b=2;
	CASE(A=rnd.nextInt(2,MAX), B=b, M=rnd.nextInt(7,MAX));
	CASE(A=rnd.nextInt(2,MAX), B=b, M=rnd.nextInt(A+1,MAX));
	CASE(A=rnd.nextInt(MAX-10,MAX-1), B=b, M=rnd.nextInt(A+1,MAX));
	CASE(M=rnd.nextInt(7,MAX), B=b, A=M/2);
	CASE(M=999999937, B=b, A=M/2);
  }

private:
};
