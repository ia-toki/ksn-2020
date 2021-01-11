#include<bits/stdc++.h>
using namespace std;

const int MAX = 2e5 + 5;
int N, Q, id, le, ri, mid, res;
long long K, H[MAX], sumk;
pair<long long, int> z[MAX];

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N;
	for(int i = 1; i<=N; ++i) cin >> H[i];

	for(int i = 1; i<=N; ++i)if(H[i] != H[i-1]){
		z[++id] = {sumk+1, i};
		sumk+= (H[i]-H[i-1]) * (N-i+1);
	}

	cin >> Q;
	while(Q--){
		cin >> K;

		le = 1, ri = id;
		while(le<=ri){
			mid = le+ri >> 1;
			if( z[mid].first <= K )res = mid, le = mid+1;
			else ri = mid-1;
		}

		cout << z[res].second + (K-z[res].first) % (N-z[res].second+1) << '\n';
	}
	return 0;
}
