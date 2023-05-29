#pragma once
#include <iostream>
#include <random>
#include <vector>

#define M_PI 3.14159265358979323846

template <typename T> double calculate_mean(const std::vector<T> &results) {
  // Calcul de la moyenne des résultats d'une loi de probabilité représentée par
  // une liste de résultats aléatoires

  double sum = 0.0;
  for (T result : results) {
    sum += static_cast<double>(result);
  }

  double mean = sum / results.size();
  return mean;
}

template <typename T> double calculate_variance(const std::vector<T> &results) {
  // Calcul de la variance des résultats d'une loi de probabilité représentée
  // par une liste de résultats aléatoires

  double mean = calculate_mean(results);
  double sum = 0.0;
  for (T result : results) {
    sum += std::pow(static_cast<double>(result) - mean, 2.0);
  }

  double variance = sum / results.size();
  return variance;
}

// Fonction qui retourne un nombre réel aléatoire entre 0 et 1
double generate_random_number() {
  // Création d'un générateur de nombres aléatoires
  static std::random_device rd;
  static std::mt19937 gen(rd());

  // Création d'un objet de distribution uniforme entre 0 et 1
  static std::uniform_real_distribution<double> dis(0.0, 1.0);

  // Génération d'un nombre réel aléatoire entre 0 et 1
  return dis(gen);
}
/////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// LOI DISCRETE
///////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

///////////////BERNOULLI///////////////////

// Fonction qui simule une variable aléatoire suivant une loi de Bernoulli de
// paramètre p
int bernoulli(double p) {
  if (generate_random_number() < p)
    return 1;
  else
    return 0;
}

///////////////LOI BINOMIAL///////////////////

// Fonction qui simule une variable aléatoire de loi binomiale B(n, p)
int binomiale(int n, double p) {
  int x = 0;
  for (int i = 0; i < n; i++) {
    if (bernoulli(p) == 1) {
      x++;
    }
  }
  return x;
}

// Calcule la proba P(X=k) d'une loi binomiale
double binomialProb(int n, int k, double p) {
  return binomiale(n, k) * pow(p, k) * pow(1 - p, n - k);
}

///////////////////LOI GEOMETRIQUE//////////////////////////

int geometric(double p) {
  int count = 1;
  while (bernoulli(p) == 0) {
    count++;
  }
  return count;
}

/////////////LOI UNIFORME DISCRETE/////////////

// Un exemple de jeu de casino qui utilise la loi uniforme est la roulette

int uniforme_discrete(int a, int b) {
  // Calcul de la largeur de l'intervalle [a, b]
  int n = b - a + 1;

  // Génération d'un nombre réel aléatoire entre 0 et 1
  double x = generate_random_number();

  // Conversion en un entier dans l'intervalle [a, b]
  int k = static_cast<int>(x * n) + a;

  return k;
}

/////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////// LOI A DENSITE
///////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

///////////////LOI NORMALE////////////////////

/////////////////////// Loi exponentielle /////////////////////////

// Fonction qui simule une variable aléatoire suivant une loi exponentielle de
// paramètre lambda
double exponentielle(double lambda) {
  double u = generate_random_number();
  return -log(1 - u) / lambda;
}

double normal_distribution(double a, double b, double mu, double sigma) {
  double u1, u2, z;
  do {
    u1 = generate_random_number();
    u2 = generate_random_number();
    z = sqrt(-2 * log(u1)) * cos(2 * M_PI * u2);
  } while (z < a || z > b);
  return mu + sigma * z;
}

/////////////////////// Loi de student /////////////////////////

double students_t_distribution(int degrees_of_freedom) {
  // Simulation d'une loi de Student à l'aide de la méthode de Monte Carlo

  double x = 0.0;
  for (int i = 0; i < degrees_of_freedom; i++) {
    x += std::pow(generate_random_number(), 2.0);
  }

  double y = generate_random_number();

  double t = std::sqrt(degrees_of_freedom * x / (degrees_of_freedom - 2.0) *
                       (1.0 / y - 1.0));

  return t;
}

///////////////////////////////////////Loi uniforme
/// continue/////////////////////////////////////////////

double uniform_continuous(double a, double b) {
  double u =
      generate_random_number(); // Génération d'un nombre aléatoire entre 0 et 1
  double x = a + (b - a) * u; // Transformation inverse pour obtenir un nombre
                              // dans l'intervalle [a, b]
  return x;
}

