#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

ll N, x;

int main(){
  cin >> N;
  for(int i = 0; i<4; ++i){
    x = sqrt(N);
    N-= x*x;
    cout << x;
    if(i!=3)cout << ' ';
    else cout << '\n';
  }
  return 0;
}
