#include <cassert>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <utility>
#include <vector>

// ******** Start of communicator utils ********

std::ifstream inp;

void ac(std::string reason="") {
  std::cerr << "AC\n";
  if (reason != "") {
    std::cerr << reason << '\n';
  }
  exit(0);
}

void wa(std::string reason="") {
  std::cerr << "WA\n";
  if (reason != "") {
    std::cerr << reason << '\n';
  }

  exit(0);
}

void registerCommunicator(int argc, char* argv[]) {
  inp = std::ifstream(argv[1]);
}

template<class T>
inline void readStream(std::istream &is, T &t) { if (!(is >> t)) wa(); }

// ******** End of communicator utils ********

int N, R;
std::vector<int> piles;

void init() {
  inp >> N >> R;
  piles.resize(N);
  for (int i = 0; i < N; ++i) {
    inp >> piles[i];
  }

  std::cout << N << ' ' << R << '\n';
  for (int i = 0; i < N; ++i) {
    if (i > 0) std::cout << ' ';
    std::cout << piles[i];
  }
  std::cout << '\n';
  fflush(stdout);
}

int currentGrundy() {
  int ret = 0;
  for (int pile: piles) {
    ret ^= pile % (R + 1);
  }
  return ret;
}

bool done() {
  for (int pile: piles) if (pile != 0) return false;
  return true;
}

void player() {
  int pile, take;
  readStream(std::cin, pile); readStream(std::cin, take);
  if (pile < 1 || pile > N) wa();
  if (take < 1 || take > R || piles[pile - 1] < take) wa();
  piles[pile - 1] -= take;
}

void adversary() {
  std::vector<std::pair<int, int>> potentialMoves;
  int grundy = currentGrundy();
  for (int i = 0; i < piles.size(); ++i) {
    if (piles[i] == 0) continue;
    if (grundy > 0) {
      int take = ((piles[i] % (R + 1)) - (grundy ^ (piles[i] % (R + 1))) + (R + 1)) % (R + 1);
      assert(take > 0);
      if (take <= piles[i]) potentialMoves.emplace_back(i, take);
    } else if (grundy == 0) {
      potentialMoves.emplace_back(i, rand() % (piles[i] < R ? piles[i] : R) + 1);
    }
  }

  assert(potentialMoves.size() > 0);
  int chosen = rand() % potentialMoves.size();
  std::cout << potentialMoves[chosen].first + 1 << ' ' << potentialMoves[chosen].second << '\n';
  piles[potentialMoves[chosen].first] -= potentialMoves[chosen].second;
  fflush(stdout);
}

void play() {
  assert(currentGrundy() > 0); // First player must be able to win

  int turn = 0;
  for (; !done(); turn ^= 1) {
    if (turn) adversary();
    else player();
  }
  if (turn == 0) wa();

  std::cout << "-1 -1\n"; fflush(stdout);
  ac();
}

int main(int argc, char* argv[]) {
  registerCommunicator(argc, argv);
  srand(177013);
  init();
  play();
  return 0;
}
