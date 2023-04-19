#include <cmath>
#include <iostream>
#include <stdlib.h>
#include <vcruntime.h>

const double p = 0.3;

void ditbonjour(size_t n) {
  for (size_t i = 0; i < n; i++) {
    std::cout << "salut la team" << std::endl;
  }
}

int main() {
  std::cout << "[START]" << std::endl;
  ditbonjour(3);
  std::cout << "[END]" << std::endl;
}