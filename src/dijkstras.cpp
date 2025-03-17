
#include "dijkstras.h"

struct CmpEdges {
    bool operator()(const Edge& a, const Edge& b) {
        return a.weight < b.weight;
    }
};

// returns a list of minimum cost from the source to the vertex.
// previous stores the previous vertex at the entry of a vertex.
vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int n = G.size();
    vector<int> distance(n, INF);
    previous = vector<int>(n, -1);
    vector<bool> visited(n, false);

    Vertex cur = source;
    distance[cur] = 0;

    priority_queue<Edge, vector<Edge>, CmpEdges> pq;
    for (Edge e : G[cur]) {
        pq.push(e);
        distance[e.dst] = e.weight;
        previous[e.dst] = cur;
    }
    visited[cur] = true;

    while(!pq.empty()) {
        Vertex cur = pq.top().dst; pq.pop();
        if (visited[cur]) continue;

        visited[cur] = true;
        for (Edge e : G[cur]) {
            if (!visited[e.dst] && distance[cur] + e.weight < distance[e.dst]) {
                distance[e.dst] = distance[cur] + e.weight;
                previous[e.dst] = cur;
                pq.push(e);
            }
        }
    }

    return distance;
}

// return a list of vertexes that forms the least cost path from the source to the destination.
vector<int> extract_shortest_path(const vector<int>& /*distances*/, const vector<int>& previous, int destination){
    vector<Vertex> shortestPath{destination};
    Vertex cur = destination;

    while(previous[cur] != -1) {
        shortestPath.insert(shortestPath.begin(), previous[cur]);
        cur = previous[cur];
    }

    return shortestPath;
}

// print ({path} (\n) Total cost is {leastCost} (\n))
void print_path(const vector<int>& v, int total){
    for (Vertex e : v) 
        cout << e << ' ';
    cout << endl;
    cout << "Total cost is " << total << endl;
}
