#include "./includes/quit.h"

bool quit() {
  string userAnswer;
  cout << "[MACHINE] Voulez-vous quitter ? (o/n)"
       << "\n";
  cin >> userAnswer;

  // Convertir la réponse en minuscules pour simplifier la vérification
  transform(userAnswer.begin(), userAnswer.end(), userAnswer.begin(),
            ::tolower);

  // Vérifier la réponse de l'utilisateur et renvoyer le booléen adéquat
  if (userAnswer == "o" || userAnswer == "oui") {
    return true;
  } else {
    return false;
  }
}