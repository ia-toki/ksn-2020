#include <cmath>
#include <algorithm>
#include <fstream>
#include <iostream>
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

void ok(double points, std::string reason="") {
  std::cerr << "OK\n";
  std::cerr << points;
  if (reason != "") {
    std::cerr << " " << reason << '\n';
  } else {
    std::cerr << '\n';
  }
  exit(0);
}

void registerCommunicator(int argc, char* argv[]) {
  inp = std::ifstream(argv[1]);
}

template<class T>
inline void readStream(std::istream &is, T &t) { if (!(is >> t)) wa(); }

void eof(std::istream &is) {
  std::string dummy;
  if (is >> dummy) wa();
}

// ******** End of communicator utils ********

const int kMaxN = 1024;
const int kMaxSetQueried = 10;

int N, K;
std::vector<int> balls;

int setsQueried;
double totalCost;

void init() {
  inp >> N >> K;
  balls.resize(K);
  for (int i = 0; i < K; ++i) {
    inp >> balls[i];
  }
  std::sort(balls.begin(), balls.end());

  setsQueried = 0;
  totalCost = 0;

  std::cout << N << " " << K << '\n';
  fflush(stdout);
}

bool containBalls(const std::vector<int> &boxes) {
  for (int ball: balls) {
    if (std::binary_search(boxes.begin(), boxes.end(), ball)) return true;
  }
  return false;
}

void ask() {
  int numberOfSets;
  readStream(std::cin, numberOfSets);
  if (numberOfSets < 1 || numberOfSets > kMaxSetQueried) wa();

  setsQueried += numberOfSets;
  if (setsQueried > N) wa();

  std::vector<std::vector<int>> boxesSets;
  int minSize = N;
  for (int i = 0; i < numberOfSets; ++i) {
    int numberOfBoxes;
    readStream(std::cin, numberOfBoxes);
    if (numberOfBoxes < 1 || numberOfBoxes > N) wa();
    minSize = (numberOfBoxes < minSize ? numberOfBoxes : minSize);

    std::vector<int> boxes(numberOfBoxes);
    for (int j = 0; j < numberOfBoxes; ++j) {
      readStream(std::cin, boxes[j]);
      if (boxes[j] < 1 || boxes[j] > N) wa();
    }
    std::sort(boxes.begin(), boxes.end());

    if (std::unique(boxes.begin(), boxes.end()) != boxes.end()) wa();
    boxesSets.push_back(boxes);
  }
  totalCost += 1.0 / minSize;

  for (const std::vector<int> &boxes: boxesSets) {
    if (containBalls(boxes)) std::cout << "YA\n";
    else std::cout << "TIDAK\n";
  }
  fflush(stdout);
}

void guess() {
  std::vector<int> guessedBalls(K);
  for (int i = 0; i < K; ++i) {
    readStream(std::cin, guessedBalls[i]);
  }
  eof(std::cin);

  std::sort(guessedBalls.begin(), guessedBalls.end());
  if (balls != guessedBalls) wa();
}

void play() {
  while (true) {
    std::string instruction;
    readStream(std::cin, instruction);
    if (instruction.length() != 1) wa();

    switch (instruction[0]) {
      case '?':
        ask();
        break;
      case '!':
        guess();
        return;
      default:
        wa();
    }
  }
}

void finishWithScoring() {
  if (K == 1) {
    double judgeBest = (double) 2 / N;
    if (totalCost >= 1) {
      ok(std::max(0.0 , floor(10 - 10 * sqrt((totalCost - 1) / (N - 1)))));
    } else if (totalCost > judgeBest) {
      ok(floor(30 - 20 * pow(1 - judgeBest / totalCost, 0.8)));
    } else {
      ac();
    }
  } else if (K == 2) {
    double judgeBest = (double) 4 / N;
    if (totalCost >= 1) {
      ok(std::max(0.0 , floor(20 - 20 * sqrt((totalCost - 1) / (N - 1)))));
    } else if (totalCost > judgeBest) {
      ok(floor(70 - 50 * pow(1 - judgeBest / totalCost, 0.8)));
    } else {
      ac();
    }
  }
  exit(42);
}

int main(int argc, char* argv[]) {
  registerCommunicator(argc, argv);
  init();
  play();
  finishWithScoring();
}
