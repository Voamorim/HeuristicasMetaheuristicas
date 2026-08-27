#include <bits/stdc++.h>
using namespace std;

void printSolution(const vector<bool> &solution);
int allPossibilities(vector<bool> solution, int idx);

int main(){
    int n;
    cout << "Digite o tamanho da string binaria: ";
    cin >> n;

    vector<bool> bin_string (n, false);

    cout << endl;
    cout << "Todas as strings binarias de tamanho " << n << ": " << endl;

    int ans = allPossibilities(bin_string, 0);

    cout << "Total de possibilidades: " << ans << endl; 

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

int allPossibilities(vector<bool> solution, int idx=0){
    if(idx == solution.size()){
        printSolution(solution);
        return 1;
    }

    int ans = 0;
    ans += allPossibilities(solution, idx+1);
    solution[idx] = true;
    ans += allPossibilities(solution, idx+1);
    return ans;
}
