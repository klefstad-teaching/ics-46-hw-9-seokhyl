#include "dijkstras.h"

int main() {
    // ifstream in("./src/small.txt");
    // Graph G;
    // in >> G;
    // in.close();
    // // vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous);
    // vector<int> previous;
    // vector<int> distance = dijkstra_shortest_path(G, 0, previous);

    // for (int e : distance)
    //     cout << e << ' ';
    // cout<<endl;

    // for (int i = 0; i < 4; ++i) {
    //     vector<int> path = extract_shortest_path(distance, previous, i);
    //         for (int e : path)
    //             cout << e << ' ';
    //         cout<<endl;
    // }

    Graph G;
    file_to_graph("./src/medium.txt", G);
    vector<int> previous;
    vector<int> distance = dijkstra_shortest_path(G, 0, previous);
    for (int i = 0; i < G.numVertices; ++i) {
        print_path(extract_shortest_path(distance, previous, i), distance[i]);
    }
}