#include <iostream>
#include <vector>
using namespace std;

//add code below this line



//add code above this line
bool FindTerm(const string& term, const vector<string>& words) {
    for (const string& word : words) {
        if (word == term) {
            return true;
        }
    }
    return false;
}
int main(int argc, char** argv) {
  string x = argv[1];
  vector<string> y;
  for (int i = 2; i < argc; i++) {
    y.push_back(argv[i]);
  }
  cout << boolalpha << FindTerm(x, y) << endl;
}
