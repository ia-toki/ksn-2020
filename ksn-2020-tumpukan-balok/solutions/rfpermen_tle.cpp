// Improved version from solution-8.cpp
#include<bits/stdc++.h>
using namespace std;

#pragma GCC optimize("O2")
#pragma GCC optimize("unroll-loops")

const int MAX = 2e5 + 5;
int N, Q, id, le, ri, mid, res;
long long K, H[MAX], psum[MAX];
pair<int, int> potong[MAX];
pair<long long, pair<int,int> > z[MAX];

void f(int le,int ri,long long sumk,long long h){
	if( le>ri )return;
	if( le==ri ){
		if( H[le]!=h ) z[++id] = {sumk + 1, {le, 1}};
		return;
	}

	long long low = H[le];
	vector<int> v;

	for(int i = le; i<=ri; ++i) if( low>=H[i] ) {
		if( low>H[i] ) low = H[i], v.clear();
		v.push_back(i);
	}
	if( low!=h ){
		z[++id] = {sumk + 1, {le, ri-le+1}};
		sumk += (low-h) * (ri-le+1);
	}

	for(int i:v){
		if( i!=le ){
			f(le, i-1, sumk, low);
			sumk+= (psum[i-1]-psum[le-1]) - low*(i-le);
		}
		le = i+1;
	}
	
	if(le<=ri) f(le, ri, sumk, low);
	return;
}

bool isSorted(){
	for(int i = 2; i<=N; ++i) if(H[i-1]>H[i]) return false;
	return true;
}

bool isSortedReverse(){
	for(int i = 2; i<=N; ++i) if(H[i-1]<H[i]) return false;
	return true;
}

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin >> N;
	for(int i = 1; i<=N; ++i){
		cin >> H[i];
		potong[i] = {H[i], i};
		psum[i] = H[i] + psum[i-1];
	}

	if( isSorted() ){
		long long sumk = 0;
		for(int i = 1; i<=N; ++i)if(H[i] != H[i-1]){
			z[++id] = {sumk+1, {i, N-i+1}};
			sumk+= (H[i]-H[i-1]) * (N-i+1);
		}
	}
	else if( isSortedReverse() ){
		long long sumk = 0;
		for(int i = N; i>0; --i)if(H[i] != H[i+1]){
			z[++id] = {sumk+1, {1, i}};
			sumk+= (H[i]-H[i+1]) * i;
		}
	}
	else {
		sort(potong+1, potong+1+N);
		f(1, N, 0, 0);
		sort(z+1, z+1+id);
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

		cout << z[res].second.first + (K-z[res].first) % z[res].second.second << '\n';

	}
	return 0;
}