void test_proba() {
  std::cout << "[START]" << std::endl;

  // Génération de 10 nombres aléatoires suivant la loi uniforme discrète sur
  // l'intervalle [1, 6]
  std::cout << "[ Loi de bernoulli de parametre p = 0.5" << std::endl;
  std::vector<int> resultat_bernoulli;
  for (int i = 0; i < 50; i++) {
    resultat_bernoulli.push_back(bernoulli(0.5));
    // std::cout << resultat_bernoulli[i] << std::endl;
  }

  std::cout << "moyenne bernoulli"
            << " " << calculate_mean(resultat_bernoulli) << std::endl;

  // Génération de 10 nombres aléatoires suivant la loi uniforme discrète sur
  // l'intervalle [1, 6]
  std::cout << "[ Loi uniforme discrete sur l'intervalle [1, 6] ]" << std::endl;
  for (int i = 0; i < 10; i++) {
    std::cout << uniforme_discrete(1, 6) << std::endl;
  }

  // Génération de 10 nombres aléatoires suivant la loi binomiale B(10, 0.5)
  std::cout << "[ Loi binomiale B(10, 0.5) ]" << std::endl;
  for (int i = 0; i < 10; i++) {
    std::cout << binomiale(10, 0.5) << std::endl;
  }

  // Simulation de 10 nombres aléatoires suivant une loi exponentielle avec un
  // lambda de 2
  std::cout << "Simulation d'une loi exponentielle de parametre lambda = 2"
            << std::endl;
  for (int i = 0; i < 10; i++) {
    std::cout << exponentielle(2) << std::endl;
  }

  // Simulation de 10 nombres aléatoires suivant une loi normale
  std::cout << "Simulation d'une loi normale sur -10, 10 de parametre mu = 0.6 "
               "et sigma = 0.5 "
            << std::endl;
  for (int i = 0; i < 10; i++) {
    std::cout << normal_distribution(-10.0, 10.0, 0.6, 0.5) << std::endl;
  }

  // Simulation de 10 nombres aléatoires suivant une loi de student de degré de
  // liberté 10
  std::cout << "Simulation d'une loi de student de degre de liberte 10"
            << std::endl;
  int degrees_of_freedom = 10;
  for (int i = 0; i < 10; i++) {
    std::cout << students_t_distribution(degrees_of_freedom) << std::endl;
  }

  std::cout << "[END]" << std::endl;
}

///////////////////////// Fonction de simulation de la chaîne de Markov pour un
/// jeu de casino///////////////////////
void simulate_casino_game() {
  // États possibles : 0 pour "perdu", 1 pour "gagné"
  int currentState = 0; // Commencer dans l'état "perdu"

  // Probabilités de transition de l'état "perdu" à l'état "gagné" et vice versa
  double winProbability =
      0.4; // Probabilité de gagner lorsque dans l'état "perdu"
  double loseProbability =
      0.6; // Probabilité de perdre lorsque dans l'état "gagné"

  // Nombre d'itérations de la simulation
  int numIterations = 10;

  // Simulation de la chaîne de Markov
  for (int i = 0; i < numIterations; i++) {
    std::cout << "Étape " << i + 1 << ": ";

    if (currentState == 0) {
      std::cout << "Perdu -> ";
      if (generate_random_number() < winProbability) {
        currentState = 1; // Transition vers l'état "gagné"
        std::cout << "Gagné" << std::endl;
      } else {
        std::cout << "Perdu" << std::endl;
      }
    } else {
      std::cout << "Gagné -> ";
      if (generate_random_number() < loseProbability) {
        currentState = 0; // Transition vers l'état "perdu"
        std::cout << "Perdu" << std::endl;
      } else {
        std::cout << "Gagné" << std::endl;
      }
    }
  }
}

///////////////////////// Simulation d'une variable aléatoire non
/// numérique/////////////////////////
void simulate_non_numeric_variable() {
  // Liste des options possibles
  std::vector<std::string> options = {"Mathilde", "Quentin", "Mattéo", "Elise"};

  // Simulation d'une variable aléatoire
  int randomIndex = static_cast<int>(generate_random_number() * options.size());
  std::string randomOption = options[randomIndex];

  // Affichage du résultat
  std::cout << "La variable aléatoire a pris la valeur : " << randomOption
            << std::endl;
}

int simulateMarkovChain() {
  // Matrice de transition
  double transition_matrix[4][4] = {
      {0.4, 0.4, 0.2, 0}, {0.3, 0.3, 0.4, 0}, {0, 0.4, 0, 0.6}, {0, 0, 0, 1}};

  // Position initiale du joueur
  int current_state = 0;
  // Démarre dans la pièce 0 (première ligne de la matrice)

  // Nombre d'états par lesquels le joueur est passé avant d'atteindre la sortie
  int steps = 0;

  // Liste des états traversés par le joueur
  std::vector<int> states;

  // Ajouter la position initiale à la liste des états
  states.push_back(current_state);

  // Tant que le joueur n'a pas atteint la sortie (dernière ligne de la matrice)
  while (current_state != 3) {
    // Générer un nombre aléatoire entre 0 et 1
    double random_number = generate_random_number();

    // Calculer la nouvelle position du joueur en fonction du nombre aléatoire
    double cumulative_prob = 0.0;
    int next_state = 0;

    for (int i = 0; i < 4; ++i) {
      cumulative_prob += transition_matrix[current_state][i];
      if (random_number <= cumulative_prob) {
        next_state = i;
        break;
      }
    }

    // Mettre à jour la position du joueur
    current_state = next_state;
    steps++;

    // Ajouter la nouvelle position à la liste des états
    states.push_back(current_state);
  }

  // Afficher les états traversés par le joueur
  std::cout << "Étapes traversées : ";
  for (int state : states) {
    std::cout
        << state + 1
        << " "; // Ajouter 1 pour correspondre aux pièces numérotées de 1 à 4
  }
  std::cout << std::endl;

  // Afficher le nombre d'états par lesquels le joueur est passé avant
  // d'atteindre la sortie
  // std::cout << "Nombre d'étapes nécessaires pour atteindre la sortie : " <<
  // steps << std::endl;

  return steps;
}