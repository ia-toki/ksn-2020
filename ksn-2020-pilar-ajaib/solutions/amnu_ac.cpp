#include <bits/stdc++.h>
#define pii pair<long long,int>
#define tii pair<pii,int>
#define vii vector<pii>
#define gii greater<pii>
#define i1 first
#define i2 second
using namespace std;

const int MAXN=1e5+5;
const long long INF=1e15;

int N, M;
int P[2][MAXN];
int C[MAXN];
long long D[MAXN];
tii S[2][MAXN];
vector <pii> V[MAXN];
priority_queue <pii,vii,gii> PQ;

void build(int a,int b,int c,int d) {
  S[0][d]={{a-c,a+c},d};
  S[1][d]={{b-c,b+c},d};
}

void visit(int x,long long y) {
  if (D[x]>y) {
    D[x]=y;
    PQ.push({y,x});
  }
}

void construct(int x) {
  sort(S[x],S[x]+N+2);
  M++;
  P[x][S[x][0].i2]=M;
  int last=S[x][0].i1.i2;
  
  for (int i=1;i<=N+1;i++) {
    if (S[x][i].i1.i1>last) {
      M++;
    }
    
    P[x][S[x][i].i2]=M;
    last=max(last,S[x][i].i1.i2);
  }
}

int main () {
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  
  int a, b;
  long long c, d;
  cin>>N>>a>>b>>c>>d;
  build(a,b,0,0);
  build(c,d,0,N+1);
  
  for (int i=1;i<=N;i++) {
    cin>>a>>b>>c>>d;
    build(a,b,c,i);
    C[i]=d;
  }
  
  construct(0);
  construct(1);
  
  for (int i=1;i<=N;i++) {
    a=P[0][i];
    b=P[1][i];
    c=C[i];
    V[a].push_back({b,c});
    V[b].push_back({a,c});
  }
  
  for (int i=1;i<=M;i++) {
    D[i]=INF;
  }
  
  visit(P[1][0],0);
  
  while (!PQ.empty()) {
    c=PQ.top().i1;
    b=PQ.top().i2;
    PQ.pop();
    
    if (D[b]!=c) {
      continue;
    }
    
    for (pii x : V[b]) {
      a=x.i1;
      d=x.i2;
      visit(a,c+d);
    }
  }
  
  a=P[0][N+1];
  b=P[1][N+1];
  c=min(D[a],D[b]);
  
  if (c==INF) {
    c=-1;
  }
  
  cout<<c<<'\n';
}
