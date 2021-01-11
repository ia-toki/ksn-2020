#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

const int MAXN=50000;
const int MAXK=400;
const int SmallN=2000;
const int SmallK=20;

template<typename data>
bool eachElementBetween(const vector<data> &V,data mins,data maks) {
	for (data x : V) {
		if (x<mins||x>maks) {
			return 0;
		}
	}
	
	return 1;
}

class ProblemSpec : public BaseProblemSpec {
protected:
	int N, M, K, ans;
	vector <int> H;
	
	void InputFormat() {
		LINE(N,M,K);
		LINE(H%SIZE(N));
	}
	
	void OutputFormat() {
		LINE(ans);
	}
	
	void GradingConfig() {
		TimeLimit(2);
		MemoryLimit(256);
    }
	
	void Constraints() {
		CONS(1<=M&&M<=N&&N<=MAXN);
		CONS(0<=K&&K<=N&&K<=MAXK);
		CONS(eachElementBetween(H,1,N));
    }
	
	void StyleConfig() {
		CustomScorer();
	}
	
	void Subtask1() {
		CONS(N==13);
		CONS(M==3);
		CONS(K==1);
		CONS(H==vector<int>({1,1,1,1,1,1,1,1,1,1,1,1,1}));
	}
	
	void Subtask2() {
		CONS(N==15);
		CONS(M==1);
		CONS(K==2);
		CONS(H==vector<int>({1,2,3,4,4,4,3,2,1,5,6,6,7,7,5}));
	}
	
	void Subtask3() {
		CONS(eachElementBetween(H,1,1));
	}
	
	void Subtask4() {
		CONS(N<=SmallN);
		CONS(K==0);
	}
	
	void Subtask5() {
		CONS(N<=SmallN);
		CONS(K<=SmallK);
	}
	
	void Subtask6() {
		CONS(K==0);
	}
	
	void Subtask7() {
		CONS(K<=SmallK);
	}
	
	void Subtask8() {
	}
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
	void SampleTestCase1() {
		Subtasks({5,7,8});
		Input({
			"8 2 1",
			"1 1 2 2 1 2 2 2"
		});
		Output({
			"2"
		});
	}
	
	void SampleTestCase2() {
		Subtasks({4,5,6,7,8});
		Input({
			"5 1 0",
			"3 3 3 3 3"
		});
		Output({
			"5"
		});
	}
	
	void TestGroup1() {
		Subtasks({1,3,5,7,8});
		
		CASE(N=13,M=3,K=1,H={1,1,1,1,1,1,1,1,1,1,1,1,1});
	}
	
	void TestGroup2() {
		Subtasks({2,5,7,8});
		
		CASE(N=15,M=1,K=2,H={1,2,3,4,4,4,3,2,1,5,6,6,7,7,5});
	}
	
	void TestGroup3() {
		Subtasks({3,4,5,6,7,8});
		
		CASE(N=1,M=1,K=0,H=fillOnes(N));
		CASE(N=SmallN,M=1,K=0,H=fillOnes(N));
		CASE(N=SmallN,M=N,K=0,H=fillOnes(N));
		CASE(N=rnd.nextInt(2,SmallN),M=rnd.nextInt(1,N),K=0,H=fillOnes(N));
	}
	
	void TestGroup4() {
		Subtasks({3,5,7,8});
		
		CASE(K=SmallK,N=K,M=1,H=fillOnes(N));
		CASE(K=SmallK,N=K,M=N,H=fillOnes(N));
		CASE(N=SmallN,M=1,K=SmallK,H=fillOnes(N));
		CASE(N=SmallN,M=N,K=SmallK,H=fillOnes(N));
		CASE(N=SmallN,K=SmallK,M=N-K,H=fillOnes(N));
		CASE(N=rnd.nextInt(SmallK+1,SmallN),M=rnd.nextInt(1,N),K=rnd.nextInt(1,SmallK),H=fillOnes(N));
	}
	
