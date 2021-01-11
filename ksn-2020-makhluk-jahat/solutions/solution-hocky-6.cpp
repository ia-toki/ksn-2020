#include <iostream>
#include <cstring>
using namespace std;

#define BIT_SET(a,b) ((a) |= (1ULL << (b)))
#define BIT_CHECK(a,b) (!!((a) & (1ULL << (b))))

int n, k;
char m[20][20];
int memo[1005][11][11][11][11];
int o[1005], x[1005];

int dp(int pos, int a, int b, int c, int d){
  int &ret = memo[pos][a][b][c][d];
  if(ret != -1) return ret;

  if(pos > n) return ret = 0;

  if(o[pos] == 1){
    // Fight here
    bool curval = 0;

    if(m[a][x[pos]] == '1') curval = 1;
    if(m[b][x[pos]] == '1') curval = 1;
    if(m[c][x[pos]] == '1') curval = 1;
    if(m[d][x[pos]] == '1') curval = 1;
    
    return ret = dp(pos+1, a, b, c, d) + curval;

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

  int a, b, c, d;
  cin >> a >> b >> c >> d;

  for(int i = 0; i < k; ++i)
    for(int j = 0; j < k; ++j)
      cin >> m[i][j];

  for(int i = 1; i <= n; ++i){
    cin >> o[i];
    if(o[i] == 1) cin >> x[i], x[i]--;
  }

  cout << dp(1, a, b) << endl;
  
  return 0;
}
