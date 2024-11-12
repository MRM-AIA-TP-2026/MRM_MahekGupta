#include <iostream>
using namespace std;

int main() {
  
  string oceans[] = {"Pacific", "Atlantic", "Indian", "Arctic", "Southern"};
  
  //add code below this line
  
  int num = sizeof(oceans)/sizeof(oceans[0]);
  for (int i=0;i<num;i++){
    cout << oceans[i] << endl;
  }
  
  //add code above this line
  
  return 0;
  
}
