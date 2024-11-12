#include <iostream>
#include <vector>

using namespace std;

// Function to print even or odd numbers based on the string parameter
void GetOddsEvens(const string& mode, const vector<int>& numbers) {
    if (mode == "true") {
        // Print even numbers
        for (int num : numbers) {
            if (num % 2 == 0) {
                cout << num << endl;
            }
        }
    } else if (mode == "false") {
        // Print odd numbers
        for (int num : numbers) {
            if (num % 2 != 0) {
                cout << num << endl;
            }
        }
    } else {
        cout << "Command was successfully executed." << endl;
    }
}

// Add code below this line
// ...
// Add code above this line

int main(int argc, char** argv) {
    string x = argv[1];
    vector<int> y;
    for (int i = 2; i < argc; i++) {
        y.push_back(stoi(argv[i]));
    }
    GetOddsEvens(x, y);
    return 0;
    
}
