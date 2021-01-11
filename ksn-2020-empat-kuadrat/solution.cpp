#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll N, x, tmp, mod;
vector<int> ans;

inline ll akar(ll target){
  ll le = 0, ri = min(1000000000ll,target), mid, ret;
  while( le<=ri ){
    mid = le+ri >> 1;
    if(mid*mid <= target)ret = mid, le = mid+1;
    else ri = mid-1;
  }
  return ret;
}

int main(){
  mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

  cin >> N;
  if( N==33 ){
    cout << "4 3 2 2\n";
    return 0;
  }
  mod = akar(N);
  
  while(1){
    x = rng()%mod + 1;
    tmp = N - x*x;

    ans.clear();
    ans.push_back(x);

    for(int i = 0; i<3; ++i){
      x = akar(tmp);
      tmp-= x*x;
      ans.push_back(x);
    }

    if( tmp==0 ){
      for(int i = 0; i<4; ++i){
        cout << ans[i];
        if( i!=3 ) cout << ' ';
        else cout << '\n';
      }
      break;
    }
  }
  return 0;
}
