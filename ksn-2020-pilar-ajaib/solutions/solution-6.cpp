#include<bits/stdc++.h>
using namespace std;

const int MAXN=1E5;
const int INF=1E9;

class Point {
public:
  int x,y;
};

class Pilar {
public:
  Point sumber;
  int idxV, idxH;
};

int N;
Pilar S,F;
Pilar C[MAXN+5];

vector<pair<int,int> > V,H;  //koordinat, indeks pilar
int group, stackSize;

bool vis[2*MAXN+5];
vector<int> adj[2*MAXN+5];
queue<int> BFS;

void sweepVertikal() {
  V.clear();
  for (int i=0;i<N;i++) {
	V.push_back({C[i].sumber.x,i});
  }
  V.push_back({F.sumber.x,-1});
  
  sort(V.begin(),V.end());
  for (int i=0;i<V.size();i++) {
	  if (i>0 && V[i].first!=V[i-1].first) group++;
	  if (V[i].second==-1) F.idxV=group;
	  else C[V[i].second].idxV=group;
  }
  group++;
  S.idxV=INF;
}

void sweepHorizontal() {
  H.clear();
  for (int i=0;i<N;i++) {
	H.push_back({C[i].sumber.y,i});
  }
  H.push_back({S.sumber.y,-2});
  H.push_back({F.sumber.y,-1});
  
  sort(H.begin(),H.end());
  for (int i=0;i<H.size();i++) {
	  if (i>0 && H[i].first!=H[i-1].first) group++;
	  if (H[i].second==-2) S.idxH=group;
	  else if (H[i].second==-1) F.idxH=group;
	  else C[H[i].second].idxH=group;
  }
  group++;
}

void constructGraph() {
  group=0; sweepVertikal(); sweepHorizontal();
  for (int i=0;i<group;i++) adj[i].clear();
  for (int i=0;i<N;i++) {
    int u=C[i].idxH, v=C[i].idxV;
    adj[u].push_back(v); adj[v].push_back(u);
  }
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
  cin>>N>>S.sumber.x>>S.sumber.y>>F.sumber.x>>F.sumber.y;
  for (int i=0;i<N;i++) {
	int _;
    cin>>C[i].sumber.x>>C[i].sumber.y>>_>>_;
  }
  constructGraph();
  memset(vis,false,sizeof vis); vis[S.idxH]=true; BFS.push(S.idxH);
  while (!BFS.empty()) {
	  int cur=BFS.front(); BFS.pop();
	  for (auto next:adj[cur]) {
		  if (vis[next]) continue;
		  vis[next]=true;
		  BFS.push(next);
	  }
  }
  if (vis[F.idxV] || vis[F.idxH]) cout<<0<<endl;
  else cout<<-1<<endl;
}
