/*
Subtask & TestGroup

Subtask 1 (Open 1)
1. Open 1 {1,3,4,5,6,7,8}

Subtask 2 (Open 2)
2. Open 2 {2,4,8}

Subtask 3 (N<=1000, C=0)
3. N<=1000, XY<=1000, R=0, C=0 {3,4,5,6,7,8}
4. N<=1000, R=0, C=0 {3,4,6,7,8}
5. N<=1000, C=0 {3,4,7,8}

Subtask 4 (N<=1000)
6. N<=1000 {4,8}

Subtask 5 (XY<=1000, R=0, C=0)
7. XY<=1000, R=0, C=0 {5,6,7,8}

Subtask 6 (R=0, C=0)
8. R=0, C=0 {6,7,8}

Subtask 7 (C=0)
9. C=0 {7,8}

Subtask 8 ()
10. {8}
*/
#include <tcframe/runner.hpp>
using namespace tcframe;

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int INF=1E9;

const int MIN_N = 1;
const int MAX_N = 1E5;

const int MIN_X = -1E9;
const int MAX_X = 1E9;

const int MIN_Y = -1E9;
const int MAX_Y = 1E9;

const int MIN_R = 0;
const int MAX_R = 1E9;

const int MIN_C = 0;
const int MAX_C = 1E9;

typedef pair<int,int> pii;

vector<int> tempV;

vector<vector<pii> > rangeV, rangeH;
vector<pair<pii,int> > idxVH;
vector<pii> tempCoor;
vector<pair<pii,pii> > tempReordering;

vector<pair<pair<int,int>,int> > sweepV,sweepH;  //koordinat, masuk(0)/keluar(1), indeks pilar
vector<pii> groupRangeV,groupRangeH;
vector<int> verticalGroup, horizontalGroup;
map<pii,vector<int> > cellGroup;

class ProblemSpec : public BaseProblemSpec {
protected:

  int N, Sx, Sy, Fx, Fy;
  vector<int> X,Y,R,C;
  
  ll ANS;

  void InputFormat() {
    LINE(N,Sx,Sy,Fx,Fy);
    LINES(X,Y,R,C)%SIZE(N);
  }

  void OutputFormat() {
    LINE(ANS);
  }
  
  void GradingConfig() {
    TimeLimit(1);
    MemoryLimit(256);
  }

  void StyleConfig() {
    CustomScorer();
  }

  void Constraints() {
    CONS(between(N,MIN_N,MAX_N));
    CONS(between(Sx,MIN_X,MAX_X));
    CONS(between(Sy,MIN_Y,MAX_Y));
    CONS(between(Fx,MIN_X,MAX_X));
    CONS(between(Fy,MIN_Y,MAX_Y));
    
    CONS(allBetween(X,MIN_X,MAX_X));
    CONS(allBetween(Y,MIN_Y,MAX_Y));
    CONS(allBetween(R,MIN_R,MAX_R));
    CONS(allBetween(C,MIN_C,MAX_C));
  }

  void Subtask1() {
    CONS(N==5);
    CONS(Sx==1);
    CONS(Sy==1);
    CONS(Fx==4);
    CONS(Fy==4);
    CONS(X==vector<int>({2,2,3,3,4}));
    CONS(Y==vector<int>({1,2,2,3,3}));
    CONS(R==vector<int>({0,0,0,0,0}));
    CONS(C==vector<int>({0,0,0,0,0}));
  }

  void Subtask2() {
    CONS(N==9);
    CONS(Sx==0);
    CONS(Sy==15);
    CONS(Fx==10);
    CONS(Fy==1);
    CONS(X==vector<int>({2,5,8,2,5,8,2,5,8}));
    CONS(Y==vector<int>({4,3,2,9,8,7,14,13,12}));
    CONS(R==vector<int>({1,1,1,1,1,1,1,1,1}));
    CONS(C==vector<int>({7,13,9,2,3,3,13,7,11}));
  }

  void Subtask3() {
    CONS(N<=1000);
    CONS(allBetween(C,0,0));
  }
  
  void Subtask4() {
    CONS(N<=1000);
  }

  void Subtask5() {
    CONS(between(Sx,-1000,1000));
    CONS(between(Sy,-1000,1000));
    CONS(between(Fx,-1000,1000));
    CONS(between(Fy,-1000,1000));
    
    CONS(allBetween(X,-1000,1000));
    CONS(allBetween(Y,-1000,1000));
    CONS(allBetween(R,0,0));
    CONS(allBetween(C,0,0));
  }

  void Subtask6() {
    CONS(allBetween(R,0,0));
    CONS(allBetween(C,0,0));
  }
  
  void Subtask7() {
    CONS(allBetween(C,0,0));
  }

  void Subtask8() {
  }

private:
  bool between(int x,int l,int r) {
    return (l<=x && x<=r);
  }
  bool allBetween(vector<int> &v,int l,int r) {
    for (auto data:v) if (!between(data,l,r)) return false; return true;
  }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:

  void SampleTestCase1() {
    Subtasks({4,8});
    Input({
    "3 0 0 2 7",
    "5 1 3 100",
    "10 2 0 3",
    "11 6 1 2"
    });
    Output({"5"});
  }
  
  void SampleTestCase2() {
    Subtasks({4,8});
    Input({
    "2 1 1 10 5",
    "3 1 1 4",
    "4 3 2 1"
    });
    Output({"0"});
  }
  
  void SampleTestCase3() {
    Subtasks({3,4,5,6,7,8});
    Input({
    "1 1 1 2 2",
    "3 3 0 0"
    });
    Output({"-1"});
  }

  void BeforeTestCase() {
    X.clear(); Y.clear(); R.clear(); C.clear();
  }

  void TestGroup1() {
    Subtasks({1,3,4,5,6,7,8});
    CASE(N=5, Sx=1, Sy=1, Fx=4, Fy=4, 
      X={2,2,3,3,4}, Y={1,2,2,3,3},
      R={0,0,0,0,0}, C={0,0,0,0,0}
    );
  }

