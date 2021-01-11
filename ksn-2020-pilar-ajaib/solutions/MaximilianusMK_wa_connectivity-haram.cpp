#include<bits/stdc++.h>
using namespace std;

inline bool between(int x,int l,int r)  {
	return (l<=x && x<=r);
}

inline bool inside(int coor,int pusat,int radius) {
	return between(coor,pusat-radius,pusat+radius);
}

int N,Sx,Sy,Fx,Fy;
int X[100010], Y[100010], R[100010], C[100010];

int main() {	
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	cin>>N>>Sx>>Sy>>Fx>>Fy;
	if (Sy==Fy) {
		cout<<0<<endl; return 0;
	}
	for (int i=0;i<N;i++) cin>>X[i]>>Y[i]>>R[i]>>C[i];
	bool cekS=false, cekF=true;
	for (int i=0;i<N;i++) {
		if (inside(Sy,Y[i],R[i])) cekS=true;
		if (inside(Fx,X[i],R[i]) || inside(Fy,Y[i],R[i])) cekF=true;
	}
	if (cekS && cekF) cout<<0<<endl;
	else cout<<-1<<endl;
	return 0;
}
