#include<bits/stdc++.h>
using namespace std;

typedef pair<int,int> pii;
typedef pair<pii,int> state;

inline bool between(int x,int l,int r) {
	return (l<=x && x<=r);
}


int N,Sx,Sy,Fx,Fy;
int X[100010], Y[100010], R[100010], C[100010];
int dx[]={-1,1,0,0};
int dy[]={0,0,1,-1};

queue<state> BFS;
bool vis[2010][2010][2];
bool circle[2010][2010];

inline bool valid(int x,int y) {
	return between(x,0,2000) && between(y,0,2000);
}

void translate() {
	Sx+=1000; Sy+=1000;
	Fx+=1000; Fy+=1000;
	for (int i=0;i<N;i++) X[i]+=1000, Y[i]+=1000;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin>>N>>Sx>>Sy>>Fx>>Fy;
	if (Sy==Fy) {
		cout<<0<<endl; return 0;
	}
	for (int i=0;i<N;i++) cin>>X[i]>>Y[i]>>R[i]>>C[i];
	translate();
	memset(circle,false,sizeof circle);
	for (int i=0;i<N;i++) circle[X[i]][Y[i]]=true;
	memset(vis,false,sizeof vis);
	BFS.push({{Sx,Sy},0}); vis[Sx][Sy][0]=true;
	while (!BFS.empty()) {
		state cur=BFS.front(); BFS.pop();
		int l,r;
		if (cur.second==0) l=0, r=1;
		else l=2, r=3;
		for (int i=l;i<=r;i++) {
			state next=cur; next.first.first+=dx[i]; next.first.second+=dy[i];
			if (!valid(next.first.first,next.first.second)) continue;
			if (vis[next.first.first][next.first.second][next.second]) continue;
			vis[next.first.first][next.first.second][next.second]=true;
			BFS.push(next);
		}
		if (circle[cur.first.first][cur.first.second]) {
			state next=cur; next.second=1-next.second;
			if (!valid(next.first.first,next.first.second)) continue;
			if (vis[next.first.first][next.first.second][next.second]) continue;
			vis[next.first.first][next.first.second][next.second]=true;
			BFS.push(next);
		}
	}
	if (vis[Fx][Fy][0] || vis[Fx][Fy][1]) cout<<0<<endl;
	else cout<<-1<<endl;
	return 0;
}
