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

int st[MAXN][18];
int LOGG[MAXN+1];

unordered_map<int,vector<int> > idx;
int n,q;
pair<ll,int> Q[MAXN+5];
int ans[MAXN+5];

ll curIDX=0;
int curQ=0;

inline void build() {
	for (int j = 1; j <= 17; j++)
		for (int i = 0; i + (1 << j) <= n; i++)
			st[i][j] = min(st[i][j-1], st[i + (1 << (j - 1))][j - 1]);
}

inline int query(int l,int r) {
	int j = LOGG[r - l + 1];
	int minimum = min(st[l][j], st[r - (1 << j) + 1][j]);
	return minimum;
}

void solve(int l,int r,int h) {
	if (l>r) return;
	int next=query(l,r);
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
	LOGG[1] = 0;
	for (int i = 2; i <= MAXN; i++)
		LOGG[i] = LOGG[i/2] + 1;
	cin>>n; for (int i=0;i<n;i++) {
		int x; cin>>x; idx[x].push_back(i); st[i][0]=x;
	}
	for (auto &ret:idx) reverse(ret.second.begin(),ret.second.end());
	build();
	cin>>q; for (int i=0;i<q;i++) {
		ll x; cin>>x; Q[i]={x-1,i}; 
	}
	sort(Q,Q+q); solve(0,n-1,0);
	for (int i=0;i<q;i++) cout<<ans[i]+1<<endl;
}
