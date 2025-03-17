
#include "dijkstras.h"

// returns a list of minimum cost from the source to the vertex.
// previous stores the previous vertex at the entry of a vertex.
vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int n = G.size();
    vector<int> distance(n, INF);
    previous = vector<int>(n, -1);
    vector<bool> visited(n, false);

    auto cmp = [&distance](const Node& a, const Node& b){return distance[a.v] > distance[b.v];};
    priority_queue<Node, vector<Node>, decltype(cmp)> pq(cmp);
    pq.push(Node{source, 0});
    distance[source] = 0;
    
    while(!pq.empty()) {
        Node curNode = pq.top(); pq.pop();
        Vertex curVertex = curNode.v;
        if (visited[curVertex]) continue;
        visited[curVertex] = true;

        for (Edge e : G[curVertex]) {
            if (!visited[e.dst] && distance[curVertex] + e.weight < distance[e.dst]) {
                distance[e.dst] = distance[curVertex] + e.weight;
                previous[e.dst] = curVertex;
                pq.push(Node{e.dst, distance[e.dst]});
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
