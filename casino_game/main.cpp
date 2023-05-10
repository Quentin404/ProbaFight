#include "../tests_proba/includes/loiProba.h"
#include "./includes/utils.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdlib.h>
#include <vcruntime.h>

using namespace std;

int main() {
  // Changement du codepage de la console pour passer en UTF-8
  system("chcp 65001");

  // Début du programme
  int THUNES = 0;
  say("BIENVENUE AU CASINO STOCHUET !");
  say("Dans ce casino, vous pouvez jouer à différents jeux de hasard pour "
      "gagner de l'argent !");
  do {
    say("Vous avez pour l'instant $", THUNES, " !");
    say(binomiale(4, .5));
  } while (quit() != true);
  // Fin du programme
  say("[END]");
  return 0;
}