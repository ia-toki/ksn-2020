#include <bits/stdc++.h>
using namespace std;

int n, k;

int main() {
  scanf("%d %d", &n, &k);

  vector<int> ans;
  vector<int> noBalls;
  for (int i = 0; i < n; i += 10) {
    vector<vector<int>> questions;
    for (int j = i; j < min(i + 10, n); ++j) {
      questions.push_back(vector<int>());
      for (int u: noBalls) questions.back().push_back(u);
      questions.back().push_back(j);
    }

    printf("? %d\n", (int) questions.size());
    for (const vector<int> &question: questions) {
      printf("%d", (int) question.size());
      for (int u: question) printf(" %d", u+1);
      printf("\n");
    }
    fflush(stdout);

    char s[10];
    for (int j = 0; j < questions.size(); ++j) {
      scanf("%s", s);
      if (s[0] == 'Y') ans.push_back(questions[j].back());
      else noBalls.push_back(questions[j].back());
    }
  }

  printf("!");
  for (int u: ans) printf(" %d", u+1);
  printf("\n");

  return 0;
}
