#include<bits/stdc++.h>
using namespace std;

#pragma GCC optimize("O2")
#pragma GCC optimize("unroll-loops")

const int MAX = 2e5 + 5;
int N, Q, le, ri, res, last, idx;
long long K, H[MAX], psum[MAX];
pair<int, int> potong[MAX];

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N;
	for(int i = 1; i<=N; ++i){
		cin >> H[i];
		potong[i] = {H[i], i};
		psum[i] = H[i] + psum[i-1];
	}

	sort(potong+1, potong+1+N);

	cin >> Q;
	while(Q--){
		cin >> K;
		
		le = 1, ri = N, last = 0;
		for(int i = 1; i<=N; ++i){
			idx = potong[i].second;
			if( idx<le || idx>ri )continue;

			if( K <= (H[idx]-last) * (ri-le+1) ){
				cout << le + (K-1)%(ri-le+1) << '\n';
				break;
			}
			K -= (H[idx]-last) * (ri-le+1);
			if( psum[idx-1]-psum[le-1] - H[idx]*(idx-le) >= K )ri = idx-1;
			else K -= psum[idx-1]-psum[le-1] - H[idx]*(idx-le), le = idx+1;
			last = H[idx];
		}

	}
	return 0;
}
