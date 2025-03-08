#include "dijkstras.h"

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous){
    //initialize all previous to null and distances to inf
    vector<int> distances(G.numVertices, INF);
    vector<bool> visited(G.numVertices, false);
    previous.resize(G.numVertices, -1);

    priority_queue<pair<int, int>, std::vector<pair<int, int>>, std::greater<pair<int, int>>> q;
    q.push({0, source});
    distances[source] = 0;

    while (!q.empty()){
        int node = q.top().second;
        q.pop();

        if (visited[node])
            continue;
        visited[node] = true;

        for (Edge e : G[node]){
            if (!visited[e.dst] && distances[node] + e.weight < distances[e.dst]){
                distances[e.dst] = distances[node] + e.weight;
                previous[e.dst] = node;
                q.push({distances[e.dst], e.dst});
            }
        }
    }
    return distances;
}
vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination){
    stack<int> stk;
    int cur = destination;
    stk.push(cur);
    while(distances[cur] > 0){
        stk.push(previous[cur]);
        cur = previous[cur];
    }
    vector<int> path;
    while (!stk.empty()){
        path.push_back(stk.top());
        stk.pop();
    }
    return path;
}
void print_path(const vector<int>& v, int total){
    for (int i : v){
        cout << i << ' ';
    }
    cout << endl << "Total cost is " << total << endl;
}