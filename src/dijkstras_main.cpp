#include "dijkstras.h"

int main(int argc, char* argv[]){
    Graph G;
    if (argc > 1)
        file_to_graph(argv[1], G);
    else
        file_to_graph("src/small.txt", G);
    cout << "Source: ";
    int source;
    cin >> source;

    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(G, source, previous);
    for (int i = 0; i < G.numVertices; ++i){
        vector<int> path = extract_shortest_path(distances, previous, i);
        print_path(path, distances[i]);
    }
    
    return 0;
}