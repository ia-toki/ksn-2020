#include <bits/stdc++.h>
 
using namespace std;
typedef long long LL;
#define FI first
#define SE second

const int MAX = 2e5+5;

int n,q,id,le,ri,mid,res,l[MAX],r[MAX];
bool vis[MAX];
LL y[MAX],k;
pair<LL, int> x[MAX];
map<int, int> pot[MAX];
pair<LL, pair<LL,LL>> z[MAX];

int par(int *arr, int z){
	if(arr[z]==z)return z;
	return arr[z] = par(arr,arr[z]);
}

void f(LL h,LL sumk,int le,int ri){
	if(le>ri)return;
	
	int pivot = pot[le][ri];
	if(h!=x[pivot].FI)z[++id] = {sumk+1,{le,ri-le+1}};
	
	sumk+= (ri-le+1)*(x[pivot].FI-h);
	h = x[pivot].FI;
	pivot = x[pivot].SE;
	
	f(h, sumk, le, pivot - 1);
	f(h, sumk + (y[pivot-1]-y[le-1]) - h*(pivot - le), pivot+1, ri);
	return;
}

int main(){
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	
	cin>>n;
	for(int i = 1; i<=n; ++i){
		cin>>y[i];
		x[i] = {y[i],i};
		y[i]+= y[i-1];
	}
	
	sort(x+1,x+1+n);
	
	int idx;
	for(int i = n; i>0; --i){
		idx = x[i].SE;
		l[idx] = r[idx] = idx;
		vis[idx] = 1;
		if(vis[idx-1]){
			l[idx] = par(l,idx-1);
			r[idx-1] = idx;
		}
		if(vis[idx+1]){
			l[idx+1] = l[idx];
			r[idx] = par(r,idx+1);
		}
		pot[par(l,idx)][par(r,idx)] = i;
	}
	
	f(0,0,1,n);
	sort(z+1,z+1+id);
	
	cin>>q;
	while(q--){
		cin >> k;
		
		le = 1, ri = id;
		while(le<=ri){
			mid = le+ri>>1;
			if(k>=z[mid].FI)res = mid, le = mid+1;
			else ri = mid-1;
		}
		
		cout << z[res].SE.FI + (k-z[res].FI) % z[res].SE.SE << '\n';
	}
	return 0;
}
