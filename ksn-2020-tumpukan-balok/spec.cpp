#include <tcframe/runner.hpp>
using namespace tcframe;

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN=2E5;
const int MAXQ=2E5;
const int MAXH=1E9;
const int k10 =1e4;
const int k30 =3e4;
const int k50 =5e4;
const int k100=1e5;

class ProblemSpec : public BaseProblemSpec {
protected:
    int N, Q;
    vector<ll> H,K;

    vector<int> ANS;

    void InputFormat() {
        LINE(N);
        LINE(H % SIZE(N));
        LINE(Q);
        LINES(K) % SIZE(Q);
    }

    void OutputFormat() {
        LINES(ANS) % SIZE(Q);
    }

    void StyleConfig() {
        CustomScorer();
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(256);
    }

    void Constraints() {
        CONS(between(N, 1, MAXN));
        CONS(allBetween(H, 0, MAXH));
        CONS(between(Q, 1, MAXQ));
        CONS(allBetween(K, 1, getSum(H)));
    }

    void Subtask1() {   //open subtask 1
        CONS(N==5);
        CONS(H==vector<ll>({3,4,5,4,3}));
        CONS(Q==6);
        CONS(K==vector<ll>({3,6,9,12,15,18}));
    }

    void Subtask2() {   //open subtask 2
        CONS(N==15);
        CONS(H==vector<ll>({8,4,8,2,8,4,8,1,8,4,8,2,8,4,8}));
        CONS(Q==7);
        CONS(K==vector<ll>({1,2,4,8,16,32,64}));
    }

    void Subtask3(){
        CONS(isEqual(N, H));
    }

    void Subtask4(){
        CONS(N<=1000);
        CONS(allBetween(H, 0, 1000));
        CONS(Q==1);
    }

    void Subtask5(){
        CONS(allBetween(H, 0, 5));
    }

    void Subtask6(){
        CONS(isSorted(N, H));
    }

    void Subtask7(){
        CONS(Q==1);
    }

    void Subtask8(){
        CONS(N<=5000);
    }

    void Subtask9(){
    }

private:
    bool between(ll x,ll l,ll r) {
        return (l<=x && x<=r);
    }
    bool allBetween(vector<ll> &x,ll l,ll r) {
        for (auto data:x) if (!between(data,l,r)) return false; return true;
    }
    long long getSum(vector<ll> &x){
        ll SUM = 0;
        for (auto data:x) SUM+= data;
        return SUM;
    }
    bool isEqual(int n, vector<ll> &x){
        for(int i = 1; i<n; ++i) if (x[0] != x[i]) return false; return true;
    }
    bool isSorted(int n, vector<ll> &x){
        for(int i = 1; i<n; ++i) if (x[i-1] > x[i]) return false; return true;
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Subtasks({5,8,9});
        Input({
            "5",
            "3 1 2 0 1",
            "3",
            "1",
            "3",
            "7",
        });
        Output({
            "1",
            "3",
            "5"
        });
    }

    void BeforeTestCase() {
        H.clear(); K.clear();
    }

    void TestGroup1() { //open subtask 1
        Subtasks({1,5,8,9});
        CASE( N=5, Q=6, H={3,4,5,4,3},  K={3,6,9,12,15,18} );
    }

    void TestGroup2() { //open subtask 2
        Subtasks({2,8,9});
        CASE( N=15, Q=7, H={8,4,8,2,8,4,8,1,8,4,8,2,8,4,8}, K={1,2,4,8,16,32,64} );
    }

    void TestGroup3() {
        Subtasks({3,4,6,7,8,9});

        CASE( N=1, Q=1, H={754}, K={723} );
        CASE( N=10, Q=1, sameElements(N, H, 1, 1000), randomElements(Q,K,1,getSum(H)));
        CASE( N=101, Q=1, sameElements(N, H, 1, 1000), randomElements(Q,K,1,getSum(H)));
        CASE( N=1000, Q=1, sameElements(N, H, 1, 1000), randomElements(Q,K,1,getSum(H)));
        CASE( N=1000, Q=1, sameElements(N, H, 1000, 1000), randomElements(Q,K,1,getSum(H)));
    }