	void TestGroup5() {
		Subtasks({3,6,7,8});
		
		CASE(N=MAXN,M=1,K=0,H=fillOnes(N));
		CASE(N=MAXN,M=21,K=0,H=fillOnes(N));
		CASE(N=MAXN-1,M=641,K=0,H=fillOnes(N));
		CASE(N=MAXN,M=250,K=0,H=fillOnes(N));
		CASE(N=MAXN,M=N,K=0,H=fillOnes(N));
		CASE(N=rnd.nextInt(SmallN+1,MAXN),M=rnd.nextInt(1,N),K=0,H=fillOnes(N));
	}
	
	void TestGroup6() {
		Subtasks({3,7,8});
		
		CASE(N=MAXN,M=1,K=SmallK,H=fillOnes(N));
		CASE(N=MAXN,M=N,K=SmallK,H=fillOnes(N));
		CASE(N=MAXN,K=SmallK,M=N-K,H=fillOnes(N));
		CASE(N=rnd.nextInt(SmallK+1,MAXN),M=rnd.nextInt(1,N),K=rnd.nextInt(1,SmallK),H=fillOnes(N));
	}
	
	void TestGroup7() {
		Subtasks({3,8});
		
		CASE(N=MAXN,M=1,K=MAXK,H=fillOnes(N));
		CASE(N=MAXN,M=297,K=MAXK,H=fillOnes(N));
		CASE(N=MAXN,M=248,K=MAXK,H=fillOnes(N));
		CASE(N=MAXN,M=1181,K=MAXK-1,H=fillOnes(N));
		CASE(N=MAXN,M=N,K=MAXK,H=fillOnes(N));
		CASE(N=MAXN,K=MAXK,M=N-K,H=fillOnes(N));
		CASE(N=rnd.nextInt(SmallN+1,MAXN),M=rnd.nextInt(1,N),K=rnd.nextInt(SmallK+1,MAXK),H=fillOnes(N));
		
		for (int i=-1;i<=1;i++) {
			CASE(K=rnd.nextInt(SmallK+1,MAXK),M=rnd.nextInt(1,SmallN),N=rnd.nextInt(1,(MAXN-1)/M)*M+K+i,H=fillOnes(N));
		}
	}
	
	void TestGroup8() {
		Subtasks({4,5,6,7,8});
		
		CASE(N=2,M=1,K=0,H=fillPermutation(N));
		CASE(N=SmallN,M=1,K=0,H=fillPermutation(N));
		CASE(N=SmallN,M=1,K=0,H=fillRand(N,1));
		CASE(N=SmallN,M=2,K=0,H=fillRand(N,2));
		CASE(N=SmallN,M=10,K=0,H=fillRand(N,10));
		CASE(N=SmallN,M=N,K=0,H=fillRand(N,N));
		CASE(N=rnd.nextInt(SmallN/2,SmallN),M=7,K=0,H=fillRand(N,rnd.nextInt(2,10)));
		CASE(N=rnd.nextInt(SmallN/2,SmallN),M=4,K=0,H=fillRand(N,rnd.nextInt(2,100)));
	}
	
	void TestGroup9() {
		Subtasks({5,7,8});
		
		CASE(K=SmallK,N=K,M=1,H=fillPermutation(N));
		CASE(K=SmallK,N=K,M=N,H=fillPermutation(N));
		CASE(N=SmallN,M=1,K=SmallK,H=fillPermutation(N));
		CASE(N=SmallN,M=1,K=1,H=fillRand(N,1));
		CASE(N=SmallN,M=2,K=SmallK,H=fillRand(N,2));
		CASE(N=SmallN,M=1,K=SmallK,H=fillRand(N,3));
		CASE(N=SmallN,M=1,K=SmallK,H=fillRand(N,N));
		CASE(N=SmallN,M=N,K=SmallK,H=fillRand(N,N));
		CASE(N=rnd.nextInt(SmallN/2,SmallN),M=7,K=rnd.nextInt(SmallK/2,SmallK),H=fillRand(N,rnd.nextInt(2,10)));
		strongTc1(SmallN,SmallK);
		strongTc2(SmallN,SmallK,4,6,1900,20);
	}
	
