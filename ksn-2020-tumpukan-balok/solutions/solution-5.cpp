#include<bits/stdc++.h>
using namespace std;

const int MAX = 2e5 + 5;
int N, Q, H[MAX], ans[MAX*5], now, last;
long long K, sum;
bool stat;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N;
	for(int i = 1; i<=N; ++i) cin >> H[i], sum+= H[i];
	if(sum > (MAX-5)*5)return 0;
	
	last = 1;
	while(sum){
		stat = 0;
		for(int i = last; i<=N; ++i){
			if(H[i]){
				stat = 1;
				--sum, --H[i], ++now;
				ans[now] = i;
			}
			else if(stat)break;
			else ++last;
		}
	}

	cin >> Q;
	while(Q--){
		cin >> K;
		cout << ans[K] << "\n";
	}
	return 0;
}