    void TestGroup4() {
        Subtasks({3,5,6,8,9});

        CASE( N=1, Q=2, H={1}, K={1,1} );
        CASE( N=1, Q=100, sameElements(N, H, 3, 3), randomElements(Q,K,1,getSum(H)) );
        CASE( N=1, Q=100, sameElements(N, H, 5, 5), randomElements(Q,K,1,getSum(H)) );
        CASE( N=2, Q=100, sameElements(N, H, 4, 4), randomElements(Q,K,1,getSum(H)) );
        CASE( N=4977, Q=5000, sameElements(N, H, 4, 4), randomElements(Q,K,1,getSum(H)) );
        CASE( N=5000, Q=5000, sameElements(N, H, 5, 5), randomElements(Q,K,1,getSum(H)) );
    }

    void TestGroup5() {
        Subtasks({3,5,6,9});

        CASE( N=k10+1231, Q=5000, sameElements(N, H, 1, 4), randomElements(Q,K,1,getSum(H)));
        CASE( N=k30+92, Q=5000, sameElements(N, H, 5, 5), randomElements(Q,K,1,getSum(H)));
    }

    void TestGroup6() {
        Subtasks({3,6,9});

        CASE( N=22627, Q=5000, sameElements(N, H, 1, MAXH), randomElements(Q,K,1,getSum(H)));
        CASE( N=k30+177, Q=k10, sameElements(N, H, MAXH-10, MAXH-1), randomElements(Q,K,1,getSum(H)));
        CASE( N=MAXN, Q=MAXQ, sameElements(N, H, MAXH, MAXH), randomElements(Q,K,1,getSum(H)));
    }

    void TestGroup7() {
        Subtasks({4,5,6,7,8,9});

        CASE( N=10, Q=1, sortedElements(N, H, 0, 5), randomElements(Q,K,1,getSum(H)));
        CASE( N=127, Q=1, sortedElements(N, H, 0, 5), randomElements(Q,K,1,getSum(H)));
        CASE( N=777, Q=1, sortedElements(N, H, 0, 5), randomElements(Q,K,1,getSum(H)));
        CASE( N=1000, Q=1, sortedElements(N, H, 0, 5), randomElements(Q,K,1,getSum(H)));
    }

    void TestGroup8() {
        Subtasks({4,5,7,8,9});

        CASE( N=327, Q=1, randomElements(N, H, 0, 5), randomElements(Q,K,1,getSum(H)));
        CASE( N=767, Q=1, randomElements(N, H, 0, 5), randomElements(Q,K,1,getSum(H)));
        CASE( N=1000, Q=1, randomElements(N, H, 0, 5), randomElements(Q,K,1,getSum(H)));
    }

    void TestGroup9() {
        Subtasks({4,6,7,8,9});

        CASE( N=384, Q=1, sortedElements(N, H, 0, 1000), randomElements(Q,K,1,getSum(H)));
        CASE( N=743, Q=1, sortedElements(N, H, 0, 1000), randomElements(Q,K,1,getSum(H)));
        CASE( N=1000, Q=1, sortedElements(N, H, 0, 1000), randomElements(Q,K,1,getSum(H)));
    }

    void TestGroup10() {
        Subtasks({4,7,8,9});

        CASE( N=777, Q=1, randomElements(N, H, 0, 1000), K={rnd.nextLongLong(1,getSum(H))});
        CASE( N=834, Q=1, randomElements(N, H, 0, 1000), K={rnd.nextLongLong(1,getSum(H))});
        CASE( N=1000, Q=1, randomElements(N, H, 0, 1000), K={rnd.nextLongLong(1,getSum(H))});
        CASE( N=1000, Q=1, alternatingElements(N, H, 1, 1000), K={rnd.nextLongLong(1,getSum(H))});
        CASE( N=1000, Q=1, alternatingElementsV2(N, H, 2, 1000), K={rnd.nextLongLong(1,getSum(H))});
        CASE( N=1000, Q=1, shuffleElements(N, H, 1), K={rnd.nextLongLong(1,getSum(H))});
        CASE( N=1000, Q=1, mixed(N, H, 3, 1000), K={rnd.nextLongLong(1,getSum(H))});
        CASE( N=1000, Q=1, dncElements(N, H, 0, 1000), K={rnd.nextLongLong(1,getSum(H))});

        CASE( N=753, Q=1, randomElements(N, H, 0, 1000), randomElements(Q,K,1,getSum(H)));
        CASE( N=1000, Q=1, randomElements(N, H, 0, 1000), randomElements(Q,K,1,getSum(H)));
        CASE( N=1000, Q=1, sortedElementsReverse(N, H, 0, 1000), randomElements(Q,K,1,getSum(H)));
        CASE( N=1000, Q=1, alternatingElements(N, H, 0, 1000), randomElements(Q,K,1,getSum(H)));
        CASE( N=1000, Q=1, alternatingElementsV2(N, H, 0, 1000), randomElements(Q,K,1,getSum(H)));
        CASE( N=1000, Q=1, shuffleElements(N, H, 1), randomElements(Q,K,1,getSum(H)));
        CASE( N=1000, Q=1, mixed(N, H, 3, 1000), randomElements(Q,K,1,getSum(H)));
        CASE( N=1000, Q=1, mixed(N, H, 900, 1000), randomElements(Q,K,1,getSum(H)));
        CASE( N=1000, Q=1, dncElements(N, H, 0, 1000), randomElements(Q,K,1,getSum(H)));
    }

