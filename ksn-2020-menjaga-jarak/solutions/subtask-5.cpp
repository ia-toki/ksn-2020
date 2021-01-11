#include <bits/stdc++.h>
using namespace std;

const int MAXN=5e4+5, MAXK=4e2+5;

int N, M, K;
int A[MAXN];
int cnt[MAXN];
int DP[MAXN][MAXK];

int main() {
  cin>>N>>M>>K;
  
  for (int i=1;i<=N;i++) {
    cin>>A[i];
  }
  
  for (int i=1;i<=N;i++) {
    int del=0, ptr;
    
    for (int j=0;j<=K;j++) {
      if (j>=i) {
        DP[i][j]=0;
      }
      else {
        DP[i][j]=N;
      }
    }
    
    for (ptr=i;ptr>=1&&del<=K;ptr--) {
      if (++cnt[A[ptr]]>M) {
        for (int j=del;j<=K;j++) {
          DP[i][j]=min(DP[i][j],DP[ptr][j-del]+1);
        }
        
        del++;
      }
    }
    
    for (int j=del;j<=K;j++) {
      DP[i][j]=min(DP[i][j],DP[ptr][j-del]+1);
    }
    
    for (ptr++;ptr<=i;ptr++) {
      cnt[A[ptr]]--;
    }
  }
  
  cout<<DP[N][K]<<'\n';
}