  void TestGroup2() {
    Subtasks({2,4,8});
    CASE(N=9, Sx=0, Sy=15, Fx=10, Fy=1,
      X={2,5,8,2,5,8,2,5,8}, Y={4,3,2,9,8,7,14,13,12},
      R={1,1,1,1,1,1,1,1,1}, C={7,13,9,2,3,3,13,7,11}
    );
  }

  void TestGroup3() {	//N<=1000, XY<=1000, R=0, C=0
    Subtasks({3,4,5,6,7,8});
    
    CASE(N=1, Sx=Fx=rnd.nextInt(1,1000), Sy=Fy=rnd.nextInt(1,1000),
      X={0}, Y={0}, R={0}, C={0}
    );
    
    CASE(N=1, Sx=Fx=rnd.nextInt(1,1000), Sy=rnd.nextInt(1,1000), Fy=rnd.nextInt(1,1000),
      X={0}, Y={0}, R={0}, C={0}
    );
    
    CASE(N=1, Sx=rnd.nextInt(1,1000), Fx=rnd.nextInt(1,1000), Sy=Fy=rnd.nextInt(1,1000), 
      X={0}, Y={0}, R={0}, C={0}
    );
    
    vector<int> listN={1000};
    vector<pii> tipeSF={{-2,2}};
    for (auto n:listN) for (auto sf:tipeSF) {
		if (sf==pii({-2,2})) {
			sf.first=rnd.nextInt(0,1); sf.second=1-sf.first;
			if (sf.first==0) sf.first--;
			if (sf.second==0) sf.second--;
		}
		//Group sqrt*sqrt
		CASE(N=n, randomVector(C,N,0,0),
		  group_generateGrouping(rangeV,rnd.nextInt(sqrt(N),2*sqrt(N)),2,0,-1000,1000),
		  group_generateGrouping(rangeH,rnd.nextInt(sqrt(N),2*sqrt(N)),2,0,-1000,1000),
		  
		  group_fillCells(N/2,0),
		  generateStart(0,sf.first,-1000,1000),
		  
		  group_fillCells(N,1),
		  generateFinish(N/2,sf.second,sf.second,-1000,1000),
		  
		  reordering()
		);
		
		CASE(N=n, randomVector(C,N,0,0),
		  group_generateGrouping(rangeV,rnd.nextInt(sqrt(N),2*sqrt(N)),2,0,-1000,1000),
		  group_generateGrouping(rangeH,rnd.nextInt(sqrt(N),2*sqrt(N)),2,0,-1000,1000),
		  
		  group_fillCells(rnd.nextInt(N/10*8,N/10*9),0),
		  generateStart(0,sf.first,-1000,1000),
		  generateFinish(0,sf.second,sf.second,-1000,1000),
		  
		  group_fillCells(N,1),
		  
		  reordering()
		);
		
		//Group small*big
		CASE(N=n, randomVector(C,N,0,0),
		  group_generateGrouping(rangeV,rnd.nextInt(2,10),2,0,-1000,1000),
		  group_generateGrouping(rangeH,rnd.nextInt(N/2,N),2,0,-1000,1000),
		  
		  group_fillCells(N/2,0),
		  generateStart(0,sf.first,-1000,1000),
		  
		  group_fillCells(N,1),
		  generateFinish(N/2,sf.second,sf.second,-1000,1000),
		  
		  reordering()
		);
		
		CASE(N=n, randomVector(C,N,0,0),
		  group_generateGrouping(rangeV,rnd.nextInt(2,10),2,0,-1000,1000),
		  group_generateGrouping(rangeH,rnd.nextInt(N/2,N),2,0,-1000,1000),
		  
		  group_fillCells(rnd.nextInt(N/10*8,N/10*9),0),
		  generateStart(0,sf.first,-1000,1000),
		  generateFinish(0,sf.second,sf.second,-1000,1000),
		  
		  group_fillCells(N,1),
		  
		  reordering()
		);
		
		//Group big*small
		CASE(N=n, randomVector(C,N,0,0),
		  group_generateGrouping(rangeV,rnd.nextInt(N/2,N),2,0,-1000,1000),
		  group_generateGrouping(rangeH,rnd.nextInt(2,10),2,0,-1000,1000),
		  
		  group_fillCells(N/2,0),
		  generateStart(0,sf.first,-1000,1000),
		  
		  group_fillCells(N,1),
		  generateFinish(N/2,sf.second,sf.second,-1000,1000),
		  
		  reordering()
		);
		
		CASE(N=n, randomVector(C,N,0,0),
		  group_generateGrouping(rangeV,rnd.nextInt(N/2,N),2,0,-1000,1000),
		  group_generateGrouping(rangeH,rnd.nextInt(2,10),2,0,-1000,1000),
		  
		  group_fillCells(rnd.nextInt(N/10*8,N/10*9),0),
		  generateStart(0,sf.first,-1000,1000),
		  generateFinish(0,sf.second,sf.second,-1000,1000),
		  
		  group_fillCells(N,1),
		  
		  reordering()
		);
	}
  }
  
  void TestGroup4() {	//N<=1000, R=0, C=0
    Subtasks({3,4,6,7,8});
    
    vector<int> listN={1000};
    vector<pii> tipeSF={{-2,2}};
    for (auto n:listN) for (auto sf:tipeSF) TG_4_8(n,sf);
  }
  
  void TestGroup5() {	//N<=1000, C=0
    Subtasks({3,4,7,8});
      
    CASE(stairs(1000,sqrt(1000)),randomVector(C,N,0,0),reordering());
    CASE(N=1000,diagonal(N),randomVector(C,N,0,0),generateStart(0,-1),generateFinish(0,0,2),Fy=MAX_X,reordering());
    CASE(N=1000,randomVector(Y,N,MIN_X,MAX_X),sameValueVector(X,N,MIN_X,MIN_X),
      sameValueVector(R,N,MAX_R,MAX_R), randomVector(C,N,MIN_C,MIN_C),
      generateStart(0,-1), generateFinish(0,0,2), Fy=MAX_X, reordering()
    );
    
    
    vector<int> listN={1000};
    vector<pii> tipeSF={{-2,2}};
    for (auto n:listN) for (auto sf:tipeSF) TG_5_9(n,sf);
  }
  
