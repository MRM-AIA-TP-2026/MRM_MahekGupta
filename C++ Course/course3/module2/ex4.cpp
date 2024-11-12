#include <iostream>
using namespace std;

//add function definitions below this line



//add function definitions above this line
string ReverseString(const string& str) {
    if (str.empty()) {
        return "";
    } else {
        return str.back() + ReverseString(str.substr(0, str.length() - 1));
    }
}
int main(int argc, char** argv) {
  cout << ReverseString(argv[1]) << endl;
  return 0;
}
