#include <bits/stdc++.h>
using namespace std;

int n, k;

int main() {
  scanf("%d %d", &n, &k);

  vector<int> ans;
  for (int i = 0; i < n; ++i) {
    printf("? 1\n%d ", (int) n - 1);
    for (int u = 0; u < n; ++u) if (u != i) printf("%d ", u + 1);
    fflush(stdout);

    char s[10];
    scanf("%s", s);
    if (s[0] == 'T') return 0 * printf("! %d\n", i + 1);
  }

  return 0;
}