  void TestGroup6() {	//N<=1000
    Subtasks({4,8});
    TG_6_10_Unique(10);
    TG_6_10_Unique(1000);
    CASE(N=1000,sameValueVector(X,N,MIN_X,MAX_X),sameValueVector(Y,N,MIN_X,MAX_X),
      sameValueVector(R,N,MIN_R,MAX_R), randomVector(C,N,MIN_C,MAX_C),
      generateStart(0,-1), generateFinish(0,0,2), Fy=MAX_X, reordering()
    );
    CASE(N=1000,randomVector(Y,N,MIN_X,MAX_X),sameValueVector(X,N,MIN_X,MIN_X),
      sameValueVector(R,N,MAX_R,MAX_R), randomVector(C,N,MIN_C,MAX_C),
      generateStart(0,-1), generateFinish(0,0,2), Fy=MAX_X, reordering()
    );
    
    vector<int> listN={1000};
    vector<pii> tipeSF={{-1,1},{1,-1}};
    for (auto n:listN) for (auto sf:tipeSF) for (auto n:listN) for (auto sf:tipeSF) TG_6_10(n,sf);
  }
  
  void TestGroup7() {	//XY<=1000, R=0, C=0
    Subtasks({5,6,7,8});
    vector<int> listN={20000};
    vector<pii> tipeSF={{0,0},{-1,1},{1,-1}};
    for (auto n:listN) for (auto sf:tipeSF) {
		if (sf==pii({-2,2})) {
		  sf.first=rnd.nextInt(0,1); sf.second=1-sf.first;
		  if (sf.first==0) sf.first--;
		  if (sf.second==0) sf.second--;
		}
		CASE(N=n, randomVector(C,N,0,0),
		  group_generateGrouping(rangeV,rnd.nextInt(sqrt(N)/2,sqrt(N)),2,0,-1000,1000),
		  group_generateGrouping(rangeH,rnd.nextInt(sqrt(N)/2,sqrt(N)),2,0,-1000,1000),
		  
		  group_fillCells(N/2,0),
		  generateStart(0,sf.first,-1000,1000),
		  
		  group_fillCells(N,1),
		  generateFinish(N/2,sf.second,sf.second,-1000,1000),
		  
		  reordering()
		);
		
		CASE(N=n, randomVector(C,N,0,0),
		  group_generateGrouping(rangeV,rnd.nextInt(sqrt(N),2*sqrt(N)),2,1,-1000,1000),
		  group_generateGrouping(rangeH,rnd.nextInt(sqrt(N),2*sqrt(N)),2,1,-1000,1000),
		  
		  group_fillCells(N,0),
		  generateStart(0,sf.first,-1000,1000),
		  generateFinish(0,sf.second,sf.second,-1000,1000),
		  
		  reordering()
		);
	}
	
	listN={20000,MAX_N};
	for (auto n:listN) {
		CASE(N=n,randomVector(X,N,-1000,1000), randomVector(Y,N,-1000,1000),
		  randomVector(R,N,0,0), randomVector(C,N,0,0),
		  generateStart(0,-1,-1000,1000), generateFinish(0,1,1,-1000,1000),
		  reordering()
		);
	}
  }
  
  void TestGroup8() {	//R=0, C=0
    Subtasks({6,7,8});
    
    CASE(stairs(MAX_N,1),randomVector(C,MAX_N,0,0),reordering());
       
    vector<int> listN={20000};
    vector<pii> tipeSF={{-2,2}};
    for (auto n:listN) for (auto sf:tipeSF) TG_4_8(n,sf);
	
	listN={MAX_N};
	for (auto n:listN) {
		CASE(N=n, randomVector(C,N,0,0),
		  group_generateGrouping(rangeV,rnd.nextInt(sqrt(N),2*sqrt(N)),1,0),
		  group_generateGrouping(rangeH,rnd.nextInt(sqrt(N),2*sqrt(N)),1,0),
		  
		  group_fillCells(N,0),
		  generateStart(0,-1),
		  generateFinish(0,1,1),
		  
		  reordering()
		);
		
		CASE(N=n, randomVector(C,N,0,0),
		  group_generateGrouping(rangeV,1,1,0),
		  group_generateGrouping(rangeH,N,1,0),
		  
		  group_fillCells(N,0),
		  generateStart(0,-1),
		  generateFinish(0,1,1),
		  
		  reordering()
		);
		
		CASE(N=n, randomVector(C,N,0,0),
		  group_generateGrouping(rangeV,N,1,0),
		  group_generateGrouping(rangeH,1,1,0),
		  
		  group_fillCells(N,0),
		  generateStart(0,-1),
		  generateFinish(0,1,1),
		  
		  reordering()
		);
	}
  }
  
