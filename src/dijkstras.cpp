#include "dijkstras.h"
#include <iostream>
#include <queue>

using namespace std;

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int V = G.numVertices;
    vector<int> distances(V, INF);
    previous.assign(V, -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    
    distances[source] = 0;
    pq.emplace(0, source);
    
    while (!pq.empty()) {
        int dist = pq.top().first;
        int u = pq.top().second;
        pq.pop();
        
        if (dist > distances[u]) continue; // Skip outdated distances
        
        for (const Edge& neighbor : G[u]) {
            int v = neighbor.dst;
            int weight = neighbor.weight;
            
            if (distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                previous[v] = u;
                pq.emplace(distances[v], v);
            }
        }
    }
    
    return distances;
}

vector<int> extract_shortest_path(const vector<int>& distances, const vector<int>& previous, int destination) {
    vector<int> path;
    for (int at = destination; at != -1; at = previous[at]) {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());
    return path;
}

void print_path(const vector<int>& path, int total) {
    if (path.empty()) {
        cout << "No path found." << endl;
        return;
    }

    for (size_t i = 0; i < path.size(); ++i) {
        // Add space only **between** numbers
        cout << path[i] << " ";
    }

    cout << "\nTotal cost is " << total << "\n";
}
