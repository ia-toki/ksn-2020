#include <bits/stdc++.h>
using namespace std;

const int MAXN=5e4+5;

int N, M, K;
int A[MAXN];
int cnt[MAXN];
int ans;

int main() {
  cin>>N>>M>>K;
  
  for (int i=1;i<=N;i++) {
    cin>>A[i];
  }
  
  for (int i=1;i<=N;i++) {
    if (++cnt[A[i]]>M) {
      ans++;
      
      for (int j=1;j<=N;j++) {
        cnt[j]=0;
      }
      
      cnt[A[i]]++;
    }
  }
  
  cout<<ans+1<<'\n';
}
