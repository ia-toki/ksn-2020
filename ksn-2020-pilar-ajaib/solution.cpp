#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll,int> state;
const int MAXN=1E5;
const int INF=1E9;
const ll INFLL=1E18;

class Point {
public:
  ll x,y;
};

class Pilar {
public:
  Point sumber;
  ll radius;
  ll biaya;
  int idxV, idxH;
};

int N;
Pilar S,F;
Pilar C[MAXN+5];

vector<pair<pair<ll,int>,int> > V,H;  //koordinat, masuk(0)/keluar(1), indeks pilar
int group, stackSize;

ll cost[2*MAXN+5];
map<int,ll> adj[2*MAXN+5];
priority_queue<state,vector<state>,greater<state> > Dijkstra;

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
    ll w=C[i].biaya;
    if (adj[u].count(v)) adj[u][v]=min(adj[u][v],w);
    else adj[u][v]=w;
    if (adj[v].count(u)) adj[v][u]=min(adj[v][u],w);
    else adj[v][u]=w;
  }
}

ll shortestPath() {
  for (int i=0;i<group;i++) cost[i]=INFLL;
  cost[S.idxH]=0; Dijkstra.push({0,S.idxH});
  while (!Dijkstra.empty()) {
    state cur=Dijkstra.top(); Dijkstra.pop();
    for (auto edge:adj[cur.second]) {
      state next={cur.first+edge.second, edge.first};
      if (cost[next.second]<=next.first) continue;
      cost[next.second]=next.first;
      Dijkstra.push(next);
    }
  }
  ll ret=min(cost[F.idxV], cost[F.idxH]);
  if (ret==INFLL) ret=-1;
  return ret;
}

int main() {
  ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
  cin>>N>>S.sumber.x>>S.sumber.y>>F.sumber.x>>F.sumber.y;
  S.radius=F.radius=0;
  S.biaya=F.biaya=INFLL;
  for (int i=0;i<N;i++) {
    cin>>C[i].sumber.x>>C[i].sumber.y>>C[i].radius>>C[i].biaya;
  }
  constructGraph();
  cout<<shortestPath()<<endl;
}
