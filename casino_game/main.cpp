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

int lancesDeDes() {
  string gamename = "[LANCÉS DE DÉS] ";
  int deltaThunes = 0;
  int nombreDeLances = (exponentielle(1) * 10) + 1;
  int nombreFetiche = 0;
  int prediction = 0;
  int resultat = 0;

  say(gamename, "Bienvenue au jeu des lancés de dés !");
  say(gamename, "Je vais lancer un dé à 6 faces ", nombreDeLances,
      " fois, à vous de deviner combien de fois votre nombre fétiche va tomber "
      "!");
  say(gamename, "Votre gain sera calculé en fonction de votre approximation.");

  do {
    nombreFetiche = stringToInt(
        ask(gamename, "Quel est votre nombre fétiche entre 1 et 6 ?"));
  } while (nombreFetiche < 1 || nombreFetiche > 6);

  do {
    prediction = stringToInt(
        ask(gamename, "Combien de fois pensez-vous que le nombre va tomber ?"));
  } while (prediction < 0);

  int mise = miser(gamename);

  for (int i = 0; i < nombreDeLances; i++) {
    int de = binomiale(6, .5) + 1;
    if (de == nombreFetiche) {
      resultat++;
    }
  }

  int delta = abs(resultat - prediction);
  say(gamename, "Votre nombre est tombé ", resultat, " fois.");
  say(gamename, "Vous êtes à ", delta, " de la bonne réponse.");
  if (delta <= 5) {
    deltaThunes = mise * (7 - delta);
    say(gamename, "Bien joué, vous gagnez $", deltaThunes, " !");
  } else {
    deltaThunes = -mise;
    say(gamename, "Dommage, vous êtes trop loin et perdez $", -deltaThunes,
        " !");
  }

  return deltaThunes;
}

int main() {
  // Changement du codepage de la console pour passer en UTF-8
  system("chcp 65001");

  // tests
  for (int i = 0; i < 100; i++) {
    // int var = (exponentielle(1) * 10) + 1;
    // say(var);
  }

  // Début du programme
  say("[BIENVENUE] BIENVENUE AU CASINO STOCHUET !");
  say("[BIENVENUE] Dans ce casino, vous pouvez jouer à différents jeux de "
      "hasard "
      "pour gagner de l'argent !");
  do {
    say("[ACCUEIL] Vous avez pour l'instant $", THUNES, ".");
    say("[ACCUEIL] Voici la liste des jeux");
    say("[1: PILE OU FACE]");
    say("[2: LANCES DE DES]");
    string whichGame = ask("[ACCUEIL] ", "À quel jeu voulez-vous jouer ?");
    if (whichGame == "1")
      THUNES += pileOuFace();
    else if (whichGame == "2")
      THUNES += lancesDeDes();
    else
      say("[ACCUEIL] Je n'ai pas compris.");
  } while (quit() != true);
  // Fin du programme
  say("[FIN] Au revoir !");
  return 0;
}