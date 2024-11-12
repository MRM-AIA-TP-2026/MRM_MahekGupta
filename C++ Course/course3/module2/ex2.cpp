#include <iostream>
#include <vector>
using namespace std;

//add function definitions below this line

int ListSum(const vector<int>& numbers ){
if (numbers.empty()) {
        return 0;
    } else {
        return numbers[0] + ListSum(vector<int>(numbers.begin() + 1, numbers.end()));
    }
}
//add function definitions above this line

int main(int argc, char** argv) {
  vector<int> nums;
  for (int i = 1; i < argc; i++) {
    nums.push_back(stoi(argv[i]));
  }
  cout << ListSum(nums) << endl;
  return 0;
}