  void TestGroup9() {	//C=0
    Subtasks({7,8});
    
    CASE(N=20000,randomVector(Y,N,MIN_X,MAX_X),sameValueVector(X,N,MIN_X,MIN_X),
      sameValueVector(R,N,MAX_R,MAX_R), randomVector(C,N,MIN_C,MIN_C),
      generateStart(0,-1), generateFinish(0,0,2), Fy=MAX_X, reordering()
    );
    CASE(N=20000,diagonal(N),randomVector(C,N,0,0),generateStart(0,-1),generateFinish(0,0,2),Fy=MAX_X,reordering());
    CASE(stairs(MAX_N,sqrt(MAX_N)),randomVector(C,MAX_N,0,0),reordering());
    
    vector<int> listN={20000};
    vector<pii> tipeSF={{-2,2}};
    for (auto n:listN) for (auto sf:tipeSF) TG_5_9(n,sf);
    
	listN={MAX_N};
	for (auto n:listN) {
		CASE(N=n, randomVector(C,N,0,0),
		  group_generateGrouping(rangeV,rnd.nextInt(sqrt(N),2*sqrt(N)),1,rnd.nextInt(100,10000)),
		  group_generateGrouping(rangeH,rnd.nextInt(sqrt(N),2*sqrt(N)),1,rnd.nextInt(100,10000)),
		  
		  group_fillCells(N/10,0,50),
		  group_fillCells(N,0),
		  generateStart(0,-1),
		  generateFinish(0,1,1),
		  
		  reordering()
		);
		
		CASE(N=n, randomVector(C,N,0,0),
		  group_generateGrouping(rangeV,1,1,rnd.nextInt(100,10000)),
		  group_generateGrouping(rangeH,N,1,rnd.nextInt(100,10000)),
		  
		  group_fillCells(N/10,0,50),
		  group_fillCells(N,0),
		  generateStart(0,-1),
		  generateFinish(0,1,1),
		  
		  reordering()
		);
		
		CASE(N=n, randomVector(C,N,0,0),
		  group_generateGrouping(rangeV,N,1,rnd.nextInt(100,10000)),
		  group_generateGrouping(rangeH,1,1,rnd.nextInt(100,10000)),
		  
		  group_fillCells(N/10,0,50),
		  group_fillCells(N,0),
		  generateStart(0,-1),
		  generateFinish(0,1,1),
		  
		  reordering()
		);
	}
  }
  
