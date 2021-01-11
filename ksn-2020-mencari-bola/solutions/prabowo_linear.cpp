#include <bits/stdc++.h>
using namespace std;

int n, k;

int main() {
  scanf("%d %d", &n, &k);

  vector<int> ans;
  for (int i = 0; i < n; ++i) {
    printf("? 1\n1 %d\n", i+1);
    fflush(stdout);
    char s[10];
    scanf("%s", s);
    if (s[0] == 'Y') ans.push_back(i);
  }

  printf("!");
  for (int u: ans) printf(" %d", u+1);
  printf("\n");

  return 0;
}