    void TestGroup11() {
        Subtasks({5,6,8,9});

        CASE( N=684, Q=5000, sortedElements(N, H, 0, 5), randomElements(Q,K,1,getSum(H)));
        CASE( N=4943, Q=5000, sortedElements(N, H, 0, 5), randomElements(Q,K,1,getSum(H)));
        CASE( N=5000, Q=5000, sortedElements(N, H, 0, 5), randomElements(Q,K,1,getSum(H)));
    }

    void TestGroup12() {
        Subtasks({5,6,9});

        CASE( N=k10+1131, Q=k10, sortedElements(N, H, 0, 5), randomElements(Q,K,1,getSum(H)));
        CASE( N=MAXN, Q=MAXQ, sortedElements(N, H, 0, 5), randomElements(Q,K,1,getSum(H)));
    }

    void TestGroup13() {
        Subtasks({5,8,9});

        CASE( N=694 , Q=k10, randomElements(N, H, 0, 5), randomElements(Q,K,1,getSum(H)));
        CASE( N=4973, Q=k10, randomElements(N, H, 0, 5), randomElements(Q,K,1,getSum(H)));
        CASE( N=5000, Q=k10, randomElements(N, H, 0, 5), randomElements(Q,K,1,getSum(H)));
    }

    void TestGroup14() {
        Subtasks({5,9});

        CASE( N=k50+1231, Q=k10, randomElements(N, H, 0, 5), randomElements(Q,K,1,getSum(H)));
        CASE( N=MAXN, Q=k10, sortedElementsReverse(N, H, 0, 5), randomElements(Q,K,1,getSum(H)));
        CASE( N=k100+1621, Q=k10, alternatingElements(N, H, 0, 5), randomElements(Q,K,1,getSum(H)));
        CASE( N=MAXN, Q=k10, alternatingElementsV2(N, H, 0, 5), randomElements(Q,K,1,getSum(H)));
        CASE( N=MAXN, Q=MAXQ, mixed(N, H, 0, 5), randomElements(Q,K,1,getSum(H)));
    }

    void TestGroup15() {
        Subtasks({6,7,8,9});

        CASE( N=977, Q=1, sortedElements(N, H, 0, MAXH), randomElements(Q,K,1,getSum(H)));
        CASE( N=5000, Q=1, sortedElements(N, H, 0, MAXH), randomElements(Q,K,1,getSum(H)));
        CASE( N=5000, Q=1, sortedElements(N, H, MAXH-10000, MAXH), randomElements(Q,K,1,getSum(H)));
    }

    void TestGroup16() {
        Subtasks({6,8,9});

        CASE( N=3977, Q=k10, sortedElements(N, H, 0, MAXH), randomElements(Q,K,1,getSum(H)));
        CASE( N=5000, Q=k10, sortedElements(N, H, 0, MAXH), randomElements(Q,K,1,getSum(H)));
        CASE( N=5000, Q=k10, sortedElements(N, H, MAXH-10000, MAXH), randomElements(Q,K,1,getSum(H)));
    }

