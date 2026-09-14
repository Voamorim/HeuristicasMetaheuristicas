#include <bits/stdc++.h>

#include "graph.hpp"
#include "timer.hpp"

using namespace std;

Graph* readInput();
int objetiveFunction(const vector<int>& solution, Graph* graph);
pair<int, vector<int>> solveFurthestNeighbor(Graph* graph, const int n, mt19937& gen);

int getRandomInteger(int l, int r, mt19937& gen);

int main() {
	random_device rd;
	mt19937 gen(rd());

	string label = "Heuristica de Vizinho Mais Distante para o Problema do Caixeiro Viajante (TSP)";
	Timer timer(label);

	Graph* graph = readInput();
	const int n = graph->getNumVertices() - 1;

	// Nesta solução, assumimos que o grafo é completo
	auto [fo, solution] = solveFurthestNeighbor(graph, n, gen);

	timer.stop();
	cout << endl;

	cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
	cout << "         Problema do Caixeiro Viajante (TSP)       " << endl;
	cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
	cout << "- FO encontrada: " << fo << endl;
	cout << "- Caminho encontrado: ";
	for (int i = 0; i < n; ++i) {
		cout << solution[i] << ' ';
	}
	cout << solution[0] << endl;

	delete graph;
	return 0;
}

pair<int, vector<int>> solveFurthestNeighbor(Graph* graph, const int n, mt19937& gen) {
	vector<int> solution(n);
	int fo = 0;

	int starting_node = getRandomInteger(1, n, gen);
	solution[0] = starting_node;

	set<int> unvisited_nodes;
	for (int i = 1; i <= n; ++i) {
		if (i != starting_node) {
			unvisited_nodes.insert(i);
		}
	}

	for (int i = 1; i < n; ++i) {
		int v = solution[i - 1];

		int furthest_unvisited_node = -1;
		int furthest_unvisited_node_dist = INT_MIN;

		for (auto& u : unvisited_nodes) {
			int w = graph->getEdge(v, u);

			if (w > furthest_unvisited_node_dist) {
				furthest_unvisited_node_dist = w;
				furthest_unvisited_node = u;
			}
		}

		unvisited_nodes.erase(furthest_unvisited_node);

		solution[i] = furthest_unvisited_node;
	}

	fo = objetiveFunction(solution, graph);
	return make_pair(fo, solution);
}

int objetiveFunction(const vector<int>& solution, Graph* graph) {
	int fo = 0;
	int v = solution[0];

	for (int u = 1; u < solution.size(); ++u) {
		int w = graph->getEdge(v, solution[u]);

		// Punicao para solucoes que usam arestas inexistentes no grafo (solucoes
		// inviaveis)
		if (w == -1) {
			return -100000;
		}

		fo += w;
		v = solution[u];
	}
	int w = graph->getEdge(solution[solution.size() - 1], solution[0]);

	// Punicao para solucoes que usam arestas inexistentes no grafo (solucoes
	// inviaveis)
	if (w == -1) {
		return -100000;
	}

	fo += w;
	return fo;
}

Graph* readInput() {
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

int getRandomInteger(int l, int r, mt19937& gen) {
	uniform_int_distribution<int> dis(l, r);
	return dis(gen);
}
