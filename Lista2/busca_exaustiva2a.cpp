#include <bits/stdc++.h>
using namespace std;

void printSolution(vector<int> solution){
    cout << '\t';
    for(auto v : solution){
        cout << v << ' ';
    }
    cout << endl;
}

void allPermutations(vector<int> solution, int idx=0){
    if(idx == solution.size()){
        printSolution(solution);
        return;
    }

    allPermutations(solution, idx + 1);

    for(int i = idx+1; i < solution.size(); ++i){
        swap(solution[idx], solution[i]);
        allPermutations(solution, idx + 1);
        swap(solution[idx], solution[i]);
    }
    return;
}

int main(){
    int n;
    cout << "Digite o tamanho da permutacao (n): ";
    cin >> n;
    cout << endl;

    vector<int> solution (n);
    iota(solution.begin(), solution.end(), 1);

    allPermutations(solution);
    return 0;
}
