#include "dijkstras.h"
#include <unordered_set>
vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous){
    int n = G.numVertices;
    vector<int> distances(n,INF);
    vector<bool> visited(n, false);
    distances[source] = 0;
    previous.resize(n, -1);
    priority_queue<pair<int,int>, vector<pair<int,int>>,greater<pair<int,int>>> minHeap;
    minHeap.push({0,source});
    while(!minHeap.empty()){
        int u = minHeap.top().second;
        minHeap.pop();
        if(visited[u]) continue;
        visited[u] = 1;
        for (Edge edge : G[u]){
            int v = edge.dst;
            int weight = edge.weight;
            if (!visited[v] && distances[u] + weight < distances[v]){
                distances[v] = distances[u] + weight;
                previous[v] = u;
                minHeap.push({distances[v],v});
            }
        }
    }
    return distances;
}
vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination){
    vector<int> ret_path;
    if (destination < 0 || destination >= distances.size() || distances[destination] == INF) {
        return ret_path;
    }
    unordered_set<int> visited_nodes;
    for (int v = destination; v != -1; v = previous[v]) {
        if (visited_nodes.count(v)) {
            return {};
        }
        visited_nodes.insert(v);
        ret_path.push_back(v);
    }
    reverse(ret_path.begin(),ret_path.end());
    return ret_path;
}

void print_path(const vector<int>& v, int total){
    for (size_t i = 0; i < v.size(); ++i) {
        cout << v[i] << " ";
    }
    cout << endl;
    cout << "Total cost is " << total << endl;
}