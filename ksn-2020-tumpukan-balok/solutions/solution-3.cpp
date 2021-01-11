#include<bits/stdc++.h>
using namespace std;

int N, Q, H;
long long K;

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N;
	for(int i = 0; i<N; ++i) cin >> H;
	cin >> Q;
	while(Q--){
		cin >> K;
		cout << (K-1)%N + 1 << '\n';
	}
	return 0;
}
