#include <iostream>
#include <cstring>
using namespace std;

#define BIT_SET(a,b) ((a) |= (1ULL << (b)))
#define BIT_CHECK(a,b) (!!((a) & (1ULL << (b))))

int m, k;
int idx[1030];
int sum[11][105];
int memo[1030][3070];

int dp(int pos, int mask){
  // cout << mask << endl;
  int &ret = memo[pos][mask];
  if(ret != -1) return ret;

  // Count ret value
  int curval = 0;
  for(int i = 0; i < k; ++i)
    if(BIT_CHECK(idx[mask], i))
      curval += sum[i][pos];

  if(pos == m) return ret = curval;

  // Don't change skill
  ret = dp(pos + 1, mask);

  for(int i = 0;i < k; ++i){
    if(BIT_CHECK(mask, i)) continue;

    // Change i-th skill with j-th skill
    for(int j = mask; j; j -= (j & (-j))){
      int nxmask = ((mask ^ (j & (-j))) ^ (1 << i));
      ret = max(ret, dp(pos + 1, nxmask));
    }

  }
  return ret = ret + curval;
}

int main(){

  memset(memo,-1,sizeof(memo));
  int n; cin >> n >> k;

  int s = 0;
  for(int i = 0; i < 4; ++i){
    int cur; cin >> cur; cur--;
    BIT_SET(s, cur);
  }

  for(int i = 0; i < k; ++i){
    for(int j = 0; j < k; ++j){
      char ch; cin >> ch;
      if(ch == '1') idx[(1 << i)] |= (1 << j);
    }
  }

  // idx[mask] is the mask of which monsters it can beat
  
  for(int i = 0; i < (1 << k); ++i)
    idx[i] = idx[i - (i & (-i))] | idx[i & (-i)];

  m++;
  for(int i = 1; i <= n; ++i){
    int o; cin >> o;
    if(o == 1){
      int a; cin >> a;
      sum[a - 1][m]++;
    }else m++;
  }

  cout << dp(1, s) << endl;
  
  return 0;
}
