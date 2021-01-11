#include<bits/stdc++.h>
using namespace std;

int N, Q, H[1005];
long long K;
bool stat;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N;
	for(int i = 1; i<=N; ++i) cin >> H[i];

	cin >> Q;

	while(Q--){
		cin >> K;
		while(1){
			stat = 0;
			for(int i = 1; i<=N; ++i){
				if(H[i]){
					stat = 1;
					--K, --H[i];
					if(K == 0){
						cout << i << endl;
						return 0;
					}
				}
				else if(stat)break;
			}
		}
	}
	return 0;
}
