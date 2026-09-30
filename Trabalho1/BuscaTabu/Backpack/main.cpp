#include <algorithm>
#include <climits>
#include <cmath>
#include <iostream>
#include <vector>

#include "backpack.hpp"
#include "bt_backpack.hpp"
#include "timer.hpp"

using namespace std;

void printSolution(const vector<bool>& solution, const long long fo);

int main() {
    string label = "Busca Tabu para o o Problema da Mochila 0/1";
    Timer timer(label);

    // Le o problema da entrada
    Backpack* backpack = readInputBackpack();

    // Solucao inicial gulosa
    auto [fo, solution] = greedySolutionBackpack(backpack);

    // Busca Tabu
    auto [best_fo, best_solution] = tabuSearchBackpack(solution, fo, backpack, timer);

    // Imprime solucao encontrada e tempo gasto
    timer.stop();
    cout << endl;
    string title = "Busca Tabu para Mochila 0/1";
    printSolutionBackpack(best_solution, best_fo, title);

    delete backpack;
    return 0;
}