  void TestGroup10() {	//
    Subtasks({8});
    
    CASE(N=20000,sameValueVector(X,N,MIN_X,MAX_X),sameValueVector(Y,N,MIN_X,MAX_X),
      sameValueVector(R,N,MIN_R,MAX_R), randomVector(C,N,MIN_C,MAX_C),
      generateStart(0,-1), generateFinish(0,0,2), Fy=MAX_X, reordering()
    );
    CASE(N=20000,randomVector(Y,N,MIN_X,MAX_X),sameValueVector(X,N,MIN_X,MIN_X),
      sameValueVector(R,N,MAX_R,MAX_R), randomVector(C,N,MIN_C,MAX_C),
      generateStart(0,-1), generateFinish(0,0,2), Fy=MAX_X, reordering()
    );
    vector<int> listN={MAX_N};
    
    for (auto n:listN) TG_6_10_Unique(n);
	
	listN={20000};
	vector<pii> tipeSF={{0,0},{-1,1},{1,-1}};
	for (auto n:listN) for (auto sf:tipeSF) TG_6_10(n,sf);
	
	listN={MAX_N};
	for (auto n:listN) {
		CASE(N=n,
		  group_generateGrouping(rangeV,rnd.nextInt(sqrt(N),2*sqrt(N)),1,rnd.nextInt(100,10000)),
		  group_generateGrouping(rangeH,rnd.nextInt(sqrt(N),2*sqrt(N)),1,rnd.nextInt(100,10000)),
		  
		  group_fillCells(N/10,0,50),
		  group_fillCells(N,0),
		  generateStart(0,-1),
		  generateFinish(0,1,1),
		  
		  group_costCellGroup(rnd.nextInt(MIN_C,MAX_C-10),10,MAX_C),
		  reordering()
		);
		
		CASE(N=n,
		  group_generateGrouping(rangeV,1,1,rnd.nextInt(100,10000)),
		  group_generateGrouping(rangeH,N,1,rnd.nextInt(100,10000)),
		  
		  group_fillCells(N/10,0,50),
		  group_fillCells(N,0),
		  generateStart(0,-1),
		  generateFinish(0,1,1),
		  
		  group_costCellGroup(rnd.nextInt(MIN_C,MAX_C-10),10,MAX_C),
		  reordering()
		);
		
		CASE(N=n,
		  group_generateGrouping(rangeV,N,1,rnd.nextInt(100,10000)),
		  group_generateGrouping(rangeH,1,1,rnd.nextInt(100,10000)),
		  
		  group_fillCells(N/10,0,50),
		  group_fillCells(N,0),
		  generateStart(0,-1),
		  generateFinish(0,1,1),
		  
		  group_costCellGroup(rnd.nextInt(MIN_C,MAX_C-10),10,MAX_C),
		  reordering()
		);
	}
	CASE(N=20000,randomVector(X,N,MIN_X,-1),sameValueVector(Y,N,MIN_X,MIN_X),
      sameValueVector(R,N,MAX_R,MAX_R), randomVector(C,N,MIN_C,MAX_C),
      generateStart(0,-1), generateFinish(0,0,2), Fy=MAX_X, reordering()
    );
    CASE(N=20000,randomVector(Y,N,MIN_X,-1),sameValueVector(X,N,MIN_X,MIN_X),
      sameValueVector(R,N,MAX_R,MAX_R), randomVector(C,N,MIN_C,MAX_C),
      generateStart(0,-1), generateFinish(0,0,2), Fy=MAX_X, reordering()
    );
  }
  
//Testcase Caller
  void TG_4_8(int n,pii sf) {
    if (sf==pii({-2,2})) {
	  sf.first=rnd.nextInt(0,1); sf.second=1-sf.first;
	  if (sf.first==0) sf.first--;
	  if (sf.second==0) sf.second--;
	}
    //Group sqrt*sqrt
	CASE(N=n, randomVector(C,N,0,0),
	  group_generateGrouping(rangeV,rnd.nextInt(sqrt(N),2*sqrt(N)),2,0),
	  group_generateGrouping(rangeH,rnd.nextInt(sqrt(N),2*sqrt(N)),2,0),
	  
	  group_fillCells(N/2,0),
	  generateStart(0,sf.first),
	  
	  group_fillCells(N,1),
	  generateFinish(N/2,sf.second,sf.second),
	  
	  reordering()
	);
	
	CASE(N=n, randomVector(C,N,0,0),
	  group_generateGrouping(rangeV,rnd.nextInt(sqrt(N),2*sqrt(N)),2,0),
	  group_generateGrouping(rangeH,rnd.nextInt(sqrt(N),2*sqrt(N)),2,0),
	  
	  group_fillCells(rnd.nextInt(N/10*8,N/10*9),0),
	  generateStart(0,sf.first),
	  generateFinish(0,sf.second,sf.second),
	  
	  group_fillCells(N,1),
	  
	  reordering()
	);
	
	//Group small*big
	CASE(N=n, randomVector(C,N,0,0),
	  group_generateGrouping(rangeV,rnd.nextInt(2,10),2,0),
	  group_generateGrouping(rangeH,rnd.nextInt(N/2,N),2,0),
	  
	  group_fillCells(N/2,0),
	  generateStart(0,sf.first),
	  
	  group_fillCells(N,1),
	  generateFinish(N/2,sf.second,sf.second),
	  
	  reordering()
	);
	
	CASE(N=n, randomVector(C,N,0,0),
	  group_generateGrouping(rangeV,rnd.nextInt(2,10),2,0),
	  group_generateGrouping(rangeH,rnd.nextInt(N/2,N),2,0),
	  
	  group_fillCells(rnd.nextInt(N/10*8,N/10*9),0),
	  generateStart(0,sf.first),
	  generateFinish(0,sf.second,sf.second),
	  
	  group_fillCells(N,1),
	  
	  reordering()
	);
	
	//Group big*small
	CASE(N=n, randomVector(C,N,0,0),
	  group_generateGrouping(rangeV,rnd.nextInt(N/2,N),2,0),
	  group_generateGrouping(rangeH,rnd.nextInt(2,10),2,0),
	  
	  group_fillCells(N/2,0),
	  generateStart(0,sf.first),
	  
	  group_fillCells(N,1),
	  generateFinish(N/2,sf.second,sf.second),
	  
	  reordering()
	);
	
	CASE(N=n, randomVector(C,N,0,0),
	  group_generateGrouping(rangeV,rnd.nextInt(N/2,N),2,0),
	  group_generateGrouping(rangeH,rnd.nextInt(2,10),2,0),
	  
	  group_fillCells(rnd.nextInt(N/10*8,N/10*9),0),
	  generateStart(0,sf.first),
	  generateFinish(0,sf.second,sf.second),
	  
	  group_fillCells(N,1),
	  
	  reordering()
	);
  }
  void TG_5_9(int n,pii sf) {
    if (sf==pii({-2,2})) {
	  sf.first=rnd.nextInt(0,1); sf.second=1-sf.first;
	  if (sf.first==0) sf.first--;
	  if (sf.second==0) sf.second--;
	}
    //Group sqrt*sqrt
	CASE(N=n, randomVector(C,N,0,0),
	  group_generateGrouping(rangeV,rnd.nextInt(sqrt(N),2*sqrt(N)),2,rnd.nextInt(100,MAX_X/n)),
	  group_generateGrouping(rangeH,rnd.nextInt(sqrt(N),2*sqrt(N)),2,rnd.nextInt(100,MAX_X/n)),
	  
	  group_fillCells(N/2,0),
	  generateStart(0,sf.first),
	  
	  group_fillCells(N,1),
	  generateFinish(N/2,sf.second,sf.second),
	  
	  reordering()
	);
	
	CASE(N=n, randomVector(C,N,0,0),
	  group_generateGrouping(rangeV,rnd.nextInt(sqrt(N),2*sqrt(N)),2,rnd.nextInt(100,MAX_X/n)),
	  group_generateGrouping(rangeH,rnd.nextInt(sqrt(N),2*sqrt(N)),2,rnd.nextInt(100,MAX_X/n)),
	  
	  group_fillCells(rnd.nextInt(N/10*8,N/10*9),0),
	  generateStart(0,sf.first),
	  generateFinish(0,sf.second,sf.second),
	  
	  group_fillCells(N,1),
	  
	  reordering()
	);
	
	//Group small*big
	CASE(N=n, randomVector(C,N,0,0),
	  group_generateGrouping(rangeV,rnd.nextInt(2,10),2,rnd.nextInt(100,MAX_X/n)),
	  group_generateGrouping(rangeH,rnd.nextInt(N/2,N),2,rnd.nextInt(100,MAX_X/n)),
	  
	  group_fillCells(N/2,0),
	  generateStart(0,sf.first),
	  
	  group_fillCells(N,1),
	  generateFinish(N/2,sf.second,sf.second),
	  
	  reordering()
	);
	
	CASE(N=n, randomVector(C,N,0,0),
	  group_generateGrouping(rangeV,rnd.nextInt(2,10),2,rnd.nextInt(100,MAX_X/n)),
	  group_generateGrouping(rangeH,rnd.nextInt(N/2,N),2,rnd.nextInt(100,MAX_X/n)),
	  
	  group_fillCells(rnd.nextInt(N/10*8,N/10*9),0),
	  generateStart(0,sf.first),
	  generateFinish(0,sf.second,sf.second),
	  
	  group_fillCells(N,1),
	  
	  reordering()
	);
	
	//Group big*small
	CASE(N=n, randomVector(C,N,0,0),
	  group_generateGrouping(rangeV,rnd.nextInt(N/2,N),2,rnd.nextInt(100,MAX_X/n)),
	  group_generateGrouping(rangeH,rnd.nextInt(2,10),2,rnd.nextInt(100,MAX_X/n)),
	  
	  group_fillCells(N/2,0),
	  generateStart(0,sf.first),
	  
	  group_fillCells(N,1),
	  generateFinish(N/2,sf.second,sf.second),
	  
	  reordering()
	);
	
	CASE(N=n, randomVector(C,N,0,0),
	  group_generateGrouping(rangeV,rnd.nextInt(N/2,N),2,rnd.nextInt(100,MAX_X/n)),
	  group_generateGrouping(rangeH,rnd.nextInt(2,10),2,rnd.nextInt(100,MAX_X/n)),
	  
	  group_fillCells(rnd.nextInt(N/10*8,N/10*9),0),
	  generateStart(0,sf.first),
	  generateFinish(0,sf.second,sf.second),
	  
	  group_fillCells(N,1),
	  
	  reordering()
	);
  }
  void TG_6_10(int n,pii sf) {
    if (sf==pii({-2,2})) {
	  sf.first=rnd.nextInt(0,1); sf.second=1-sf.first;
	  if (sf.first==0) sf.first--;
	  if (sf.second==0) sf.second--;
	}
    //Group small*small	
	CASE(N=n,
	  group_generateGrouping(rangeV,rnd.nextInt(2,sqrt(N)),2,rnd.nextInt(100,MAX_X/n)),
	  group_generateGrouping(rangeH,rnd.nextInt(2,sqrt(N)),2,rnd.nextInt(100,MAX_X/n)),
	  
	  group_fillCells(rnd.nextInt(N/10*8,N/10*9),0),
	  generateStart(0,sf.first),
	  generateFinish(0,sf.second,sf.second),
	  
	  group_fillCells(N,1),
	  
	  group_costCellGroup(rnd.nextInt(MIN_C,MAX_C-10),10,MAX_C),
	  reordering()
	);
	
	//Group sqrt*sqrt	
	CASE(N=n,
	  group_generateGrouping(rangeV,rnd.nextInt(sqrt(N),2*sqrt(N)),2,rnd.nextInt(100,MAX_X/n)),
	  group_generateGrouping(rangeH,rnd.nextInt(sqrt(N),2*sqrt(N)),2,rnd.nextInt(100,MAX_X/n)),
	  
	  group_fillCells(rnd.nextInt(N/10*8,N/10*9),0),
	  generateStart(0,sf.first),
	  generateFinish(0,sf.second,sf.second),
	  
	  group_fillCells(N,1),
	  
	  group_costCellGroup(rnd.nextInt(MIN_C,MAX_C-10),10,MAX_C),
	  reordering()
	);
	
	//Group small*big		
	CASE(N=n,
	  group_generateGrouping(rangeV,rnd.nextInt(2,10),2,rnd.nextInt(100,MAX_X/n)),
	  group_generateGrouping(rangeH,rnd.nextInt(N/2,N),2,rnd.nextInt(100,MAX_X/n)),
	  
	  group_fillCells(rnd.nextInt(N/10*8,N/10*9),0),
	  generateStart(0,sf.first),
	  generateFinish(0,sf.second,sf.second),
	  
	  group_fillCells(N,1),
	  
	  group_costCellGroup(rnd.nextInt(MIN_C,MAX_C-10),10,MAX_C),
	  reordering()
	);
	
	CASE(N=n,
	  group_generateGrouping(rangeV,rnd.nextInt(2,10),1,rnd.nextInt(100,MAX_X/n)),
	  group_generateGrouping(rangeH,rnd.nextInt(N/2,N),1,rnd.nextInt(100,MAX_X/n)),
	  
	  group_fillCells(N,0),
	  generateStart(0,sf.first),
	  generateFinish(0,sf.second,sf.second),
	  
	  group_costCellGroup(rnd.nextInt(MIN_C,MAX_C-10),10,MAX_C),
	  reordering()
	);
	
	//Group big*small		
	CASE(N=n,
	  group_generateGrouping(rangeV,rnd.nextInt(N/2,N),2,rnd.nextInt(100,MAX_X/n)),
	  group_generateGrouping(rangeH,rnd.nextInt(2,10),2,rnd.nextInt(100,MAX_X/n)),
	  
	  group_fillCells(rnd.nextInt(N/10*8,N/10*9),0),
	  generateStart(0,sf.first),
	  generateFinish(0,sf.second,sf.second),
	  
	  group_fillCells(N,1),
	  
	  group_costCellGroup(rnd.nextInt(MIN_C,MAX_C-10),10,MAX_C),
	  reordering()
	);
	
	CASE(N=n,
	  group_generateGrouping(rangeV,rnd.nextInt(N/2,N),1,rnd.nextInt(100,MAX_X/n)),
	  group_generateGrouping(rangeH,rnd.nextInt(2,10),1,rnd.nextInt(100,MAX_X/n)),
	  
	  group_fillCells(N,0),
	  generateStart(0,sf.first),
	  generateFinish(0,sf.second,sf.second),
	  
	  group_costCellGroup(rnd.nextInt(MIN_C,MAX_C-10),10,MAX_C),
	  reordering()
	);
  }
  void TG_6_10_Unique(int n) {
	CASE(N=n,diagonal(n),randomVector(C,n,MIN_C,MAX_C),generateStart(0,-1),generateFinish(0,0,2),Fy=MAX_X,reordering());  
	
    CASE(stairs(n,1),randomVector(C,n,MAX_C,MAX_C),reordering());
	CASE(stairs(n,sqrt(n)),group_costCellGroup(MAX_C-100,rnd.nextInt(10,100),MAX_C),reordering());
	
	CASE(binaryTree(n),group_costCellGroup(MAX_C-100,rnd.nextInt(10,100),MAX_C),reordering());
	CASE(binaryTree_Sinked(n,true),group_costCellGroup(MAX_C-100,rnd.nextInt(10,100),MAX_C),reordering());
	CASE(binaryTree_Sinked(n,false),group_costCellGroup(MAX_C-100,rnd.nextInt(10,100),MAX_C),reordering());
	
	CASE(twoDepthTree_Sinked(n,sqrt(n)),group_costCellGroup(MAX_C-100,rnd.nextInt(10,100),MAX_C),reordering());
  }

private:
//Utility
  void randomVector(vector<int> &v,int sz,int l,int r) {
	  v.clear();
	  while (sz--) v.push_back(rnd.nextInt(l,r));
  }
  void sameValueVector(vector<int> &v,int sz,int l,int r) {
	  int x=rnd.nextInt(l,r); randomVector(v,sz,x,x);
  }
  void randomPoint(int &x,int &y,int l,int r) {
	  x=rnd.nextInt(l,r); y=rnd.nextInt(l,r);
  }
  void reordering() {
	  assert(X.size()==N && Y.size()==N && R.size()==N && C.size()==N);
	  tempReordering.clear();
	  for (int i=0;i<N;i++) tempReordering.push_back({{X[i],Y[i]},{R[i],C[i]}});
	  rnd.shuffle(tempReordering.begin(),tempReordering.end());
	  for (int i=0;i<tempReordering.size();i++) {
		  auto data=tempReordering[i];
		  X[i]=data.first.first;
		  Y[i]=data.first.second;
		  R[i]=data.second.first;
		  C[i]=data.second.second;
	  }
  }
  
