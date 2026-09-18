#include <algorithm>
#include <cmath>
#include <iostream>
#include <numeric>
#include <random>
#include <string>
#include <utility>
#include <vector>

#include "timer.hpp"

using namespace std;

struct Item {
    int value, weight;
};

struct Backpack {
    vector<Item> items;
    int capacity;
};

Backpack* readInput(void);
int objectiveFunction(const vector<bool> solution, Backpack* backpack);

pair<int, vector<bool>> costBenefitSolution(Backpack* backpack);
bool compItemsCostBenefit(const pair<Item, int>& item1, const pair<Item, int>& item2);

int getRandomInteger(int l, int r, mt19937& gen);
float getRandomFloat(mt19937& gen);

int main() {
    random_device rd;
    mt19937 gen(rd());

    string problema =
        "Solucao Gulosa por Custo Beneficio + Heuristica para o Problema da Mochila 0/1";
    Timer timer(problema);

    // Criterio de Parada 1: Numero de interacoes
    int max_iterations = 1000;

    // Criterio de Parada 2: Numero de iteracoes sem melhoria
    int max_iterations_without_improvement = sqrt(max_iterations);

    Backpack* backpack = readInput();
    int n = backpack->items.size();

    auto [curr_fo, curr_solution] = costBenefitSolution(backpack);
    int best_fo = curr_fo;

    cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
    cout << "               Heuristica por Custo Beneficio" << endl;
    cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
    cout << "- Funcao objetivo encontrada: " << curr_fo << endl;
    cout << "- Itens selecionados: ";
    for (int i = 0; i < curr_solution.size(); ++i) {
        if (not curr_solution[i]) continue;
        cout << i << ' ';
    }
    cout << endl << endl;
    timer.elapsed();
    cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
    cout << endl;

    vector<bool> best_solution(n);
    copy(curr_solution.begin(), curr_solution.end(), best_solution.begin());

    int iterations_without_improvement = 0;

    // Vetor com a ordem de acesso das posicoes do vetor solucao
    vector<int> access_order(n);
    iota(access_order.begin(), access_order.end(), 0);

    // Loop principal
    while (max_iterations--) {
        // Aplica o critério de parada por estagnação
        if (iterations_without_improvement >= max_iterations_without_improvement) {
            cout << "Criterio de parada por estagnacao acionado!" << endl << endl;
            break;
        }

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
                curr_solution[i] = curr_solution[i] ^ true;  // flip
            }

            // Verifica se a nova solucao e melhor
            curr_fo = objectiveFunction(curr_solution, backpack);

            if (unfeasible) {
                if (curr_fo > best_fo) {
                    best_fo = curr_fo;
                    copy(curr_solution.begin(), curr_solution.end(), best_solution.begin());
                }
                continue;
            }

            // Politica de melhoria: First Improvement
            if (curr_fo > best_fo) {
                best_fo = curr_fo;
                copy(curr_solution.begin(), curr_solution.end(), best_solution.begin());
                improvement = true;

                cout << "Solucao melhor encontrada: " << best_fo << endl;
                timer.elapsed();
                cout << endl;

                break;
            }

            curr_solution[i] = curr_solution[i] ^ true;  // reverte o flip
        }

        iterations_without_improvement = improvement ? 0 : iterations_without_improvement + 1;

        // Nao aplica o criterio de parada caso uma solucao viavel ainda nao
        // tenha sido encontrada
        if (best_fo < 0) iterations_without_improvement = 0;
    }

    timer.stop();
    cout << endl;

    cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
    cout << "               Problema da Mochila                 " << endl;
    cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
    cout << "- Melhor FO encontrada: " << best_fo << endl;
    cout << "- Itens escolhidos: ";
    for (int i = 0; i < n; ++i) {
        if (best_solution[i]) cout << i << ' ';
    }
    cout << endl;

    delete backpack;
    return 0;
}

pair<int, vector<bool>> costBenefitSolution(Backpack* backpack) {
    vector<pair<Item, int>> sorted_items_costbenefit(backpack->items.size());
    for (int i = 0; i < backpack->items.size(); ++i) {
        auto& item = sorted_items_costbenefit[i];
        item.first = backpack->items[i];
        item.second = i;
    }

    sort(sorted_items_costbenefit.begin(), sorted_items_costbenefit.end(), compItemsCostBenefit);

    int curr_capacity = backpack->capacity;
    int solution = 0;

    vector<bool> selected_items(backpack->items.size(), false);

    // Pega os itens de maior custo benefício que ainda cabem na mochila
    for (int i = 0; i < backpack->items.size(); ++i) {
        auto& item = sorted_items_costbenefit[i];

        if (item.first.weight <= curr_capacity) {
            curr_capacity -= item.first.weight;
            solution += item.first.value;
            selected_items[item.second] = true;
        }
    }

    return make_pair(objectiveFunction(selected_items, backpack), selected_items);
}

Backpack* readInput(void) {
    Backpack* backpack = new Backpack();
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

int objectiveFunction(vector<bool> solution, Backpack* backpack) {
    const int n = solution.size();

    int total_value = 0;
    int total_weight = 0;

    for (int i = 0; i < n; ++i) {
        if (solution[i]) {
            total_value += backpack->items[i].value;
            total_weight += backpack->items[i].weight;
        }
    }

    if (total_weight <= backpack->capacity) return total_value;

    return -100 * (total_weight - backpack->capacity);  // Penaliza solucoes invalidas
}

bool compItemsCostBenefit(const pair<Item, int>& item1, const pair<Item, int>& item2) {
    double costbenefit_item1 = (double)item1.first.value / item1.first.weight;
    double costbenefit_item2 = (double)item2.first.value / item2.first.weight;

    return costbenefit_item1 > costbenefit_item2;
}

float getRandomFloat(mt19937& gen) {
    uniform_real_distribution<float> dis(0.0f, 1.0f);
    return dis(gen);
}

int getRandomInteger(int l, int r, mt19937& gen) {
    uniform_int_distribution<int> dis(l, r);
    return dis(gen);
}
