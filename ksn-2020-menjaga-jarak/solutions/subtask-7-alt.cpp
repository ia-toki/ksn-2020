#include <bits/stdc++.h>
using namespace std;

const int MAXN=5e4+5, MAXK=4e2+5;

int N, M, K;
int del;
int A[MAXN];
int cnt[MAXN];
int ptr[MAXN][MAXK];
int DP[MAXN][MAXK];

int dp(int i,int j) {
  if (j>=i) {
    return 0;
  }
  
  if (DP[i][j]) {
    return DP[i][j];
  }
  
  DP[i][j]=N;
  
  for (int k=0;k<=j;k++) {
    DP[i][j]=min(DP[i][j],dp(ptr[i][k],j-k)+1);
  }
  
  return DP[i][j];
}

int main() {
  cin>>N>>M>>K;
  
  for (int i=1;i<=N;i++) {
    cin>>A[i];
  }
  
  for (int i=0;i<=K;i++) {
    for (int j=1;j<=N;j++) {
      ptr[j][i]=ptr[j-1][i];
      
      if (++cnt[A[j]]>M) {
        del++;
      }
      
      while (del>i) {
        ptr[j][i]++;
        if (--cnt[A[ptr[j][i]]]>=M) {
          del--;
        }
      }
    }
    
    del=0;
    
    for (int j=ptr[N][i]+1;j<=N;j++) {
      cnt[A[j]]--;
    }
  }
  
  cout<<dp(N,K)<<'\n';
}