    void TestGroup17() {
        Subtasks({6,7,9});

        CASE( N=k10+5761, Q=1, sortedElements(N, H, 0, MAXH), randomElements(Q,K,1,getSum(H)));
        CASE( N=MAXN, Q=1, sortedElements(N, H, 0, MAXH), randomElements(Q,K,1,getSum(H)));
        CASE( N=MAXN, Q=1, sortedElements(N, H, MAXH-10000, MAXH), randomElements(Q,K,1,getSum(H)));
    }

    void TestGroup18() {
        Subtasks({6,9});

        CASE( N=k10+5761, Q=k10, sortedElements(N, H, 0, MAXH), randomElements(Q,K,1,getSum(H)));
        CASE( N=k10+6761, Q=k10, sortedElements(N, H, 0, 5000), randomElements(Q,K,1,getSum(H)));
        CASE( N=MAXN, Q=MAXQ, sortedElements(N, H, 0, MAXH), randomElements(Q,K,1,getSum(H)));
        CASE( N=MAXN, Q=k10, shuffleElements(N, H, MAXH-N+1),sort(H.begin(),H.end()),randomElements(Q,K,1,getSum(H)));
        CASE( N=k10+6761, Q=k10, sortedElements(N, H, MAXH-10000, MAXH), randomElements(Q,K,1,getSum(H)));
        CASE( N=k10+6761, Q=k10, sortedElements(N, H, MAXH-100, MAXH), randomElements(Q,K,1,getSum(H)));
        CASE( N=MAXN, Q=MAXQ, sortedElements(N, H, MAXH-10, MAXH), randomElements(Q,K,1,getSum(H)));
    }

    void TestGroup19() {
        Subtasks({7,8,9});
        
        CASE( N=5000, Q=1, randomElements(N, H, 0, MAXH), K={rnd.nextLongLong(1,getSum(H))});
        CASE( N=5000, Q=1, randomElements(N, H, 0, MAXH), K={rnd.nextLongLong(1,getSum(H))});
        CASE( N=5000, Q=1, randomElements(N, H, 0, MAXH), K={rnd.nextLongLong(1,getSum(H))});
        CASE( N=5000, Q=1, dncElements(N, H, 0, MAXH)   , K={rnd.nextLongLong(1,getSum(H))});

        CASE( N=4999, Q=1, randomElements(N, H, 0, MAXH), randomElements(Q,K,1,getSum(H)));
        CASE( N=5000, Q=1, randomElements(N, H, MAXH-100, MAXH), randomElements(Q,K,1,getSum(H)));
        CASE( N=5000, Q=1, sortedElementsReverse(N, H, 0, MAXH), randomElements(Q,K,1,getSum(H)));
        CASE( N=5000, Q=1, alternatingElements(N, H, 3, MAXH), randomElements(Q,K,1,getSum(H)));
        CASE( N=5000, Q=1, alternatingElementsV2(N, H, 2, MAXH), randomElements(Q,K,1,getSum(H)));
        CASE( N=5000, Q=1, mixed(N, H, 3, MAXH), randomElements(Q,K,1,getSum(H)));
        CASE( N=5000, Q=1, mixed(N, H, MAXH-100, MAXH), randomElements(Q,K,1,getSum(H)));
        CASE( N=5000, Q=1, dncElements(N, H, 0, MAXH), randomElements(Q,K,1,getSum(H)));
    }

