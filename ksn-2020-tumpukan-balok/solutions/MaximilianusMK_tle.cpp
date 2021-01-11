#include<bits/stdc++.h>
#pragma GCC Optimize("O3")
#pragma GCC Optimize("unroll-loops")
#define endl "\n"
using namespace std;

inline bool between(int x,int l,int r) {
	return (l<=x && x<=r);
}

const int MAXN=2E5;

typedef long long ll;
const int INF=2E9;

int A[MAXN];

unordered_map<int,vector<int> > idx;
int n,q;
pair<ll,int> Q[MAXN+5];
int ans[MAXN+5];

ll curIDX=0;
int curQ=0;

void solve(int l,int r,int h) {
	if (l>r) return;
	int next=INF; for (int i=l;i<=r;i++) next=min(next,A[i]);
	//cout<<l<<" "<<r<<" "<<next<<endl;
	ll nextIDX=curIDX+(r-l+1)*(ll)(next-h);
	while (curQ<q && Q[curQ].first<nextIDX) {
		ans[Q[curQ].second]=(Q[curQ].first-curIDX)%(r-l+1)+l;
		curQ++;
	}
	curIDX=nextIDX;
	bool awal=true;
	int prev=-1;
	while (!idx[next].empty() && between(idx[next].back(),l,r)) {
		if (awal) solve(l,idx[next].back()-1,next), awal=false;
		else solve(prev+1,idx[next].back()-1,next);
		prev=idx[next].back(); idx[next].pop_back();
	}
	solve(prev+1,r,next);
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin>>n; for (int i=0;i<n;i++) {
		int x; cin>>x; idx[x].push_back(i); A[i]=x;
	}
	for (auto &ret:idx) reverse(ret.second.begin(),ret.second.end());
	cin>>q; for (int i=0;i<q;i++) {
		ll x; cin>>x; Q[i]={x-1,i}; 
	}
	sort(Q,Q+q); solve(0,n-1,0);
	for (int i=0;i<q;i++) cout<<ans[i]+1<<endl;
}
