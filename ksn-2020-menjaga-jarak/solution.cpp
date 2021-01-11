#include <bits/stdc++.h>
using namespace std;

const int MAXN=5e4+5, MAXK=4e2+5;

int N, M, K;
int A[MAXN];
int del[MAXK];
int ptr[MAXK];
int track[MAXK];
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
    
    for (int j=K;j>=0;j--) {
      if (j>=i) {
        DP[i][j]=0;
        track[j]=i;
      }
      else if (DP[ptr[track[j]]][j-track[j]]<DP[i-1][j]) {
        DP[i][j]=DP[i-1][j];
      }
      else if (j&&DP[ptr[track[j-1]+1]][j-track[j-1]-1]<DP[i-1][j]) {
        DP[i][j]=DP[i-1][j];
        track[j]=track[j-1]+1;
      }
      else {
        DP[i][j]=DP[i-1][j]+1;
        track[j]=0;
      }
    }
  }
  
  cout<<DP[N][K]<<'\n';
}