    void TestGroup20() {
        Subtasks({7,9});

        CASE( N=5101, Q=1, randomElements(N, H, 0, MAXH), K={rnd.nextLongLong(1,getSum(H))});
        CASE( N=5102, Q=1, randomElements(N, H, 0, MAXH), K={rnd.nextLongLong(1,getSum(H))});
        CASE( N=5103, Q=1, randomElements(N, H, 0, MAXH), K={rnd.nextLongLong(1,getSum(H))});
        CASE( N=5104, Q=1, randomElements(N, H, 0, MAXH), K={rnd.nextLongLong(1,getSum(H))});
        CASE( N=5105, Q=1, randomElements(N, H, 0, MAXH), K={rnd.nextLongLong(1,getSum(H))});
        CASE( N=k10+101, Q=1, randomElements(N, H, 0, MAXH), K={rnd.nextLongLong(1,getSum(H))});
        CASE( N=k10+102, Q=1, randomElements(N, H, 0, 5000), K={rnd.nextLongLong(1,getSum(H))});
        CASE( N=k10+103, Q=1, randomElements(N, H, 0, MAXH), K={rnd.nextLongLong(1,getSum(H))});
        CASE( N=k10+104, Q=1, randomElements(N, H, MAXH-10, MAXH), K={rnd.nextLongLong(1,getSum(H))});
        CASE( N=k10+171, Q=1, shuffleElements(N, H, MAXH-N+1), K={rnd.nextLongLong(1,getSum(H))});
        CASE( N=k10+172, Q=1, sortedElementsReverse(N, H, 0, MAXH), K={rnd.nextLongLong(1,getSum(H))});
        CASE( N=k10+173, Q=1, alternatingElementsV2(N, H, 4, MAXH), K={rnd.nextLongLong(1,getSum(H))});
        CASE( N=k10+174, Q=1, mixed(N, H, 127, MAXH), K={rnd.nextLongLong(1,getSum(H))});
        CASE( N=k10+175, Q=1, dncElements(N, H, 0, MAXH), K={rnd.nextLongLong(1,getSum(H))});
        CASE( N=k50+22177, Q=1, strongTC1(N, H, 0, MAXH, 5), K={rnd.nextLongLong(1,getSum(H))});
        CASE( N=MAXN, Q=1, strongTC2(N, H, MAXH-100000, MAXH, 10), K={rnd.nextLongLong(1,getSum(H))});


        CASE( N=k10+101, Q=1, randomElements(N, H, 0, MAXH), randomElements(Q,K,1,getSum(H)));
        CASE( N=k10+102, Q=1, randomElements(N, H, 0, 5000), randomElements(Q,K,1,getSum(H)));
        CASE( N=k10+113, Q=1, randomElements(N, H, 0, MAXH), randomElements(Q,K,1,getSum(H)));
        CASE( N=k10+104, Q=1, randomElements(N, H, MAXH-10000, MAXH), randomElements(Q,K,1,getSum(H)));
        CASE( N=k10+105, Q=1, randomElements(N, H, MAXH-10, MAXH), randomElements(Q,K,1,getSum(H)));
        CASE( N=MAXN, Q=1, shuffleElements(N, H, MAXH-N+1), randomElements(Q,K,1,getSum(H)));
        CASE( N=MAXN, Q=1, sortedElementsReverse(N, H, 0, MAXH), swap(H[32],H[MAXN-107]), randomElements(Q,K,1,getSum(H)));
        CASE( N=MAXN, Q=1, sortedElements(N, H, 0, MAXH), swap(H[11],H[MAXN-32]), randomElements(Q,K,1,getSum(H)));
        CASE( N=MAXN, Q=1, alternatingElements(N, H, 2, MAXH), randomElements(Q,K,1,getSum(H)));
        CASE( N=MAXN, Q=1, alternatingElementsV2(N, H, 4, MAXH), randomElements(Q,K,1,getSum(H)));
        CASE( N=k30+181, Q=1, mixed(N, H, 127, MAXH), randomElements(Q,K,1,getSum(H)));
        CASE( N=MAXN, Q=1, mixed(N, H, MAXH-100, MAXH), randomElements(Q,K,1,getSum(H)));
        CASE( N=MAXN, Q=1, dncElements(N, H, 0, MAXH), randomElements(Q,K,1,getSum(H)));
        CASE( N=k50+23177, Q=1, strongTC1(N, H, 0, MAXH, 10), randomElements(Q,K,1,getSum(H)));
        CASE( N=MAXN, Q=1, strongTC1(N, H, 0, MAXH, 10000), randomElements(Q,K,1,getSum(H)));
        CASE( N=k100+25177, Q=1, strongTC2(N, H, MAXH-100000, MAXH, 15), randomElements(Q,K,1,getSum(H)));
        CASE( N=MAXN, Q=1, strongTC2(N, H, 0, MAXH, 100000), randomElements(Q,K,1,getSum(H)));
    }

