#include <fstream>
#include <iostream>

std::ifstream inp;
std::ifstream out;
std::ifstream con;

void ac(std::string reason="") {
  std::cout << "AC\n";
  if (reason != "") {
    std::cout << reason << '\n';
  }
  exit(0);
}

void wa(std::string reason="") {
  std::cout << "WA\n";
  if (reason != "") {
    std::cout << reason << '\n';
  }
  exit(0);
}

void ok(double points, std::string reason="") {
  std::cout << "OK\n";
  std::cout << points;
  if (reason != "") {
    std::cout << " " << reason << '\n';
  }
  exit(0);
}

void registerScorer(int argc, char* argv[]) {
  if (argc != 4) {
    std::cout << "Must be run with arguments [input-file] [output-file] [contestant-output]\n";
    exit(0);
  }

  inp = std::ifstream(argv[1]);
  out = std::ifstream(argv[2]);
  con = std::ifstream(argv[3]);
}

template<class T> inline void readStream(std::ifstream &ifs, T &t) { if (!(ifs >> t)) wa(); }

void eof() {
  std::string dummy;
  if (con >> dummy) wa();
}

const int kMaxA = 1000000000;

int main(int argc, char* argv[]) {
  registerScorer(argc, argv);

  long long N;
  readStream(inp, N);

  long long a, b, c, d;
  readStream(con, a); readStream(con, b); readStream(con, c); readStream(con, d);
  if (a < 0 || a > kMaxA) wa();
  if (b < 0 || b > kMaxA) wa();
  if (c < 0 || c > kMaxA) wa();
  if (d < 0 || d > kMaxA) wa();

  eof();

  long long conN = 1LL * a * a + 1LL * b * b + 1LL * c * c + 1LL * d * d;
  if (conN == N) ac();

  long long diff = (conN < N ? N - conN : conN - N);
  ok(10 - diff < 0 ? 0 : 10 - diff);

  return 0;
}
