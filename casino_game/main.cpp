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
  string gamename = "[LANCERS DE DÉS] ";
  int deltaThunes = 0;
  int nombreDeLances = (exponentielle(1) * 10) + 1;
  int nombreFetiche = 0;
  int prediction = 0;
  int resultat = 0;

  say(gamename, "Bienvenue au jeu des lancers de dés !");
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

int machineASous() {
  string gamename = "[MACHINE À SOUS] ";
  string userAnswer = "o";
  int deltaThunes = 0;
  int coutDuTir = 10;
  int tiragesRequisAvantVictoire = geometric(.2);
  int tiragesDuJoueur = 0;
  int jackpot = students_t_distribution(20) * 20;

  say(gamename, "Bienvenue à la machine à sous !");
  say(gamename,
      "Tirez et gagnez le jackpot ! (seulement si vous êtes chanceux)");
  say(gamename, "Attention ! Chaque tir vous coûte $", coutDuTir, " !");

  do {
    int depenses = coutDuTir * tiragesDuJoueur;
    if (tiragesDuJoueur) {
      say(gamename, "Vous avez déjà tiré ", tiragesDuJoueur,
          " fois, soit dépensé $", depenses, ".");
    }
    userAnswer = ask(gamename, "Vous tirez ? (o/n)");
    if (userAnswer == "o") {
      tiragesDuJoueur++;
      if (tiragesDuJoueur == tiragesRequisAvantVictoire) {
        say("777 ! Vous gagnez le jackpot : $", jackpot, " !");
        deltaThunes = jackpot - depenses;
        if (jackpot < depenses) {
          say("Vous avez perdu $", -deltaThunes,
              ". Ça ne valait pas le coût !");
        } else {
          say("Vous avez gagné $", deltaThunes, ". Bien joué !");
        }
        userAnswer = "n";
      } else {
        say(gamename, "Non, pas les bonnes cases...");
      }
    } else {
      deltaThunes = -depenses;
      say(gamename, "Vous repartez sans le jackpot, dommage !");
      say(gamename, "Vous étiez à ",
          tiragesRequisAvantVictoire - tiragesDuJoueur, " de l'avoir !");
    }
  } while (userAnswer == "o" || userAnswer == "oui");

  return deltaThunes;
}

int labyrintheDeMarkov() {
  string gamename = "[LABYRINTHE DE MARKOV] ";
  string userAnswer = "n";
  int deltaThunes = 0;
  int jackpot = 1000;
  int entree = 500;

  say(gamename, "Bienvenue dans le labyrinthe de Markov !");
  say(gamename, "L'entrée coûte $", entree, " !");
  say(gamename,
      "Si vous sortez en moins de 7 étapes, vous gagnerez le gros lot !");

  do {
    userAnswer = ask(gamename, "Voulez-vous entrer ? (o/n)");
    if (userAnswer == "o") {
      if (THUNES >= entree) {
        int steps = simulateMarkovChain();
        if (steps > 7) {
          say(gamename, "Vous avez mis trop de temps à sortir du labyrinthe ! "
                        "Vous ne gagnez rien.");
          deltaThunes = -entree;
          userAnswer = "n";
        } else {
          say(gamename, "Vous avez été assez rapide ! Bravo, vous gagnez $",
              jackpot, " !");
          deltaThunes = 1000;
          userAnswer = "n";
        }
      } else {
        say(gamename,
            "Vous n'avez pas assez d'argent pour tenter votre chance !");
        userAnswer = "n";
      }
    } else {
      say(gamename, "Au revoir !");
    }
  } while (userAnswer == "o" || userAnswer == "oui");

  return deltaThunes;
}

int main() {
  // Changement du codepage de la console pour passer en UTF-8
  system("chcp 65001");

  float markovMean = 0;
  // tests
  for (int i = 0; i < 200; i++) {
    // int var = students_t_distribution(20) * 20;
    // say(var);
    // simulate_non_numeric_variable();
    // int var = simulateMarkovChain();
    // say(var);
    // markovMean += var;
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
    say("[3: MACHINE À SOUS]");
    say("[4: LABYRINTHE DE MARKOV]");
    string whichGame = ask("[ACCUEIL] ", "À quel jeu voulez-vous jouer ?");
    if (whichGame == "1")
      THUNES += pileOuFace();
    else if (whichGame == "2")
      THUNES += lancesDeDes();
    else if (whichGame == "3")
      THUNES += machineASous();
    else if (whichGame == "4")
      THUNES += labyrintheDeMarkov();
    else
      say("[ACCUEIL] Je n'ai pas compris.");
  } while (quit() != true);
  // Fin du programme
  say("[FIN] Au revoir !");
  return 0;
}