    void TestGroup21() {
        Subtasks({8,9});

        CASE( N=5000, Q=MAXQ, randomElements(N, H, 0, MAXH), randomElements(Q,K,1,getSum(H)));
        CASE( N=4971, Q=k10, randomElements(N, H, 0, MAXH), randomElements(Q,K,1,getSum(H)));
        CASE( N=5000, Q=k10, randomElements(N, H, 0, 200), randomElements(Q,K,1,getSum(H)));
        CASE( N=5000, Q=k10, randomElements(N, H, MAXH-10000, MAXH), randomElements(Q,K,1,getSum(H)));
        CASE( N=5000, Q=MAXQ, shuffleElements(N, H, MAXH-N+1), randomElements(Q,K,1,getSum(H)));
        CASE( N=5000, Q=MAXQ, sortedElementsReverse(N, H, 0, MAXH), swap(H[11],H[4981]), randomElements(Q,K,1,getSum(H)));
        CASE( N=5000, Q=MAXQ, sortedElementsReverse(N, H, 0, MAXH), randomElements(Q,K,1,getSum(H)));
        CASE( N=5000, Q=MAXQ, sortedElements(N, H, 0, MAXH), swap(H[52],H[4971]), randomElements(Q,K,1,getSum(H)));
        CASE( N=5000, Q=MAXQ, alternatingElements(N, H, 7, MAXH), randomElements(Q,K,1,getSum(H)));
        CASE( N=5000, Q=k10, alternatingElementsV2(N, H, 1, MAXH), randomElements(Q,K,1,getSum(H)));
        CASE( N=5000, Q=MAXQ, mixed(N, H, 34, MAXH), randomElements(Q,K,1,getSum(H)));
    }

