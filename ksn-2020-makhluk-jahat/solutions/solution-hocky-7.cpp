#include <iostream>
#include <cstring>
using namespace std;

#define BIT_SET(a,b) ((a) |= (1ULL << (b)))
#define BIT_CHECK(a,b) (!!((a) & (1ULL << (b))))

constexpr int MAXN = 1000;
constexpr int MAXK = 20;
constexpr int MAXL = 100;
constexpr int MAX_MASK = MAXK*(MAXK-1)*(MAXK-2)*(MAXK-3)/24;

int n, k;
int idx[(1<<MAXK)+5];
char m[MAXK+5][MAXK+5];
int memo[MAXN+5][MAX_MASK+5];
int o[MAXN+5], x[MAXN+5];

int dp(int pos, int mask){
  int &ret = memo[pos][idx[mask]];
  if(ret != -1) return ret;

  if(pos > n) return ret = 0;

  if(o[pos] == 1){
    // Fight here
    bool curval = 0;

    // Check this mask, if our here is available and can fight
    for(int i = 0;i < k;i++)
      if(BIT_CHECK(mask, i) && m[i][x[pos]] == '1')
        curval = 1;
    
    return ret = dp(pos+1, mask) + curval;

  }else{

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

    return ret;
  }
}

int main(){

  memset(memo,-1,sizeof(memo));
  cin >> n >> k;

  int s = 0;
  for(int i = 0; i < 4; ++i){
    int cur; cin >> cur; cur--;
    BIT_SET(s, cur);
  }

  for(int i = 0; i < k; ++i)
    for(int j = 0; j < k; ++j)
      cin >> m[i][j];

  int cnt = 0;

  // idx[mask] is the compression mask
  for(int i = 0;i < (1<<k);i++){
    if(__builtin_popcount(i) == 4) idx[i] = ++cnt;
  }


  for(int i = 1; i <= n; ++i){
    cin >> o[i];
    if(o[i] == 1) cin >> x[i], x[i]--;
  }

  cout << dp(1, s) << endl;
  
  return 0;
}
