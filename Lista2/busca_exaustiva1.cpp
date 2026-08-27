#include <bits/stdc++.h>
using namespace std;

void printSolution(const vector<bool> &solution);
void allPossibilities(vector<bool> solution, int idx);

int main(){
    int n;
    cout << "Digite o tamanho da string binaria: ";
    cin >> n;

    vector<bool> bin_string (n, false);

    cout << endl;
    cout << "Todas as strings binarias de tamanho " << n << ": " << endl;

    allPossibilities(bin_string, 0);

    return 0;
}

void printSolution(const vector<bool> &solution){
    cout << '\t';
    for(auto bit : solution){
        if(bit) cout << 1;
        else cout << 0;
    }
    cout << endl;
}

void allPossibilities(vector<bool> solution, int idx=0){
    if(idx == solution.size()){
        printSolution(solution);
        return;
    }

    allPossibilities(solution, idx+1);
    solution[idx] = true;
    allPossibilities(solution, idx+1);

    return;
}