	void TestGroup10() {
		Subtasks({6,7,8});
		
		CASE(N=SmallN+1,M=1,K=0,H=fillPermutation(N));
		CASE(N=MAXN,M=1,K=0,H=fillPermutation(N));
		CASE(N=MAXN,M=1,K=0,H=fillRand(N,1));
		CASE(N=MAXN,M=1,K=0,H=fillRand(N,2));
		CASE(N=MAXN,M=2,K=0,H=fillRand(N,2));
		CASE(N=MAXN,M=1,K=0,H=fillRand(N,3));
		CASE(N=MAXN,M=1,K=0,H=fillRand(N,1000));
		CASE(N=MAXN,M=1,K=0,H=fillRand(N,N));
		CASE(N=MAXN,M=N,K=0,H=fillRand(N,N));
		CASE(N=MAXN,M=1,K=0,H=fillPalindrom(N));
		CASE(N=MAXN,M=1,K=0,H=fillPeriod(N,N/2));
		CASE(N=rnd.nextInt(SmallN+1,MAXN),M=8,K=0,H=fillRand(N,rnd.nextInt(2,10)));
	}
	
	void TestGroup11() {
		Subtasks({7,8});
		
		CASE(N=SmallN+1,M=1,K=1,H=fillPermutation(N));
		CASE(N=MAXN,M=1,K=SmallK,H=fillPermutation(N));
		CASE(N=MAXN,M=1,K=SmallK,H=fillRand(N,1));
		CASE(N=MAXN,M=1,K=SmallK,H=fillRand(N,2));
		CASE(N=MAXN,M=2,K=11,H=fillRand(N,2));
		CASE(N=MAXN,M=1,K=5,H=fillRand(N,3));
		CASE(N=MAXN,M=1,K=SmallK,H=fillRand(N,1000));
		CASE(N=MAXN,M=1,K=7,H=fillRand(N,N));
		CASE(N=MAXN,M=N,K=SmallK,H=fillRand(N,N));
		CASE(N=MAXN,M=1,K=SmallK,H=fillPalindrom(N));
		CASE(N=MAXN,M=1,K=SmallK,H=fillPeriod(N,N/2));
		CASE(N=rnd.nextInt(MAXN/2,MAXN),M=6,K=SmallK,H=fillRand(N,rnd.nextInt(2,10)));
		CASE(N=rnd.nextInt(MAXN/2,MAXN),M=3,K=SmallK,H=fillRand(N,rnd.nextInt(2,100)));
		strongTc1(MAXN,SmallK);
		strongTc2(MAXN,SmallK,21,46,40000,20);
	}
	
	void TestGroup12() {
		Subtasks({8});
		
		CASE(N=MAXN,M=1,K=MAXK,H=fillPermutation(N));
		CASE(N=SmallN+1,M=1,K=SmallK+1,H=fillRand(N,2));
		CASE(N=MAXN,M=1,K=MAXK,H=fillRand(N,1));
		CASE(N=MAXN,M=1,K=MAXK,H=fillRand(N,2));
		CASE(N=MAXN,M=2,K=100,H=fillRand(N,2));
		CASE(N=MAXN,M=1,K=21,H=fillRand(N,3));
		CASE(N=MAXN,M=1,K=MAXK,H=fillRand(N,1000));
		CASE(N=MAXN,M=1,K=250,H=fillRand(N,N));
		CASE(N=MAXN,M=N,K=250,H=fillRand(N,N));
		CASE(N=MAXN,M=1,K=MAXK,H=fillPalindrom(N));
		CASE(N=MAXN,M=1,K=MAXK,H=fillPeriod(N,N/2));
		CASE(N=MAXN,M=1,K=MAXK,H=fillPeriod(N,2));
		CASE(N=MAXN,M=1,K=MAXK,H=fillPeriod(N,224));
		CASE(N=rnd.nextInt(MAXN/20,MAXN/10),M=3,K=rnd.nextInt(300,MAXK),H=fillRand(N,rnd.nextInt(2,10)));
		CASE(N=rnd.nextInt(MAXN/2,MAXN),M=10,K=rnd.nextInt(300,MAXK),H=fillRand(N,rnd.nextInt(2,10)));
		CASE(N=rnd.nextInt(40000,MAXN),M=12,K=rnd.nextInt(300,MAXK),H=fillRand(N,rnd.nextInt(2,100)));
		strongTc1(MAXN,MAXK);
		strongTc2(MAXN,MAXK,19,31,40000,300);
		strongTc3(MAXN,MAXK,200);
		strongTc3(MAXN,MAXK,132);
		strongTc3(MAXN,MAXK,302);
	}
	
