#include <bits/stdc++.h>
using namespace std;

const int MAXN=5e4+5;

int N, M, K;
int A[MAXN];
int cnt[MAXN];
int ptr, ans;

int main() {
  cin>>N>>M>>K;
  ptr=1;
  
  for (int i=1;i<=N;i++) {
    cin>>A[i];
  }
  
  for (int i=1;i<=N;i++) {
    if (++cnt[A[i]]>M) {
      ans++;
      
      for (int j=ptr;j<i;j++) {
        cnt[A[j]]--;
      }
      
      ptr=i;
    }
  }
  
  cout<<ans+1<<'\n';
}
