#include <bits/stdc++.h>

#include "graph.hpp"
#include "timer.hpp"

using namespace std;

Graph* readInput();
int objectiveFunction(const vector<int>& solution, Graph* graph);
pair<int, vector<int>> solveFurthestNeighbor(Graph* graph, const int n, mt19937& gen);

int getRandomInteger(int l, int r, mt19937& gen);
float getRandomFloat(mt19937& gen);

int main() {
	random_device rd;
	mt19937 gen(rd());

	string label = "Heuristica de Vizinho Mais Distante para o Problema do Caixeiro Viajante (TSP)";
	Timer timer(label);

	Graph* graph = readInput();
	const int n = graph->getNumVertices() - 1;

	// Nesta solução, assumimos que o grafo é completo
	auto [curr_fo, curr_solution] = solveFurthestNeighbor(graph, n, gen);
	
    cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
	cout << "         Heuristica de Vizinho Mais Distante       " << endl;
	cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
	cout << "- FO encontrada: " << curr_fo << endl;
	cout << "- Caminho encontrado: ";
	for (int i = 0; i < n; ++i) {
		cout << curr_solution[i] << ' ';
	}
	cout << curr_solution[0] << endl;
	timer.elapsed();
	cout << endl;

    // Criterio de parada 1: numero maximo de iteracoes
    int num_iterations = 300;

    // Criterio de parada 2: numero maximo de iteracoes sem melhora na melhor
    // solucao encontrada
    const int max_iterations_without_improvement = sqrt(num_iterations);

    vector<int> best_solution(n);
    copy(curr_solution.begin(), curr_solution.end(), best_solution.begin());
    int best_fo = curr_fo;

    int iterations_without_improvement = 0;

    // Vetor com a ordem de acesso das posicoes do vetor solucao
    vector<int> access_order(n);
    iota(access_order.begin(), access_order.end(), 0);

    // Loop principal
    while (num_iterations--){

        // Aplica o critério de parada por estagnação
        if(iterations_without_improvement >= max_iterations_without_improvement) {
            cout << "Criterio de parada por estagnacao acionado!" << endl << endl;
            break;
        }

        bool improvement = false;

        // Ordem de acesso aleatoria a cada iteracao
        shuffle(access_order.begin(), access_order.end(), gen);
        for (auto& v : access_order) {
            // Obtem um outro no aleatorio para fazer a troca (2-opt)
            int u;
            do {
                u = getRandomInteger(0, n - 1, gen);
            } while (u == v);

            swap(curr_solution[u], curr_solution[v]);
            int new_fo = objectiveFunction(curr_solution, graph);

            // Desfaz a mudanca caso a nova solucao seja inviavel
            if (new_fo < 0 and curr_fo >= 0) {
                swap(curr_solution[u], curr_solution[v]);
                continue;
            }
            curr_fo = new_fo;

            if (curr_fo < best_fo) {
                cout << "Solucao melhor encontrada: " << best_fo << endl;
                timer.elapsed();
                cout << endl;

                best_fo = curr_fo;
                copy(curr_solution.begin(), curr_solution.end(), best_solution.begin());
                improvement = true;
                break;
            }

            // 50% de chance de reverter a alteracao caso ela nao tenha gerado a
            // melhor solucao ate aqui
            float p_revert = getRandomFloat(gen);
            if (p_revert < 0.50) {
                swap(curr_solution[u], curr_solution[v]);
                curr_fo = objectiveFunction(curr_solution, graph);
            }
        }

        iterations_without_improvement = improvement ? 0 : iterations_without_improvement + 1;

        // Nao aplica o criterio de parada por estagnacao caso uma solucao
        // viavel ainda nao tenha sido encontrada
        if (best_fo < 0) iterations_without_improvement = 0;
    }
	timer.stop();
    cout << endl;

	cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
	cout << "         Problema do Caixeiro Viajante (TSP)       " << endl;
	cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=" << endl;
	cout << "- FO encontrada: " << best_fo << endl;
	cout << "- Caminho encontrado: ";
	for (int i = 0; i < n; ++i) {
		cout << best_solution[i] << ' ';
	}
	cout << best_solution[0] << endl;

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

	fo = objectiveFunction(solution, graph);
	return make_pair(fo, solution);
}

int objectiveFunction(const vector<int>& solution, Graph* graph) {
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

float getRandomFloat(mt19937& gen) {
        uniform_real_distribution<float> dis(0.0f, 1.0f);
        return dis(gen);
}