  //Line sweep like model solution
  void getActualCellGroup() {
	  verticalGroup.clear(); horizontalGroup.clear(); cellGroup.clear();
	  groupRangeV.clear(); groupRangeH.clear();
	  for (int i=0;i<N;i++) {
		  horizontalGroup.push_back(-1);
		  verticalGroup.push_back(-1);
	  }

	  {
		  sweepV.clear();
		  for (int i=0;i<X.size();i++) {
			sweepV.push_back({{X[i]-R[i],0},i});
			sweepV.push_back({{X[i]+R[i],1},i});
		  }
	  
		  sort(sweepV.begin(),sweepV.end());
		  int stackSize=0, group=0;
		  int l=INF, r=-INF;
		  for (auto data:sweepV) {
			if (data.first.second==0) {
			  l=min(l,data.first.first);
			  stackSize++; verticalGroup[data.second]=group;
			}
			else {
			  r=max(r,data.first.first);
			  stackSize--;
			  if (stackSize==0) {
				  groupRangeV.push_back({l,r});
				  l=INF; r=-INF;
				  group++;  
			  }
			}
		  }
	  }
	  
	  {
		  sweepH.clear();
		  for (int i=0;i<Y.size();i++) {
			sweepH.push_back({{Y[i]-R[i],0},i});
			sweepH.push_back({{Y[i]+R[i],1},i});
		  }
	  
		  sort(sweepH.begin(),sweepH.end());
		  int stackSize=0, group=0;
		  int l=INF, r=-INF;
		  for (auto data:sweepH) {
			if (data.first.second==0) {
			  l=min(l,data.first.first);
			  stackSize++; horizontalGroup[data.second]=group;
			}
			else {
			  r=max(r,data.first.first);
			  stackSize--;
			  if (stackSize==0) {
				  groupRangeH.push_back({l,r});
				  l=INF; r=-INF;
				  group++;  
			  }
			}
		  }
	  }

	  for (int i=0;i<X.size();i++) {
		  assert(verticalGroup[i]!=-1);
		  assert(horizontalGroup[i]!=-1);
		  cellGroup[{verticalGroup[i],horizontalGroup[i]}].push_back(i);
	  }
  }

//Generate circles from given grouping
  //Generate group range
  void group_generateGrouping(vector<vector<pii> > &v,int sz,int component,int range=-1,int l=MIN_X,int r=MAX_X) {
	  if (range!=-1) assert((r-l+1)/(range+1)>=sz);
	  v.clear(); 
	  for (int i=0;i<component;i++) {
		  vector<pii> temp; v.push_back(temp);
	  }
	  vector<int> listL; listL.push_back(l);
	  for (int i=1;i<sz;i++) {
		  listL.push_back(listL.back()+(r-l+1)/sz);
	  }
	  for (int i=0;i<sz;i++) {
		  int sisa=sz-i;
		  if (range==-1) {
			  int kanan=rnd.nextInt(l,r-sisa+1);
			  v[i%component].push_back({l,kanan});
		  }
		  else {
			  int kiri=listL[i]+rnd.nextInt((r-l+1)/sz-range);
			  v[i%component].push_back({kiri,kiri+range});
		  }
	  }
  }
  
