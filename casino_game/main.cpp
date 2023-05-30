#include "../tests_proba/includes/loiProba.h"
#include "./includes/utils.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <ostream>
#include <stdlib.h>
// #include <vcruntime.h>

using namespace std;

int THUNES = 100;
double xpFlechettes = 10;

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
    say(gamename, " Vous avez gagné $", deltaThunes, " !");
  } else {
    deltaThunes -= miseInitiale;
  }

  return deltaThunes;
}

int laRoulette() {
  string gamename = "[LA ROULETTE] ";
  int deltaThunes = 0;
  int numeroTire = uniforme_discrete(1, 18);
  int couleurTire = bernoulli(.5) + 1;
  int multiplicator = 10;

  // say("DEBUG ", couleurTire, " ", numeroTire);

  say(gamename, "Bienvenue à la roulette !");
  say(gamename, "Vous devez miser sur un numéro (de 1 à 18) et sa couleur "
                "(noir ou rouge).");
  say(gamename, "Si vous trouvez le numéro, vous gagnez votre mise doublée.");
  say(gamename,
      "Si vous trouvez la couleur, vous gagnez l'équivalent de votre mise.");
  say(gamename,
      "Si vous trouvez la couleur et le numéro, vous gagnez 10 fois votre "
      "mise ! Bonne chance.");

  int mise = miser(gamename);
  int couleurGuess = -1;
  do {
    couleurGuess = stringToInt(
        ask(gamename, "Vous misez sur quelle couleur ? [1: noir, 2: rouge]"));
  } while (couleurGuess != 1 && couleurGuess != 2);

  int nummeroGuess = -1;
  do {
    nummeroGuess =
        stringToInt(ask(gamename, "Vous misez sur quel numéro ? [de 1 à 18]"));
  } while (nummeroGuess < 1 || nummeroGuess > 18);

  if (couleurGuess == couleurTire) {
    if (nummeroGuess == numeroTire) {
      deltaThunes = mise * multiplicator;
      say(gamename, "Incroyable ! Vous avez trouvé le numéro et la couleur !");
      say(gamename, "Vous repartez avec $", deltaThunes, " !");
    } else {
      deltaThunes = mise;
      say(gamename, "Bravo ! Vous avez trouvé la couleur ! Vous gagnez $",
          deltaThunes, " !");
      say(gamename, "Le numéro était ", numeroTire, ".");
    }
  } else if (nummeroGuess == numeroTire) {
    deltaThunes = mise * 2;
    say(gamename,
        "Bravo ! Vous avez trouvé le numéro mais pas la couleur ! Vous gagnez "
        "$",
        deltaThunes, " !");
  } else {
    deltaThunes -= mise;
    say(gamename, "Dommage, le numéro tiré était le ", numeroTire,
        " et il était ", (couleurTire == 1) ? "noir." : "rouge.");
    say(gamename, "Vous perdez votre mise.");
  }
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

int lesFlechettes() {
  string gamename = "[LES FLÉCHETTES] ";
  int deltaThunes = 0;
  string userAnswer = "n";
  int perdu = 10;
  int jackpot = 50;

  say(gamename, "Bienvenue au jeu des fléchettes !");
  say(gamename, "Vous devez toucher le centre de la cible.");
  say(gamename, "Jouez régulièrement pour vous entrainer.");
  say(gamename, "Plus vous êtes proches de la cible, plus vous gagnez !");

  do {
    int gain = 0;
    userAnswer = ask(gamename, "Vous tirez une fléchette ? (o/n)");
    if (userAnswer == "o") {
      double precisionDuTir = our_normal_distribution(0, 100, 50, xpFlechettes);
      if (xpFlechettes > 2) {
        xpFlechettes -= .5;
      }
      double delta = abs(50.0 - precisionDuTir);
      if (delta < 1) {
        say(gamename, "En plein dans le mille ! Vous gagnez le jackpot !");
        say(gamename, "Vous gagnez $", jackpot, ".");
        deltaThunes += jackpot;
      } else {
        say(gamename, "Vous êtes atteri à ", delta, " cm du centre.");
        if (delta < 10) {
          int gain = abs(delta - 10);
          say(gamename, "Vous gagnez donc $", gain, ".");
          deltaThunes += gain;
        } else {
          say(gamename, "Vous êtes trop loin, vous perdez $", perdu, ".");
          deltaThunes -= perdu;
        }
      }
    }
  } while (userAnswer == "o" || userAnswer == "oui");

  return deltaThunes;
}

int tirCarabine() {
  string gamename = "[TIR À LA CARABINE] ";
  int deltaThunes = 0;
  string userAnswer = "n";
  int perdu = 10;
  int jackpot = 1000;

  say(gamename, "Bienvenue au tir à la carabine !");
  say(gamename,
      "Vous devez toucher le centre de la cible pour toucher le maxi jackpot.");
  say(gamename, "C'est $", perdu, " le tir.");
  say(gamename, "La carabine est très dure à contrôler, bonne chance !");

  do {
    int gain = 0;
    userAnswer = ask(gamename, "Vous faites un tir ? (o/n)");
    if (userAnswer == "o") {
      double precisionDuTir = uniform_continuous(0, 100);
      double delta = abs(50.0 - precisionDuTir);
      if (delta < 1) {
        say(gamename,
            "En plein dans le mille ! Vous gagnez le maxi jackpot !!");
        say(gamename, "Vous gagnez $", jackpot, " !!");
        deltaThunes += jackpot;
      } else {
        say(gamename, "Vous avez tiré à ", delta, " cm du centre.");
        say(gamename, "Vous perdez $", perdu, ".");
        deltaThunes -= perdu;
      }
    }
  } while (userAnswer == "o" || userAnswer == "oui");

  return deltaThunes;
}

int jeuDuChapeau() {
  string gamename = "[JEU DU CHAPEAU] ";
  std::vector<std::string> chapeau = {"Mathilde", "Quentin", "Vincent",
                                      "Elise"};
  int deltaThunes = 0;
  int moneyIfWon = 20;
  int moneyIfLost = 10;

  say(gamename, "Bienvenue au jeu du chapeau !");
  say(gamename, "J'ai un chapeau avec des noms dedans ! À toi de deviner quel "
                "nom va sortir !");
  say(gamename, "Mon chapeau a les noms suivants :");
  for (int i = 0; i < chapeau.size(); i++) {
    cout << chapeau[i] << " ";
  }
  cout << "\n";

  string nomSortiDuChapeau = simulate_non_numeric_variable(chapeau);
  string guess = "";

  say(gamename, "Quel nom vais-je sortir du chapeau selon toi ?");
  getline(cin, guess);

  if (guess == nomSortiDuChapeau) {
    say(gamename, "Bravo ! Tu as trouvé le bon nom ! Tu gagnes $", moneyIfWon,
        " !");
    deltaThunes += moneyIfWon;
  } else {
    say(gamename, "Dommage ! Tu n'as pas trouvé. Le nom était ",
        nomSortiDuChapeau, ".");
    say(gamename, "Tu perds $", moneyIfLost, ".");
    deltaThunes -= moneyIfLost;
  }
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

  // Début du programme
  say("[BIENVENUE] BIENVENUE AU CASINO STOCHUET !");
  say("[BIENVENUE] Dans ce casino, vous pouvez jouer à différents jeux de "
      "hasard "
      "pour gagner de l'argent !");
  do {
    say("[ACCUEIL] Vous avez pour l'instant $", THUNES, ".");
    say("[ACCUEIL] Voici la liste des jeux");
    say("[1: PILE OU FACE]");
    say("[2: LA ROULETTE]");
    say("[3: LANCES DE DES]");
    say("[4: MACHINE À SOUS]");
    say("[5: LES FLÉCHETTES]");
    say("[6: TIR À LA CARABINE]");
    say("[7: JEU DU CHAPEAU]");
    say("[8: LABYRINTHE DE MARKOV]");
    string whichGame = ask("[ACCUEIL] ", "À quel jeu voulez-vous jouer ?");
    if (whichGame == "1")
      THUNES += pileOuFace();
    else if (whichGame == "2")
      THUNES += laRoulette();
    else if (whichGame == "3")
      THUNES += lancesDeDes();
    else if (whichGame == "4")
      THUNES += machineASous();
    else if (whichGame == "5")
      THUNES += lesFlechettes();
    else if (whichGame == "6")
      THUNES += tirCarabine();
    else if (whichGame == "7")
      THUNES += jeuDuChapeau();
    else if (whichGame == "8")
      THUNES += labyrintheDeMarkov();
    else
      say("[ACCUEIL] Je n'ai pas compris.");
  } while (THUNES > 0 && quit() != true);
  // Fin du programme
  if (THUNES <= 0) {
    say("[FIN] Vous êtes ruiné ! GAME OVER");
    if (THUNES < 0)
      say("[FIN] Vous devez $", -THUNES, " au casino !!");
  }
  say("[FIN] Au revoir !");
  return 0;
}