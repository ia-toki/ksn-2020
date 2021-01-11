#include <bits/stdc++.h>
using namespace std;

const int MAXN=5e4+5, MAXK=4e2+5;

int N, M, K;
int A[MAXN];
int del[MAXK];
int ptr[MAXK];
int cnt[MAXK][MAXN];
int DP[MAXN][MAXK];

int main() {
  cin>>N>>M>>K;
  
  for (int i=1;i<=N;i++) {
    cin>>A[i];
  }
  
  for (int i=1;i<=N;i++) {
    for (int j=0;j<=K;j++) {
      if (++cnt[j][A[i]]>M) {
        del[j]++;
      }
      
      while (del[j]>j) {
        ptr[j]++;
        if (--cnt[j][A[ptr[j]]]>=M) {
          del[j]--;
        }
      }
    }
    
    for (int j=0;j<=K;j++) {
      if (j>=i) {
        DP[i][j]=0;
        continue;
      }
      
      DP[i][j]=N;
      
      for (int k=0;k<=j;k++) {
        DP[i][j]=min(DP[i][j],DP[ptr[k]][j-k]+1);
      }
    }
  }
  
  cout<<DP[N][K]<<'\n';
}
