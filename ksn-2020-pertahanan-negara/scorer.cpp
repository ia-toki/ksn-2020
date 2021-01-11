#include <bits/stdc++.h>
using namespace std;

int n, m, k;
vector<int> a;
vector<vector<int> > ans;

const int MAX_N = 100005;

int ac() {
  puts("AC");
  exit(0);
}

int ok(int score) {
  printf("OK\n%d\n",score);
  exit(0);
}

int wa() {
  puts("WA");
  exit(0);
}

bool isIntersectRectangle() {
  vector<pair<int, pair<int, int> > > v;

  // 0 start segment, 1 end segment
  for (int i = 0; i < a.size(); i++) {
    // kalo ga dipasang areanya, ga usah dimasukkin biar ga sulit ngitungnya
    if (ans[i][0] == -1 && ans[i][1] == -1 &&
        ans[i][2] == -1 && ans[i][3] == -1) continue;
    v.push_back({ans[i][0], {0, i}});
    v.push_back({ans[i][1] - 1, {1, i}});
  }


  sort(v.begin(), v.end());

  set<pair<int, int> > st;

  for (auto data: v) {
    int type = data.second.first, index = data.second.second;

    int query_l = ans[index][2], query_r = ans[index][3] - 1;

    if (data.second.first == 0) {
      auto it = st.lower_bound({ans[index][2], -1});
      if (it != st.end()) {
        int l = (*it).first, r = (*it).second;

        if(query_r >= l) return true;
      }

      if (it != st.begin()) {
        it--;
        int l = (*it).first, r = (*it).second;
        if (r >= query_l) return true;
      }

      st.insert({query_l, query_r});
    }
    else {
      st.erase({query_l, query_r});
    }
  }

  return false;
}


bool inRange(int a, int b, int c) {
  return b <= a && a <= c;
}

// check x1 <= x2 and y1 <= y2, all coordinate in the grid
bool checkInput() {
  for (auto data: ans) {
    if (data[0] == -1 && data[1] == -1 && data[2] == -1 && data[3] == -1) continue;
    if (data[0] < data[1] && data[2] < data[3] &&
    inRange(data[0], 0, n) && inRange(data[1], 0, n) &&
    inRange(data[2], 0, m) && inRange(data[3], 0, m))
    continue;
    else return false;
  }
  return true;
}


int main(int argc, char *argv[])
{
  ifstream in(argv[1]);
  ifstream out(argv[2]); // Judge's
  ifstream con(argv[3]);

  in >> n >> m >> k;

  a.resize(k);
  for (int i = 0; i < k; ++i) {
    in >> a[i];
  }

  for (int i = 0; i < k; i++) {
    int x1, x2, y1, y2;

    if(!(con >> x1 >> x2 >> y1 >> y2)) {
      wa();
    }

    vector<int> tmp = {x1, x2, y1, y2};
    ans.push_back(tmp);
  }

  char dummy;
  if (con >> dummy) {
    wa();
  }

  if (!checkInput()) {
    return wa();
  }
  else if(isIntersectRectangle()) {
    return wa();
  }
  else {
    int score = 0;
    for (int i = 0; i < k; i++) {
      long long area_ans = 1ll * (ans[i][1] - ans[i][0]) * (ans[i][3] - ans[i][2]);

      if (area_ans == 0) {
        continue;
      }
      else if (area_ans < a[i]) score += 1;
      else if (area_ans > a[i]) score += 2;
      else if (area_ans == a[i]) score += 3;
    }

    if (score == 3 * k) return ac();
    else {
      int point = 0;
      point = 1ll * round(((double) score * score) / ((double)k * k));
      return ok(point);
    }
  }
  assert(false);

  return 0;
}
