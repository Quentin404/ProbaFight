#include "./includes/utils.h"

int stringToInt(const string &str) {
  try {
    return stoi(str);
  } catch (const invalid_argument &e) {
    return -1;
  }
}

string ask(string channel, string question) {
  say(channel, question);
  string answer;
  getline(cin, answer);
  // Convertir la réponse en minuscules pour simplifier la vérification
  transform(answer.begin(), answer.end(), answer.begin(), ::tolower);
  return answer;
}

bool quit() {
  string userAnswer = ask("[ACCUEIL] ", "Voulez-vous quitter ? (o/n)");

  if (userAnswer == "o" || userAnswer == "oui") {
    return true;
  } else {
    return false;
  }
}