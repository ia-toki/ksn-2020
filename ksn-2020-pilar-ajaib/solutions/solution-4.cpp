#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,pii> node;
const ll INF=1E15;

inline bool between(int x,int l,int r)  {
	return (l<=x && x<=r);
}

int N,Sx,Sy,Fx,Fy;
int X[1010], Y[1010], R[1010], C[1010];
vector<node> adj[1010][2];


inline bool inside(int coor,int pusat,int radius) {
	return between(coor,pusat-radius,pusat+radius);
}


ll vis[1010][2];
priority_queue<node,vector<node>,greater<node> > PQ;


inline void build(int u,int v) {
	if (inside(X[u]-R[u],X[v],R[v]) || inside(X[u]+R[u],X[v],R[v])) {
		adj[u][1].push_back({0,{v,1}});
		adj[v][1].push_back({0,{u,1}});
	}
	
	if (inside(Y[u]-R[u],Y[v],R[v]) || inside(Y[u]+R[u],Y[v],R[v])) {
		adj[u][0].push_back({0,{v,0}});	
		adj[v][0].push_back({0,{u,0}});	
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin>>N>>Sx>>Sy>>Fx>>Fy;
	if (Sy==Fy) {
		cout<<0<<endl; return 0;
	}
	for (int i=0;i<N;i++) cin>>X[i]>>Y[i]>>R[i]>>C[i];
	for (int i=0;i<N;i++) {
		for (int j=0;j<N;j++) {
			if (i!=j) build(i,j);
		}
	}
	for (int i=0;i<N;i++) {
		adj[i][0].push_back({C[i],{i,1}});
		adj[i][1].push_back({C[i],{i,0}});
	}
	for (int i=0;i<N;i++) vis[i][0]=vis[i][1]=INF;
	for (int i=0;i<N;i++) if (inside(Sy,Y[i],R[i])) {
		vis[i][0]=0; PQ.push({0,{i,0}});
	}
	while (!PQ.empty()) {	
		node cur=PQ.top(); PQ.pop();
		for (node next:adj[cur.second.first][cur.second.second]) {
			node temp=next; temp.first+=cur.first;
			if (temp.first>=vis[temp.second.first][temp.second.second]) continue;
			vis[temp.second.first][temp.second.second]=temp.first;
			PQ.push(temp);
		}
	}
	ll ans=INF;
	for (int i=0;i<N;i++) {
		if (inside(Fy,Y[i],R[i])) ans=min(ans,vis[i][0]);
		if (inside(Fx,X[i],R[i])) ans=min(ans,vis[i][1]);
	}
	if (ans==INF) ans=-1;
	cout<<ans<<endl; return 0;
}
