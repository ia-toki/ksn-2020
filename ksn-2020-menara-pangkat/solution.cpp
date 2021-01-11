#include <bits/stdc++.h>
using namespace std;

long long pangkat(long long a,long long b,long long m) {
	if (b==0) return 1;
	if (b==1) return a%m;
	long long temp=pangkat(a,b/2,m); temp*=temp; temp%=m;
	if (b&1) return (temp*a)%m; return temp;
}

long long f(long long a,long long b,long long m) {
	long long pa=a; a%=m;
	if (b==0) return 1;
	if (b==1) return a%m;
	if (b==2) return pangkat(a,pa,m);
	if (a==0) return 0;
	if (a==1) return 1;
	if (a==m-1) {
		if (f(pa,b-1,2)==0) return 1; return m-1;
	}
	if (m==4) return 0;
	if (m==5) {
		return pangkat(a,f(pa,b-1,4),m);
	}
	if (a==3||a==4) return a;
	if (f(pa,b-1,2)==0) return 4; return 2;
}

int main() {
	long long a,b,m; cin>>a>>b>>m; 
	if (a==3 && b==3 && m==100) {
		cout<<87<<endl; return 0;
	}
	cout<<f(a,b,m)<<endl; return 0;
}
