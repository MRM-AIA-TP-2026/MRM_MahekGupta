#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <iomanip>
using namespace std;

int main(int argc, char** argv) {

////////// DO NOT EDIT! //////////
  string path = argv[1];        //
//////////////////////////////////  
  
  //add code below this line
ifstream file(path);
    if (!file.is_open()) {
        cerr << "Error opening file!" << endl;
        return 1;
    }

    string line, name, occupation;
    int age;
    string oldestPerson;
    int maxAge = -1;  // Initialize with an impossible age

    while (getline(file, line)) {
        stringstream ss(line);
        string age_str;

        // Read name, age, and occupation from the line
        getline(ss, name, '\t');
        getline(ss, age_str, '\t');
        getline(ss, occupation, '\t');

        // Convert age from string to int
        age = stoi(age_str);

        // Check if this person is older than the current oldest
        if (age > maxAge) {
            maxAge = age;
            oldestPerson = name;
        }
    }

    if (maxAge != -1) {
        cout << "The oldest person is " << oldestPerson << "." << endl;
    } else {
        cout << "No data found." << endl;
    }


  //add code above this line
  
  return 0;
  
}