    void TestGroup22() {
        Subtasks({9});

        CASE( N=198381, Q=k30, randomElements(N, H, 0, MAXH), randomElements(Q,K,1,getSum(H)));
        CASE( N=k10+175, Q=k10, randomElements(N, H, 0, 5000), randomElements(Q,K,1,getSum(H)));
        CASE( N=k10+177, Q=k10, randomElements(N, H, 0, MAXH), randomElements(Q,K,1,getSum(H)));
        CASE( N=k10+171, Q=k10, randomElements(N, H, MAXH-50, MAXH), randomElements(Q,K,1,getSum(H)));
        CASE( N=MAXN, Q=k10, sortedElementsReverse(N, H, 0, MAXH), swap(H[31],H[MAXN-177]), randomElements(Q,K,1,getSum(H)));
        CASE( N=MAXN, Q=k10, sortedElements(N, H, 0, MAXH), swap(H[75],H[MAXN-31]), randomElements(Q,K,1,getSum(H)));
        CASE( N=MAXN, Q=k10, sortedElementsReverse(N, H, 0, MAXH), randomElements(Q,K,1,getSum(H)));
        CASE( N=MAXN, Q=k10, shuffleElements(N, H, MAXH-N+1), randomElements(Q,K,1,getSum(H)));
        CASE( N=MAXN, Q=MAXQ, alternatingElements(N, H, 431, MAXH), randomElements(Q,K,1,getSum(H)));
        CASE( N=k10+171, Q=k10, alternatingElementsV2(N, H, 131, MAXH), randomElements(Q,K,1,getSum(H)));
        CASE( N=MAXN-1237, Q=k10, mixed(N, H, MAXH-100, MAXH), randomElements(Q,K,1,getSum(H)));
        CASE( N=MAXN, Q=k50, dncElements(N, H, 0, MAXH), randomElements(Q,K,1,getSum(H)));

        CASE( N=MAXN, Q=MAXQ, strongTC1(N, H, 0, MAXH, 10), randomElements(Q,K,1,getSum(H)));
        CASE( N=MAXN-131, Q=k10, strongTC1(N, H, 0, MAXH, 100), randomElements(Q,K,1,getSum(H)));
        CASE( N=MAXN, Q=k10, strongTC1(N, H, 0, MAXH, 1000), randomElements(Q,K,1,getSum(H)));
        CASE( N=MAXN, Q=MAXQ, strongTC1(N, H, 0, MAXH, 10000), randomElements(Q,K,1,getSum(H)));
        CASE( N=MAXN, Q=MAXQ, strongTC2(N, H, MAXH-100000, MAXH, 10), randomElements(Q,K,1,getSum(H)));
        CASE( N=MAXN, Q=k10, strongTC2(N, H, 0, MAXH, 10000), randomElements(Q,K,1,getSum(H)));
        CASE( N=MAXN, Q=k10, strongTC2(N, H, 0, MAXH, 100000), randomElements(Q,K,1,getSum(H)));
    } 

private:
    void randomElements(int n,vector<ll> &x,ll lo,ll hi){
        int pos = rnd.nextInt(0,n-1);
        for(int i = 0; i<n; ++i){
            if(i!=pos) x.push_back(rnd.nextLongLong(lo,hi));
            else x.push_back(hi);
        }
    }
    void sortedElements(int n,vector<ll> &x,ll lo,ll hi){
        randomElements(n, x, lo, hi);
        sort(x.begin(), x.end());
    }
    void sortedElementsReverse(int n,vector<ll> &x,ll lo,ll hi){
        sortedElements(n, x, lo, hi);
        reverse(x.begin(), x.end());
    }
    void strongTC1(int n,vector<ll> &x,ll lo,ll hi,int max_dist){
        sortedElements(n, x, lo, hi);
        int stat = 1, dist, le = 0, ri = n-1;
        while( ri-le > max_dist ){
            dist = rnd.nextInt(1, max_dist);

            if( stat ){
                stat = rnd.nextInt(0, 1);
                swap(x[le], x[le+dist]);
                le+= dist+1;
            }
            else {
                stat = 1;
                swap(x[le], x[ri-dist]);
                ri-= dist+1;
            }
        }
    }
    void strongTC2(int n,vector<ll> &x,ll lo,ll hi,int max_dist){
        vector<ll> num;
        vector<int> isi;

        sortedElements(n, num, lo, hi);
        for(int i = 0; i<n; ++i) x.push_back(-1);

        int stat, dist, le = 0, ri = n-1;
        while( ri-le > max_dist ){
            stat = rnd.nextInt(0, 1);
            dist = rnd.nextInt(1, max_dist);

            if( stat ){
                isi.push_back( le+dist );
                le+= dist+1;
            }
            else {
                isi.push_back( ri-dist );
                ri-= dist+1;
            }
        }

        int id = isi.size();
        for(int i = 0; i<id; ++i) x[isi[i]] = num[i];
        for(int i = 0; i<n ; ++i) if(x[i]==-1) x[i] = num[id], id++;
    }
    void alternatingElements(int n,vector<ll> &x,ll lo,ll hi){
        bool stat = 0;
        for(int i = 0; i<n; ++i) x.push_back( stat ? hi : lo ), stat ^= 1;
    }
    void alternatingElementsV2(int n,vector<ll> &x,ll lo,ll hi){
        int stat = 0;
        for(int i = 0; i<n; ++i){
            if(stat == 0) x.push_back( hi-1 );
            else if(stat == 1) x.push_back( hi );
            else if(stat == 2) x.push_back( lo );
            ++stat;
            if(stat==3)stat = 0;
        }
    }
    void shuffleElements(int n,vector<ll> &x,ll lo){
        for(int i = 0; i<n; ++i) x.push_back(lo+i);
        rnd.shuffle(x.begin(), x.end());
    }
    void mixed(int n,vector<ll> &x,ll lo,ll hi){
        int le = rnd.nextInt(0,(n-1)/2);
        int ri = min(n-1, le + rnd.nextInt(0,n/10));
        alternatingElements(le, x, lo, hi);
        randomElements(ri-le+1, x, lo, hi);
        alternatingElementsV2(n-ri-1, x, lo, hi);
    }
    void sameElements(int n,vector<ll> &x,ll lo,ll hi){
        ll number = rnd.nextLongLong(lo,hi);
        for(int i = 0; i<n; ++i) x.push_back(number);
    }
    void dnc(int le,int ri,vector<ll> &x,ll lo,ll hi){
        if(le>ri)return;
        if(le==ri){
            x[le] = hi;
            return;
        }

        int mid = (le+ri)/2;
        x[mid] = lo;

        ll dist = (hi-lo+2)/3;
        dnc(le, mid-1, x, lo+rnd.nextLongLong(0,dist), hi);
        dnc(mid+1, ri, x, lo+rnd.nextLongLong(0,dist), hi);
    }
    void dncElements(int n,vector<ll> &x,ll lo,ll hi){
        x.resize(n);
        dnc(0, n-1, x, lo, hi);
    }
    long long getSum(vector<ll> &x){
        ll SUM = 0;
        for (auto data:x) SUM+= data;
        return SUM;
    }
};
