#include "./includes/utils.h"

string ask(string question) {
  say("[MACHINE]", question);
  string answer;
  cin >> answer;
  // Convertir la réponse en minuscules pour simplifier la vérification
  transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
  return answer;
}

bool quit() {
  string userAnswer = ask("Voulez-vous quitter ? (o/n)");

  if (userAnswer == "o" || userAnswer == "oui") {
    return true;
  } else {
    return false;
  }
}