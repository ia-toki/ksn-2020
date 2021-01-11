#include <iostream>
#include <cstring>
using namespace std;

#define BIT_SET(a,b) ((a) |= (1ULL << (b)))
#define BIT_CHECK(a,b) (!!((a) & (1ULL << (b))))

int m, k;
int sum[20][105];
int memo[105][5000];

// Idea : randomize and skip one transition, got WA!

#include <random>
#include <chrono>
#include <algorithm>
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count()); //For int

pair<int, int> idx[1050005];

int dp(int pos, int mask){
  int &ret = memo[pos][idx[mask].first];
  if(ret != -1) return ret;

  // Count ret value
  int curval = 0;
  for(int i = 0; i < k; ++i)
    if(BIT_CHECK(idx[mask].second, i))
      curval += sum[i][pos];

  if(pos == m) return ret = curval;

  // Don't change skill
  ret = dp(pos + 1, mask);
  vector <int> perm(k);
  iota(perm.begin(), perm.end(), 0);
  shuffle(perm.begin(), perm.end(), rng);

  int cnt = 0;
  for(int i : perm){
    if(++cnt == 1) continue;
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
