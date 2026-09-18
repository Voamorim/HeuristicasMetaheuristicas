#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <vector>

using namespace std;

class Graph {
   private:
    vector<vector<int>> G;
    int n;

   public:
    void initGraph(const int n);
    void resetGraph(void);

    void readGraph(ifstream& input_file);

    int getEdge(const int src, const int dest) const;
    void setEdge(const int src, const int dest, const int cost);
    void incrementEdge(const int src, const int dest, const int increment);

    int getNumVertices() const;

    Graph();
    Graph(const int num_vertices);
};

#endif
