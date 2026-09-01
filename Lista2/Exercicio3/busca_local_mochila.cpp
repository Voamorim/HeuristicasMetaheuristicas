#include "../Timer/timer.hpp"
#include <bits/stdc++.h>

using namespace std;

struct Item {
  int value, weight;
};

struct Backpack {
  vector<Item> items;
  int capacity;
};

vector<bool> randomInitialSolution(int n, mt19937 &gen);
int objectiveFunction(const vector<bool> solution, Backpack *backpack);

int getRandomInteger(int l, int r, mt19937 &gen);
float getRandomFloat(mt19937 &gen);

Backpack *readInput(void);

int main() {
  random_device rd;
  mt19937 gen(rd());

  string problema = "Heuristica para o Problema da Mochila";
  Timer timer(problema);

  // Criterio de Parada 1: Numero de interacoes
  int max_iterations = 100;

  // Criterio de Parada 2: Numero de iteracoes sem melhoria
  int max_iterations_without_improvement = sqrt(max_iterations);

  Backpack *backpack = readInput();

  int n = backpack->items.size();

  vector<bool> curr_solution = randomInitialSolution(n, gen);
  vector<bool> best_solution(n);
  copy(curr_solution.begin(), curr_solution.end(), best_solution.begin());

  int curr_fo = objectiveFunction(curr_solution, backpack);
  int best_fo = curr_fo;

  int iterations_without_improvement;

  // Vetor com a ordem de acesso das posicoes do vetor solucao
  vector<int> access_order(n);
  iota(access_order.begin(), access_order.end(), 0);

  // Loop principal
  while (max_iterations-- &&
         iterations_without_improvement < max_iterations_without_improvement) {
    bool improvement = false;

    shuffle(access_order.begin(), access_order.end(), gen);

    // Percorre pela vizinhanca aplicando o operador de vizinhanca (flip)
    for (auto i : access_order) {

      bool unfeasible = false;

      // Caso a solucao atual seja inviavel, obrigatoriamente seta o bit para 0
      if (curr_fo < 0) {
        curr_solution[i] = false;
        unfeasible = true;
      } else {
        curr_solution[i] = curr_solution[i] ^ true; // flip
      }

      // Verifica se a nova solucao e melhor
      curr_fo = objectiveFunction(curr_solution, backpack);

      if (unfeasible) {
        if (curr_fo > best_fo) {
          best_fo = curr_fo;
          copy(curr_solution.begin(), curr_solution.end(),
               best_solution.begin());
        }
        continue;
      }

      // Politica de melhoria: First Improvement
      if (curr_fo > best_fo) {
        best_fo = curr_fo;
        copy(curr_solution.begin(), curr_solution.end(), best_solution.begin());
        improvement = true;
        break;
      }

      curr_solution[i] = curr_solution[i] ^ true; // reverte o flip
    }

    iterations_without_improvement =
        improvement ? 0 : iterations_without_improvement + 1;

    // Nao aplica o criterio de parada caso uma solucao viavel ainda nao
    // tenha sido encontrada
    if (best_fo < 0)
      iterations_without_improvement = 0;
  }

  timer.stop();
  cout << endl;

  cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
  cout << "               Problema da Mochila                 " << endl;
  cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
  cout << "- Melhor FO encontrada: " << best_fo << endl;
  cout << "- Itens escolhidos: ";
  for (int i = 0; i < n; ++i) {
    if (best_solution[i])
      cout << i << ' ';
  }
  cout << endl;

  free(backpack);
  return 0;
}

Backpack *readInput(void) {
  Backpack *backpack = new Backpack();

  int n, m;
  cin >> n >> m;

  backpack->capacity = m;

  for (int i = 0; i < n; ++i) {
    int value, weight;
    cin >> value >> weight;

    Item item = {value, weight};
    backpack->items.push_back(item);
  }

  return backpack;
}

int objectiveFunction(vector<bool> solution, Backpack *backpack) {
  const int n = solution.size();

  int total_value = 0;
  int total_weight = 0;

  for (int i = 0; i < n; ++i) {
    if (solution[i]) {
      total_value += backpack->items[i].value;
      total_weight += backpack->items[i].weight;
    }
  }

  if (total_weight <= backpack->capacity)
    return total_value;

  return -1000000; // Penaliza solucoes invalidas
}

vector<bool> randomInitialSolution(int n, mt19937 &gen) {
  vector<bool> solution(n);
  for (int i = 0; i < n; ++i) {
    solution[i] = getRandomInteger(0, 1, gen);
  }
  return solution;
}

float getRandomFloat(mt19937 &gen) {
  uniform_real_distribution<float> dis(0.0f, 1.0f);
  return dis(gen);
}

int getRandomInteger(int l, int r, mt19937 &gen) {
  uniform_int_distribution<int> dis(l, r);
  return dis(gen);
}
