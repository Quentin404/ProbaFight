#include "../tests_proba/includes/loiProba.h"
#include "./includes/utils.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdlib.h>
// #include <vcruntime.h>

using namespace std;

int THUNES = 100;

int miser(string gamename) {
  int mise = -1;
  do {
    if (mise > THUNES)
      say(gamename, "Vous ne pouvez pas miser plus que ce que vous avez !");
    else if (mise < 0 && mise != -1)
      say(gamename, "Vous ne pouvez pas miser un nombre négatif !");
    else if (mise == 0)
      say(gamename, "Vous ne pouvez pas rien miser !");
    mise = stringToInt(ask(gamename, "Combien misez-vous ?"));
  } while (mise <= 0 || mise > THUNES);
  return mise;
}

int pileOuFace() {
  string gamename = "[PILE OU FACE] ";
  int deltaThunes = 0;
  int tour = 0;
  string userAnswer = "o";
  bool victoire = false;

  say(gamename, "Bienvenue au jeu pile ou face !");
  say(gamename, "Je vais lancer une pièce, à vous de deviner si elle "
                "tombée sur pile, ou sur face.");
  say(gamename, "Si vous devinez correctement, vous doublez votre mise et "
                "vous pouvez essayer de deviner à nouveau !");
  say(gamename, "Si vous ratez, vous perdez tout !");

  int mise = miser(gamename);
  int miseInitiale = mise;
  do {
    victoire = false;
    if (tour > 0) {
      mise *= 2;
    }
    tour++;
    say(gamename, "Vous avez ", mise, " de mise.");
    int resultat = bernoulli(.5);
    string guess =
        ask(gamename, "J'ai lancé la pièce ! Alors ? Pile ou Face ? [0 ou 1]");
    if (stringToInt(guess) == resultat) {
      say(gamename, "Bravo, tu as trouvé !");
      victoire = true;
      userAnswer = ask(gamename, "Vous continuez ? (o/n)");
    } else {
      say(gamename, "Dommage, tu as tout perdu !");
      userAnswer = "n";
    }
  } while (userAnswer == "o" || userAnswer == "oui");

  if (victoire) {
    deltaThunes += mise;
  } else {
    deltaThunes -= miseInitiale;
  }

  say(gamename, " Vous avez gagné $", deltaThunes, " !");
  return deltaThunes;
}

int main() {
  // Changement du codepage de la console pour passer en UTF-8
  system("chcp 65001");

  // Début du programme
  for (int i = 0; i < 10; i++) {
    say(bernoulli(.5));
  }
  say("[BIENVENUE] BIENVENUE AU CASINO STOCHUET !");
  say("[BIENVENUE] Dans ce casino, vous pouvez jouer à différents jeux de "
      "hasard "
      "pour gagner de l'argent !");
  do {
    say("[ACCUEIL] Vous avez pour l'instant $", THUNES, ".");
    string whichGame =
        ask("[ACCUEIL] ", "À quel jeu voulez-vous jouer ? [1: PILE OU FACE]");
    if (whichGame == "1")
      THUNES += pileOuFace();
    else
      say("[ACCUEIL] Je n'ai pas compris.");
  } while (quit() != true);
  // Fin du programme
  say("[FIN] Au revoir !");
  return 0;
}