  //Add one circle to Cell Group
  void addCircleToCellGroup(int component,int idxV,int idxH,int persenR) {
	  auto rangeX=rangeV[component][idxV], rangeY=rangeH[component][idxH];
	  int maxR=min(rangeX.second-rangeX.first,rangeY.second-rangeY.first)/2;
	  int minR=maxR/100*persenR;
	  R.push_back(rnd.nextInt(minR,maxR));
	  X.push_back(rnd.nextInt(rangeX.first+R.back(),rangeX.second-R.back()));
	  Y.push_back(rnd.nextInt(rangeY.first+R.back(),rangeY.second-R.back()));
  }
  
  //Fill all cell groups with circles, uniform distribution
  void group_fillCells(int cnt,int component,int persenR=0) {
	  assert(!rangeV[component].empty() && !rangeH[component].empty());
	  idxVH.clear();
	  for (int i=0;i<rangeV[component].size();i++) {
		  for (int j=0;j<rangeH[component].size();j++) {
			  idxVH.push_back({{i,j},component});
		  }
	  }
	  rnd.shuffle(idxVH.begin(),idxVH.end());
	  while (X.size()!=cnt) {
		  for (auto data:idxVH) {
			  addCircleToCellGroup(data.second,data.first.first,data.first.second,persenR);
			  if (X.size()==cnt) break;
		  }
	  }
  }

//Generate Start/Finish (tipe: smallest (-1), random inside (0), largest (1), random total (2)
  //Generate coordinate (x or y)
  void getCoor(int idx,int &coor,bool forX,int tipe,int l,int r) {
	  tempCoor.clear();
	  for (int i=idx;i<X.size();i++) {
		  pair<int,int> temp;
		  if (forX) temp={max(l,X[i]-R[i]),min(r,X[i]+R[i])};
		  else temp={max(l,Y[i]-R[i]),min(r,Y[i]+R[i])};
		  tempCoor.push_back(temp);
	  }
	  if (tipe==2) coor=rnd.nextInt(l,r);
	  else if (tipe==0) {
		  pii temp=tempCoor[rnd.nextInt(tempCoor.size())];
		  coor=rnd.nextInt(temp.first,temp.second);
	  }
	  else if (tipe==-1) {
		  coor=r;
		  for (auto data:tempCoor) coor=min(coor,data.first);
	  }
	  else {
		  coor=l;
		  for (auto data:tempCoor) coor=max(coor,data.second);
	  }
  }
  
