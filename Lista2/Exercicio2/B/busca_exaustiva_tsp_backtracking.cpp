#include <bits/stdc++.h>
#include <bits/types/timer_t.h>

#include "../../Graph/graph.hpp"
#include "../../Timer/timer.hpp"

using namespace std;

void printSolution(const vector<int>& solution);
int allPermutations(Graph* graph, vector<int> solution, int idx = 0);

Graph* readGraphAdjMatrix();
Graph* readGraphPoints();

int main() {
	Graph* graph = readGraphAdjMatrix();
	const int n = graph->getNumVertices() - 1;

	string label =
		"Busca Exaustiva por todas as permutacoes possiveis para o TSP (com Backtracking)";
	Timer timer(label);

	vector<int> solution(n);
	iota(solution.begin(), solution.end(), 1);

	cout << "Todas as permutacoes possiveis: " << endl;
	int ans = allPermutations(graph, solution);
	cout << "Total de permutacoes: " << ans << endl;

	timer.stop();
	delete graph;
	return 0;
}

Graph* readGraphAdjMatrix() {
    int n, m; cin >> n >> m; 
    Graph* graph = new Graph(n+1);
    
    for(int i = 0; i < m; ++i){
        int a, b, c; cin >> a >> b >> c;

        graph->setEdge(a, b, c);
        graph->setEdge(b, a, c);
    } 

    // Existe aresta do vertice para ele mesmo
    for(int i = 0; i < graph->getNumVertices(); ++i){
        graph->setEdge(i, i, 0);
    }

    return graph;
}

Graph* readGraphPoints() {
	int n;
	cin >> n;

	vector<tuple<int, int>> points;
	for (int i = 0; i < n; ++i) {
		int a, b, c;
		cin >> a >> b >> c;

		points.push_back(make_tuple(b, c));
	}

	Graph* graph = new Graph(n + 1);
	for (int i = 0; i < n; ++i) {
		for (int j = i + 1; j < n; ++j) {
			int v = i + 1, u = j + 1;

			int xvar = get<0>(points[i]) - get<0>(points[j]);
			int yvar = get<1>(points[i]) - get<1>(points[j]);
			int dist = round(sqrt((double)pow(xvar, 2) + pow(yvar, 2)));

			graph->setEdge(v, u, dist);
			graph->setEdge(u, v, dist);
			graph->setEdge(v, v, 0);
		}
	}

	return graph;
}

void printSolution(const vector<int>& solution){
	cout << '\t';
	for (auto v : solution) {
		cout << v << ' ';
	}
	cout << endl;
}

int allPermutations(Graph* graph, vector<int> solution, int idx) {
	if (idx == solution.size()) {

        // Verifica se existe aresta do ultimo vertice para o vertice inicial
        if(graph->getEdge(solution[idx-1], solution[0]) == -1) 
            return 0;
            
		printSolution(solution);
		return 1;
	}
    
	const int n = graph->getNumVertices() - 1;
	int ans = 0;

	int prev_idx = idx - 1;

	// Não troca nada
	if (prev_idx == -1 or graph->getEdge(solution[prev_idx], solution[idx]) != -1) {
		ans += allPermutations(graph, solution, idx + 1);
	} 

	for (int i = idx + 1; i < solution.size(); ++i) {
		int prev_i = i - 1;
		prev_i = prev_i >= 0 ? prev_i : n - 1;

		// Verifica se trocar os vertices de posicao geraria uma solucao invalida
		if (prev_idx != -1 and graph->getEdge(solution[prev_idx], solution[i]) == -1) {
			continue;
		}

        swap(solution[idx], solution[i]);
		ans += allPermutations(graph, solution, idx + 1);
		swap(solution[idx], solution[i]);
	}
	return ans;
}
