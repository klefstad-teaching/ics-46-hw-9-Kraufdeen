#include "dijkstras.h"

int main(int argc, char *argv[]){
    Graph g;
    string file_name = argv[1];
    file_to_graph(file_name, g);
    vector<int> prev;
    int source = 0;
    vector<int> sol = dijkstra_shortest_path(g, source, prev);
    for (int destination = 0; destination < g.numVertices; ++destination) {
        vector<int> path = extract_shortest_path(sol, prev, destination);
        print_path(path, sol[destination]);
        //cout << endl;
    }
    return 0;
}