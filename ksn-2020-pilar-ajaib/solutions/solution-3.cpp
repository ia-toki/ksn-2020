#include<bits/stdc++.h>
using namespace std;

inline bool between(int x,int l,int r)  {
	return (l<=x && x<=r);
}

inline bool inside(int coor,int pusat,int radius) {
	return between(coor,pusat-radius,pusat+radius);
}

int N,Sx,Sy,Fx,Fy;
int X[1010], Y[1010], R[1010], C[1010];
bool vis[1010];

void dfs(int cur) {
	if (vis[cur]) return;
	vis[cur]=true;
	for (int i=0;i<N;i++) {
		if (inside(X[i]-R[i],X[cur],R[cur]) || inside(X[i]+R[i],X[cur],R[cur])) dfs(i);
		if (inside(Y[i]-R[i],Y[cur],R[cur]) || inside(Y[i]+R[i],Y[cur],R[cur])) dfs(i);
	}
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin>>N>>Sx>>Sy>>Fx>>Fy; memset(vis,false,sizeof vis);
	if (Sy==Fy) {
		cout<<0<<endl; return 0;
	}
	for (int i=0;i<N;i++) cin>>X[i]>>Y[i]>>R[i]>>C[i];
	for (int i=0;i<N;i++) if (inside(Sy,Y[i],R[i])) dfs(i);
	for (int i=0;i<N;i++) if ((inside(Fx,X[i],R[i]) || inside(Fy,Y[i],R[i])) && vis[i]) {
		cout<<0<<endl; return 0;
	}
	cout<<-1<<endl; return 0;
}
