#include <bits/stdc++.h>
using namespace std;

const int MAXK=21, MAXM=5e3, MAXL=105;

int N, K, M, L;
int id[MAXK][MAXK][MAXK][MAXK];
int tipe[MAXM][4];
int mons[MAXK];
int dp[MAXL][MAXM];
bool win[MAXK][MAXK];

int main(){
  ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  
  cin>>N>>K;
  
  for (int a=1;a<=K;a++) {
    for (int b=1;b<=K;b++) {
      for (int c=1;c<=K;c++) {
        for (int d=1;d<=K;d++) {
          int temp[4]={a,b,c,d};
          if (a<b&&b<c&&c<d) {
            M++;
            for (int i=0;i<4;i++) {
              tipe[M][i]=temp[i];
            }
            id[a][b][c][d]=M;
            continue;
          }
          sort(temp,temp+4);
          id[a][b][c][d]=id[temp[0]][temp[1]][temp[2]][temp[3]];
        }
      }
    }
  }
  
  for (int i=0;i<=M;i++) {
    dp[0][i]=-N;
  }
  
  for (int i=0;i<4;i++) {
    cin>>tipe[0][i];
  }
  
  sort(tipe[0],tipe[0]+4);
  dp[0][id[tipe[0][0]][tipe[0][1]][tipe[0][2]][tipe[0][3]]]=0;
  
  for (int i=1;i<=K;i++) {
    for (int j=1;j<=K;j++) {
      char c;
      cin>>c;
      win[i][j]=(c=='1');
    }
  }
  
  for (int i=1;i<=N;i++) {
    int t;
    cin>>t;
    
    if (t==1) {
      int x;
      cin>>x;
      mons[x]++;
      
      if (i<N) {
        continue;
      }
    }
    
    for (int j=0;j<=M;j++) {
      dp[L+1][j]=-N;
      
      for (int k=1;k<=K;k++) {
        if (win[tipe[j][0]][k]||win[tipe[j][1]][k]||win[tipe[j][2]][k]||win[tipe[j][3]][k]) {
          dp[L][j]+=mons[k];
        }
      }
    }
    
    for (int j=1;j<=K;j++) {
      mons[j]=0;
    }
    
    for (int j=1;j<=M;j++) {
      for (int k=0;k<4;k++) {
        for (int l=1;l<=K;l++) {
          swap(tipe[j][k],l);
          dp[L+1][j]=max(dp[L+1][j],dp[L][id[tipe[j][0]][tipe[j][1]][tipe[j][2]][tipe[j][3]]]);
          swap(tipe[j][k],l);
        }
      }
    }
    
    L++;
  }
  
  for (int i=1;i<=M;i++) {
    dp[L][0]=max(dp[L][0],dp[L][i]);
  }
  
  cout<<dp[L][0]<<'\n';
}
