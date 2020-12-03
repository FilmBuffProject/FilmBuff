#include "movieGraph.h"

movieGraph::movieGraph() {

}

void movieGraph::insertEdge(string from, string to, int weight) {
    graph[from].insert(make_pair(to, weight));
    graph[to].insert(make_pair(from, weight));
}

void movieGraph::insertVertex(string from) {
    graph[from] = {};
}

int movieGraph::getWeight(string from, string to) {
    int weight;
    set<pair<string, int>> edges = graph[from];

    for (pair<string, int> p : edges) {
        if (p.first == to) {
            weight = p.second;
            break;
        }
    }

    return weight;
}

set<pair<string, int>> movieGraph::getAdjacent(string vertex) {
    return graph[vertex];
}