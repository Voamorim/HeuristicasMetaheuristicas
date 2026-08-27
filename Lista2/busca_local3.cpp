#include <bits/stdc++.h>
using namespace std; 

struct Item {
    int value, weight;
};

struct Backpack {
    vector<Item> items;
    int capacity;
};

vector<bool> randomInitialSolution(int n);
int objectiveFunction(const vector<bool> solution, const Backpack &backpack);

int getRandomInteger(int l, int r, mt19937& gen);
float getRandomFloat(mt19937& gen);

int main(){
    random_device rd;
    mt19937 gen(rd());

    // Criterio de Parada 1: Numero de interacoes
    const int num_iterations = 100;

    // Criterio de Parada 2: Numero de iteracoes sem melhoria
    const int num_iterations_without_improvement = sqrt(num_iterations);

    vector<bool> solution = randomInitialSolution(n);

    // Loop principal
    while(num_iterations--){
        
    }

    return 0;
}

int objectiveFunction(vector<bool> solution, vector<Item> backpack){
    const int n = solution.size();
   
    int total_value = 0;
    int total_weight = 0;

    for(int i = 0; i < n; ++i){
        if(solution[i]){
            total_value += backpack.items[i].value;
            total_weight += backpack.items[i].weight;
        }
    }

    if(total_weight <= backpack.capacity) 
        return total_value;

    return -1000000; // Penaliza solucoes invalidas
}

vector<bool> randomInitialSolution(int n, mt19937& gen){
    vector<bool> solution (n);
    for(auto &bit : solution){
        bit = getRandomInteger(0, 1, gen);
    }
    return solution;
}

float getRandomFloat(mt19937& gen){
    uniform_real_distribution<float> dis(0.0f, 1.0f);
    return dis(gen);
}

int getRandomInteger(int l, int r, mt19937& gen){
    uniform_int_distribution<int> dis(l, r);
    return dis(gen);
}
