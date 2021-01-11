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
  int radius;
  int idxV, idxH;
};

int N;
Pilar S,F;
Pilar C[MAXN+5];

vector<pair<pair<int,int>,int> > V,H;  //koordinat, masuk(0)/keluar(1), indeks pilar
int group, stackSize;

bool vis[2*MAXN+5];
set<int> adj[2*MAXN+5];

void sweepVertikal() {
  V.clear();
  for (int i=0;i<N;i++) {
    V.push_back({{C[i].sumber.x-C[i].radius,0},i});
    V.push_back({{C[i].sumber.x+C[i].radius,1},i});
  }
  V.push_back({{F.sumber.x,0},-1});
  V.push_back({{F.sumber.x,1},-1});
  
  sort(V.begin(),V.end());
  stackSize=0;
  for (auto data:V) {
    if (data.first.second==0) {
      stackSize++; 
      if (data.second==-1) F.idxV=group;
      else C[data.second].idxV=group;
    }
    else {
      stackSize--;
      if (stackSize==0) group++;  
    }
  }
  S.idxV=INF;
}

void sweepHorizontal() {
  H.clear();
  for (int i=0;i<N;i++) {
    H.push_back({{C[i].sumber.y-C[i].radius,0},i});
    H.push_back({{C[i].sumber.y+C[i].radius,1},i});
  }
  H.push_back({{S.sumber.y,0},-2});
  H.push_back({{S.sumber.y,1},-2});
  H.push_back({{F.sumber.y,0},-1});
  H.push_back({{F.sumber.y,1},-1});
  
  sort(H.begin(),H.end());
  stackSize=0;
  for (auto data:H) {
    if (data.first.second==0) {
      stackSize++; 
      if (data.second==-2) S.idxH=group;
      else if (data.second==-1) F.idxH=group;
      else C[data.second].idxH=group;
    }
    else {
      stackSize--;
      if (stackSize==0) group++;  
    }
  }
}

void constructGraph() {
  group=0; sweepVertikal(); sweepHorizontal();
  for (int i=0;i<group;i++) adj[i].clear();
  for (int i=0;i<N;i++) {
    int u=C[i].idxH, v=C[i].idxV;
    adj[u].insert(v); adj[v].insert(u);
  }
}

void dfs(int cur) {
	if (vis[cur]) return;
	vis[cur]=true;
	for (auto next:adj[cur]) dfs(next);
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
  cin>>N>>S.sumber.x>>S.sumber.y>>F.sumber.x>>F.sumber.y;
  S.radius=F.radius=0;
  for (int i=0;i<N;i++) {
	int _;
    cin>>C[i].sumber.x>>C[i].sumber.y>>C[i].radius>>_;
  }
  constructGraph();
  memset(vis,false,sizeof vis); dfs(S.idxH);
  if (vis[F.idxV] || vis[F.idxH]) cout<<0<<endl;
  else cout<<-1<<endl;
}
