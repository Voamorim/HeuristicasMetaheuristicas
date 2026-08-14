#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

const string INPUT_FILE_NAME = "Input/input1.txt";



tuple<vector<vector<int>>, int, int> readGraphAdjMatrix(const string input_file_name){
    ifstream input_file(input_file_name);
   
    int n, m;
    input_file >> n >> m;

    vector<vector<int>> graph (n, vector<int> (n, 0));

    for(int edge = 0; edge < m; ++edge){
        int v, u, w; 
        input_file >> v >> u >> w;
        v-=1, u-=1;

        graph[v][u] = w;
        graph[u][v] = w;
    }

    input_file.close();
    return make_tuple(graph, n, m);
}

tuple<vector<vector<pair<int, int>>>, int, int> readGraphAdjList(const string input_file_name){
    ifstream input_file(input_file_name);
    
    int n, m;
    input_file >> n >> m;

    vector<vector<pair<int, int>>> graph (n);

    for(int edge = 0; edge < m; ++ edge){
        int v, u, w;
        input_file >> v >> u >> w;
        v-=1, u-=1;

        graph[v].push_back(make_pair(u, w));
        graph[u].push_back(make_pair(v, w));
    }

    input_file.close();
    return make_tuple(graph, n, m);
}

int main(){
    auto [graph_adj_matrix, n1, m1] = readGraphAdjMatrix(INPUT_FILE_NAME);
    auto [graph_adj_list, n2, m2] = readGraphAdjList(INPUT_FILE_NAME);    

    // Imprime o grafo formado com matriz de adjacencias
    cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
    cout << "       Grafo em Matriz de Adjacencias       " << endl;
    cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl << endl;

    cout << "Numero de vertices: " << n1 << endl;
    cout << "Numero de arestas: " << m1 << endl;
    cout << endl;
   
    cout << "Grafo: " << endl;
    for(int i = 0; i < n1; ++i){
        for(int j = 0; j < n1; ++j){
            cout << graph_adj_matrix[i][j] << ' ';
        }
        cout << endl;
    }

    cout << endl;
    
    // Imprime o grafo formado com lista de adjacencias
    cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl;
    cout << "       Grafo em Lista de Adjacencias        " << endl;
    cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-" << endl << endl;

    cout << "Numero de vertices: " << n2 << endl;
    cout << "Numero de arestas: " << m2 << endl;
    cout << endl;
    
    cout << "Grafo: " << endl;
    for(int i = 0; i < n2; ++i){
        cout << i << ": ";
        for(auto &[dest, w] : graph_adj_list[i]){
            cout << "{" << dest << ", " << w << "} ";
        }
        cout << endl;
    }
    cout << endl;

    return 0;
}
