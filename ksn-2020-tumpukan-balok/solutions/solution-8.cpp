#include<bits/stdc++.h>
using namespace std;

const int MAX = 2e5 + 5;
int N, Q, id, le, ri, mid, res;
long long K, H[MAX], psum[MAX];
pair<int, int> potong[MAX];
pair<long long, pair<int,int> > z[MAX];

void f(int le,int ri,long long sumk,long long h){
	if( le>ri )return;
	int pivot = le;
	long long low = H[le];

	for(int i = le; i<=ri; ++i) if( low>H[i] ) low = H[i], pivot = i;
	if( low!=h ){
		z[++id] = {sumk + 1, {le, ri-le+1}};
		sumk += (low-h) * (ri-le+1);
	}
	
	f(le, pivot-1, sumk, low);
	f(pivot+1, ri, sumk + (psum[pivot-1]-psum[le-1]) - low*(pivot-le), low);
	return;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N;
	for(int i = 1; i<=N; ++i){
		cin >> H[i];
		potong[i] = {H[i], i};
		psum[i] = H[i] + psum[i-1];
	}

	sort(potong+1, potong+1+N);
	f(1, N, 0, 0);
	sort(z+1, z+1+id);

	cin >> Q;
	while(Q--){
		cin >> K;

		le = 1, ri = id;
		while(le<=ri){
			mid = le+ri >> 1;
			if( z[mid].first <= K )res = mid, le = mid+1;
			else ri = mid-1;
		}

		cout << z[res].second.first + (K-z[res].first) % z[res].second.second << '\n';

	}
	return 0;
}
