#include "graph.hpp"

#include <bits/stdc++.h>

using namespace std;

Graph::Graph() {}

Graph::Graph(const int num_vertices)
    : G(num_vertices, vector<double>(num_vertices, -1.0)), n(num_vertices) {}

void Graph::initGraph(const int _n) {
    n = _n;
    G.assign(n, vector<double>(n, -1.0));
}

void Graph::resetGraph(void) {
    for (auto& row : G) fill(row.begin(), row.end(), -1.0);
}

double Graph::getEdge(const int src, const int dest) const {
    if (src < 0 or dest < 0 or src > n or dest > n) {
        cerr << "graph.cpp: Erro ao obter o valor da aresta entre " << src << " e " << dest
             << " em getEdge(). Esta aresta nao existe no " << "Grafo." << endl;
        exit(1);
    }
    return G[src][dest];
}

void Graph::setEdge(const int src, const int dest, const double cost) {
    if (src < 0 or dest < 0 or src > n or dest > n) {
        cerr << "graph.cpp: Erro ao atribuir valor a aresta entre " << src << " e " << dest
             << " em setEdge()" << ". Esta aresta nao existe" << " no Grafo." << endl;
        exit(1);
    }
    G[src][dest] = cost;
}

void Graph::incrementEdge(const int src, const int dest, const double increment) {
    if (src < 0 or dest < 0 or src > n or dest > n) {
        cerr << "graph.cpp: Erro ao incrementar aresta entre " << src << " e " << dest
             << " em incrementEdge()" << ". Esta aresta nao " << "existe no Grafo." << endl;
        exit(1);
    }
    G[src][dest] += increment;
}

int Graph::getNumVertices() const { return n; }
