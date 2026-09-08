#include <bits/stdc++.h>

#include "../../Timer/timer.hpp"

using namespace std;

void printSolution(const vector<int> &solution);
int allPermutations(vector<int> solution, int idx = 0);

int main() {
	int n;
	cout << "Digite o tamanho da permutacao (n): ";
	cin >> n;
	cout << endl;

	string label = "Busca Exaustiva para o problema TSP";
	Timer timer(label);

	vector<int> solution(n);
	iota(solution.begin(), solution.end(), 1);

	cout << "Todas as permutacoes possiveis: " << endl;
	int ans = allPermutations(solution);
	cout << "Total de permutacoes: " << ans << endl;

	timer.stop();
	return 0;
}

void printSolution(const vector<int> &solution) {
	cout << '\t';
	for (auto v : solution) {
		cout << v << ' ';
	}
	cout << endl;
}

int allPermutations(vector<int> solution, int idx) {
	if (idx == solution.size()) {
		printSolution(solution);
		return 1;
	}

	int ans = 0;

	ans += allPermutations(solution, idx + 1);

	for (int i = idx + 1; i < solution.size(); ++i) {
		swap(solution[idx], solution[i]);
		ans += allPermutations(solution, idx + 1);
		swap(solution[idx], solution[i]);
	}
	return ans;
}
