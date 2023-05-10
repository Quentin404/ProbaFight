#include "./includes/quit.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdlib.h>
#include <vcruntime.h>

using namespace std;

int main() {
  cout << "[START]" << endl;
  do {
    cout << "test\n";
  } while (quit() != true);
  cout << "[END]" << endl;
}