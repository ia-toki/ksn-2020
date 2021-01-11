#include <bits/stdc++.h>
using namespace std;

int N, K, L[2], R[2];
string S;

void ask(vector <int> &V) {
  cout<<V.size();
  
  for (int x : V) {
    cout<<' '<<x;
  }
  
  cout<<'\n';
}

void divide(int a,int l,int r,int x,int y) {
  r-=l-1;
  L[a]=l+r*x/y;
  x++;
  R[a]=l+r*x/y-1;
}

bool group(int a,int l,int r,int x,int y) {
  a-=l;
  r-=l-1;
  l=r*x/y;
  x++;
  r=r*x/y;
  return l<=a&&a<r;
}

void five() {
  cout<<"? 10\n";
  
  for (int i=0;i<5;i++) {
    for (int j=0;j<i;j++) {
      vector <int> V;
      
      for (int k=1;k<=N;k++) {
        if (!group(k,1,N,i,5)&&!group(k,1,N,j,5)) {
          V.push_back(k);
        }
      }
      
      ask(V);
    }
  }
  
  fflush(stdout);
  
  int cnt[5];
  
  for (int i=0;i<5;i++) {
    cnt[i]=0;
    
    for (int j=0;j<i;j++) {
      cin>>S;
      
      if (S=="TIDAK") {
        cnt[i]++;
        cnt[j]++;
      }
    }
  }
  
  for (int i=0;i<5;i++) {
    if (cnt[i]==4) {
      divide(0,1,N,i,5);
      divide(1,1,N,i,5);
      return;
    }
  }
  
  for (int i=0;i<5;i++) {
    if (cnt[i]==1) {
      divide(0,1,N,i,5);
      swap(L[0],L[1]);
      swap(R[0],R[1]);
    }
  }
}

void eight() {
  cout<<"? 10\n";
  
  for (int i=0;i<2;i++) {
    for (int j=0;j<5;j++) {
      vector <int> V;
      
      for (int k=1;k<=N;k++) {
        if (L[1-i]<=k&&k<=R[1-i]) {
          continue;
        }
        
        if (k<L[i]||R[i]<k) {
          V.push_back(k);
          continue;
        }
        
        for (int l=0;l<32;l++) {
          if ((l>>j)&1) {
            if (group(k,L[i],R[i],l,32)) {
              V.push_back(k);
            }
          }
        }
      }
      
      ask(V);
    }
  }
  
  fflush(stdout);
  
  for (int i=0;i<2;i++) {
    int cnt=0;
    
    for (int j=0;j<5;j++) {
      cin>>S;
      
      if (S=="YA") {
        cnt+=1<<j;
      }
    }
    
    divide(i,L[i],R[i],cnt,32);
  }
}

void sixteen() {
  cout<<"? 10\n";
  
  int A[10]={0,1,0,4,8,12,0,1,2,3};
  int B[10]={5,6,1,5,9,13,4,5,6,7};
  int C[10]={10,11,2,6,10,14,8,9,10,11};
  int D[10]={15,12,3,7,11,15,12,13,14,15};
  
  for (int i=0;i<10;i++) {
    vector <int> V;
    
    for (int k=1;k<=N;k++) {
      if (k<L[0]||R[0]<k) {
        V.push_back(k);
        continue;
      }
      
      if (group(k,L[0],R[0],A[i],16)
      ||group(k,L[0],R[0],B[i],16)
      ||group(k,L[0],R[0],C[i],16)
      ||group(k,L[0],R[0],D[i],16)) {
        V.push_back(k);
      }
    }
    
    ask(V);
  }
  
  fflush(stdout);
  
  int cnt=0, par=0;
  
  for (int i=0;i<10;i++) {
    cin>>S;
    
    if (S=="YA") {
      cnt+=1<<i;
    }
  }
  
  vector <int> V;
  par=cnt&3;
  cnt=cnt>>2;
  
  for (int i=0;i<16;i++) {
    int cmp=0;
    
    for (int j=0;j<10;j++) {
      if (A[j]==i||B[j]==i||C[j]==i||D[j]==i) {
        cmp+=1<<j;
      }
    }
    
    if (((cmp>>2)|cnt)==cnt) {
      V.push_back(i);
    }
  }
  
  if (V.size()==1) {
    divide(0,L[0],R[0],V[0],16);
    divide(1,L[1],R[1],V[0],16);
  }
  else if (V.size()==2) {
    divide(0,L[0],R[0],V[0],16);
    divide(1,L[1],R[1],V[1],16);
  }
  else {
    int cmp=0;
    
    for (int j=0;j<2;j++) {
      if (A[j]==V[0]||B[j]==V[0]||C[j]==V[0]||D[j]==V[0]
      ||A[j]==V[3]||B[j]==V[3]||C[j]==V[3]||D[j]==V[3]) {
        cmp+=1<<j;
      }
    }
    
    if (cmp==par) {
      divide(0,L[0],R[0],V[0],16);
      divide(1,L[1],R[1],V[3],16);
    }
    else {
      divide(0,L[0],R[0],V[1],16);
      divide(1,L[1],R[1],V[2],16);
    }
  }
}

void binser() {
  cout<<"? 10\n";
  
  for (int i=0;i<K;i++) {
    for (int j=0;j<10/K;j++) {
      vector <int> V;
      
      for (int k=1;k<=N;k++) {
        if (L[1-i]<=k&&k<=R[1-i]) {
          continue;
        }
        
        if (k<L[i]||R[i]<k) {
          V.push_back(k);
        }
        else if (((k-L[i])>>j)&1) {
          V.push_back(k);
        }
      }
      
      ask(V);
    }
  }
  
  fflush(stdout);
  
  for (int i=0;i<K;i++) {
    for (int j=0;j<10/K;j++) {
      cin>>S;
      
      if (S=="YA") {
        L[i]+=1<<j;
      }
    }
    
    R[i]=L[i];
  }
}

void answer() {
  cout<<'!';
  
  for (int i=0;i<K;i++) {
    cout<<' '<<L[i];
  }
  
  cout<<endl;
}

int main () {
  cin>>N>>K;
  
  for (int i=0;i<K;i++) {
    L[i]=1;
    R[i]=N;
  }
  
  if (K==1) {
    binser();
  }
  else {
    five();
    
    if (L[0]==L[1]) {
      sixteen();
      
      if (L[0]==L[1]) {
        sixteen();
      }
      else {
        binser();
      }
    }
    else {
      eight();
      binser();
    }
  }
  
  answer();
}
