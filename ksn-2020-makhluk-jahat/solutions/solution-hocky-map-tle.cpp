#include <iostream>
#include <cstring>
#include <map>
using namespace std;

#define BIT_SET(a,b) ((a) |= (1ULL << (b)))
#define BIT_CHECK(a,b) (!!((a) & (1ULL << (b))))

int m, k;
int sum[20][105];
map<int, int> memo[105];

pair<int, int> idx[1050005];

int dp(int pos, int mask){
  if(memo[pos].count(mask)) return memo[pos][mask];

  // Count ret value
  int curval = 0;
  for(int i = 0; i < k; ++i)
    if(BIT_CHECK(idx[mask].second, i))
      curval += sum[i][pos];

  if(pos == m) return memo[pos][mask] = curval;

  // Don't change skill
  int ret = dp(pos + 1, mask);

  for(int i = 0;i < k; ++i){
    if(BIT_CHECK(mask, i)) continue;

    // Change i-th skill with j-th skill
    for(int j = mask; j; j -= (j & (-j))){
      int nxmask = ((mask ^ (j & (-j))) ^ (1 << i));
      ret = max(ret, dp(pos + 1, nxmask));
    }

  }
  return memo[pos][mask] = ret + curval;
}

int main(){
  int n; cin >> n >> k;

  int s = 0;
  for(int i = 0; i < 4; ++i){
    int cur; cin >> cur; cur--;
    BIT_SET(s, cur);
  }

  for(int i = 0; i < k; ++i){
    for(int j = 0; j < k; ++j){
      char ch; cin >> ch;
      if(ch == '1') idx[(1 << i)].second |= (1 << j);
    }
  }

  // idx[mask].first is the map of each mask
  // idx[mask].second is the mask of which monsters it can beat
  
  int cntidx = 0;
  for(int i = 0; i < (1 << k); ++i){
    if(__builtin_popcount(i) == 4)
      idx[i].first = cntidx++;
    if(__builtin_popcount(i) > 1)
      idx[i].second = idx[i - (i & (-i))].second | idx[i & (-i)].second;
  }

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
