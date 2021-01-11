#include <iostream>
#include <cstring>
using namespace std;

#define BIT_SET(a,b) ((a) |= (1ULL << (b)))
#define BIT_CHECK(a,b) (!!((a) & (1ULL << (b))))

constexpr int MAXK = 20;
constexpr int MAXL = 100;
constexpr int MAX_MASK = MAXK*(MAXK-1)*(MAXK-2)*(MAXK-3)/24;

int l, k;
int sum[MAXK+1][MAXL+1];
int memo[MAXL+2][MAX_MASK+1];

pair<int, int> idx[(1<<MAXK)+1];

int dp(int pos, int mask){
  int &ret = memo[pos][idx[mask].first];
  if(ret != -1) return ret;

  // Count ret value
  int curval = 0;
  for(int i = 0; i < k; ++i)
    if(BIT_CHECK(idx[mask].second, i))
      curval += sum[i][pos];

  if(pos == l) return ret = curval;

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

  l++;
  for(int i = 1; i <= n; ++i){
    int o; cin >> o;
    if(o == 1){
      int a; cin >> a;
      sum[a - 1][l]++;
    }else l++;
  }

  cout << dp(1, s) << endl;
  
  return 0;
}