  //Generate starting point
  void generateStart(int idx,int tipe,int l=MIN_X,int r=MAX_X) {
	  assert(!Y.empty() && !R.empty());
	  assert(-1<=tipe && tipe<=2);
	  getCoor(idx,Sx,true,0,l,r);
	  getCoor(idx,Sy,false,tipe,l,r);
  }
  
  //Generate finish point
  void generateFinish(int idx,int tipeX,int tipeY,int l=MIN_X,int r=MAX_X) {
	  assert(!X.empty() && !Y.empty() && !R.empty());
	  assert(-1<=tipeX && tipeX<=2);
	  assert(-1<=tipeY && tipeY<=2);
	  getCoor(idx,Fx,true,tipeX,l,r);
	  getCoor(idx,Fy,false,tipeY,l,r);
  }
  
//Generate cost
  //Set one circle to c as the minimum cost in the circle
  void assignCellGroupCost(vector<int> &v,int c,int max_c) {
	  int idx=rnd.nextInt(v.size());
	  for (auto data:v) {
		  if (data==v[idx]) C[data]=c;
		  else C[data]=rnd.nextInt(c,max_c);
	  }
  }
  //Random cost, but cell group's cost is determined
  void group_costCellGroup(int l,int range,int max_c) {
	  assert(!X.empty() && !Y.empty() && !R.empty());
	  assert(l<=MAX_X-range);
	  int r=l+range;
	  getActualCellGroup();
	  for (int i=0;i<N;i++) C.push_back(-1);
	  for (auto cell:cellGroup) {
		  assignCellGroupCost(cell.second,rnd.nextInt(l,r),max_c);
	  }
	  for (int i=0;i<N;i++) assert(C[i]!=-1);
  }


//Custom made TC
  //Diagonal, all one component
  void diagonal(int sz,int l=MIN_X,int r=MAX_X) {
	  int curX=l, curY=l;
	  while (X.size()!=sz) {
		  int radius=rnd.nextInt(1,(r-l+1)/(sz*2));
		  X.push_back(curX+radius); Y.push_back(curY+radius); R.push_back(radius);
		  curX+=2*radius+1; curY+=2*radius;
	  }
  }
  
  //Stairs, one circle -> many cirlces -> one circles -> many circles -> ...
  void stairs(int sz,int blockSize) {
	  assert(blockSize+1<=sz);
	  int radius=(blockSize-1)/2;
	  Sx=Sy=MIN_X;
	  bool big=true;
	  int curX=MIN_X, curY=MIN_X;
	  while (X.size()!=sz-1) {
		  if (big) {
			  X.push_back(curX+radius); Y.push_back(curY+radius);
			  R.push_back(radius);
			  curX+=2*radius+10;
		  }
		  else {
			  int x=curX, y=curY;
			  for (int i=0;i<blockSize;i++) {
				  if (X.size()==sz-1) break;
				  X.push_back(x); Y.push_back(y); x++; y++;
				  R.push_back(0);
			  }
			  curY+=2*radius+10;
		  }
		  big=!big;
	  }
	  X.push_back(curX+radius); Y.push_back(curY+radius);
	  R.push_back(radius);
	  Fx=curX+2*radius+10; Fy=curY+2*radius; N=sz;
  }
  
  //Helper function to generate circles for Binary Tree
  void generateBinaryTree(vector<int> &v,int cur,int coor,bool forX,bool status) {
	  if (cur==0) return;
	  tempV.clear();
	  for (int i=0;i<cur;i++) {
		  tempV.push_back(coor);
		  if (status) coor-=6; else coor-=3;
	  }
	  if (!forX) reverse(tempV.begin(),tempV.end());
	  for (auto data:tempV) v.push_back(data);
	  if (status) generateBinaryTree(v,cur/2,coor,forX,!status);
	  else {
		  if (forX) generateBinaryTree(v,cur/2,tempV.front()-1,forX,!status);
		  else generateBinaryTree(v,cur/2,tempV.back()-1,forX,!status);
	  }
	  return;
  }
  
  //Binary Tree
  void binaryTree(int sz) {
	  int cur=1; while (2*cur-1<sz) cur*=2;
	  N=cur-1; cur/=2;
	  for (int i=0;i<N;i++) R.push_back(1);
	  generateBinaryTree(X,cur,0,true,true);
	  generateBinaryTree(Y,cur,0,false,false);
  }
  
  //Binary Tree + all leaves are connected to 1 big circle
  void binaryTree_Sinked(int sz,bool loc) {
	  binaryTree(sz); int cur=(N+1)/2;
	  int l=INF, r=-INF;
	  for (int i=0;i<cur;i++) {
		  if (loc) {
			  l=min(l,X[i]); r=max(r,X[i]);
		  }
		  else {
			  l=min(l,Y[i]); r=max(r,Y[i]);
		  }
	  }
	  if (loc) {
		  X.push_back((l+r)/2); Y.push_back(MAX_X); R.push_back((r-l)/2+3);
	  }
	  else {
		  Y.push_back((l+r)/2); X.push_back(MAX_X); R.push_back((r-l)/2+3);
	  }
	  N++; Fx=Fy=MAX_X;
  }
  
  //Tree with 2 depth (intended for sqrt children) + all leaves are connected to 1 big circle
  void twoDepthTree_Sinked(int sz,int block) {
	  assert(block<=MAX_N/block);
	  Sx=Sy=MIN_X;
	  tempV.clear();
	  for (int i=0;i<block;i++) {
		  X.push_back(MIN_X+i*1E5+5E4);
		  Y.push_back(MIN_X);
		  R.push_back(5E4-1);
		  tempV.push_back(X.back()-R.back());
	  }
	  N=sz; int curY=1E8; int l,r; l=r=curY;
	  while (X.size()!=sz-1) {
		  for (int i=0;i<block;i++) {
			  if (X.size()==sz-1) break;
			  X.push_back(tempV[i]); tempV[i]++;
			  Y.push_back(curY); l=min(l,curY); curY--;
			  R.push_back(0);
		  }
	  }
	  X.push_back(MAX_X); Y.push_back(5E7); R.push_back(5E7);
	  Fx=Fy=MAX_X;
  }
};