	vector <int> ret, temp;
	
	vector <int> fillOnes(int size) {
		ret.clear();
		
		for (int i=0;i<size;i++) {
			ret.push_back(1);
		}
		
		return ret;
	}
	
	vector <int> fillPermutation(int size) {
		ret.clear();
		
		for (int i=0;i<size;i++) {
			ret.push_back(i+1);
			swap(ret[rnd.nextInt(0,i)],ret[i]);
		}
		
		return ret;
	}
	
	vector <int> fillRand(int size,int type) {
		fillPermutation(size);
		temp.clear();
		
		for (int i=0;i<size;i++) {
			temp.push_back(ret[rnd.nextInt(0,type-1)]);
		}
		
		return temp;
	}
	
	vector <int> fillPalindrom(int size) {
		fillPermutation(size);
		
		for (int i=0;2*i<size;i++) {
			ret[size-1-i]=ret[i];
		}
		
		return ret;
	}
	
	vector <int> fillPeriod(int size,int mod) {
		fillPermutation(size);
		
		for (int i=mod;i<size;i++) {
			ret[i]=ret[i-mod];
		}
		
		return ret;
	}
	
	void strongTc1(int n,int k) {
		temp=fillPermutation(n);
		fillPermutation(n);
		
		for (int i=1;i<=k;i++) {
			ret[temp[i]-1]=ret[temp[0]-1];
		}
		
		vector <int> h=ret;
		CASE(N=n,M=1,K=k,H=h);
	}
	
	void strongTc3(int n,int k,int d) {
		int m=(n-k)/4-1;
		vector <int> h;
		h.clear();
		
		for (int i=0;i<2;i++) {
			h.push_back(3);
		}
		
		for (int i=0;i<m+d;i++) {
			h.push_back(1);
		}
		
		for (int i=0;i<m;i++) {
			h.push_back(2);
		}
		
		for (int i=0;i<m;i++) {
			h.push_back(1);
		}
		
		for (int i=0;i<m+k-d;i++) {
			h.push_back(2);
		}
		
		for (int i=0;i<2;i++) {
			h.push_back(3);
		}
		
		CASE(N=n,M=m,K=k,H=h);
	}
	
	int DP[MAXN+1][MAXK+1];
	int A[MAXN+1];
	int del[MAXK+1];
	int ptr[MAXK+1];
	int track[MAXK+1];
	int cnt[MAXK+1][50];
	
	void strongTc2(int n,int k,int m,int maxA,int minN,int minK) {
		int nn=0, kk=0;
		
		while (nn<minN||kk<minK) {
			for (int i=1;i<=n;i++) {
				A[i]=rnd.nextInt(1,maxA);
			}
			
			for (int i=0;i<=k;i++) {
				del[i]=0;
				ptr[i]=0;
				track[i]=0;
				
				for (int j=1;j<=maxA;j++) {
					cnt[i][j]=0;
				}
			}
			
			for (int i=1;i<=n;i++) {
				for (int j=0;j<=k;j++) {
					if (++cnt[j][A[i]]>m) {
						del[j]++;
					}
					
					while (del[j]>j) {
						ptr[j]++;
						if (--cnt[j][A[ptr[j]]]>=m) {
							del[j]--;
						}
					}
				}
				
				for (int j=k;j>=0;j--) {
					if (DP[ptr[track[j]]][j-track[j]]<DP[i-1][j]) {
						DP[i][j]=DP[i-1][j];
					}
					else if (j&&DP[ptr[track[j-1]+1]][j-track[j-1]-1]<DP[i-1][j]) {
						if (track[j]<track[j-1]) {
							nn=i;
							kk=j;
						}
						
						DP[i][j]=DP[i-1][j];
						track[j]=track[j-1]+1;
					}
					else {
						DP[i][j]=DP[i-1][j]+1;
						track[j]=0;
					}
				}
			}
		}
		
		fillPermutation(nn);
		temp.clear();
		
		for (int i=1;i<=nn;i++) {
			temp.push_back(ret[A[i]-1]);
		}
		
		vector <int> h=temp;
		CASE(N=nn,M=m,K=kk,H=h);
	}
};
