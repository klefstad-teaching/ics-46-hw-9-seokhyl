
#include "dijkstras.h"

struct CmpNodes {
    bool operator()(const Node& a, const Node& b) {
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

    priority_queue<Node, vector<Node>, CmpNodes> pq;
    pq.push(Node{cur, 0});
    // for (Edge e : G[cur]) {
    //     pq.push(e);
    //     distance[e.dst] = e.weight;
    //     previous[e.dst] = cur;
    // }
    // visited[cur] = true;

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
