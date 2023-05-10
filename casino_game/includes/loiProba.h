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

///////////////LOI NORMALE////////////////////

double normal_distribution(double a, double b, double mu, double sigma) {
  double u1, u2, z;
  do {
    u1 = generate_random_number();
    u2 = generate_random_number();
    z = sqrt(-2 * log(u1)) * cos(2 * M_PI * u2);
  } while (z < a || z > b);
  return mu + sigma * z;
}

///////////////LOI UNIFORME///////////////////

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

/////////////////////// Loi de Poisson /////////////////////////

int poisson(double lambda) {
  double L = exp(-lambda);
  double p = 1.0;
  int k = 0;
  do {
    k++;
    p *= generate_random_number();
  } while (p > L);
  return k - 1;
}

/////////////////////// Loi exponentielle /////////////////////////

// Fonction qui simule une variable aléatoire suivant une loi exponentielle de
// paramètre lambda
double exponentielle(double lambda) {
  double u = generate_random_number();
  return -log(1 - u) / lambda;
}

/////////////////////// Loi de student /////////////////////////

double student_t_distribution(int degrees_of_freedom) {
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

  // Simulation de 10 nombres aléatoires suivant une loi de Poisson avec un
  // lambda de 5
  std::cout << "[ Loi de Poisson avec un lambda de 5 ]" << std::endl;
  for (int i = 0; i < 10; i++) {
    std::cout << poisson(5) << std::endl;
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
    std::cout << student_t_distribution(degrees_of_freedom) << std::endl;
  }

  std::cout << "[END]" << std::endl;
}