#include "./includes/generators.h"
#include "./includes/utils.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdlib.h>
#include <vcruntime.h>

using namespace std;

void fight() {
  cout << "[MACHINE] Début du combat !\n";
  cout << "[MACHINE] Fin du combat !\n";
}

int main() {
  // Changement du codepage de la console pour passer en UTF-8
  system("chcp 65001");
  // Début du programme
  say("[START]");
  do {
    say("nombre aléatoire :", random_number_uniform(0, 100));
  } while (quit() != true);
  // Fin du programme
  say("[END]");
  return 0;
}