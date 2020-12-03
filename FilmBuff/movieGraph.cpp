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

void movieGraph::bfs(string src) const {
    queue<string> q;
    set<string> visited;

    q.push(src);
    visited.insert(src);

    while (!q.empty()) {
        string temp = q.front();
        cout << temp << " ";
        q.pop();

        for (pair<string, int> n : this->graph.at(temp)) {
            if (visited.find(n.first) == visited.end()) {
                visited.insert(n.first);
                q.push(n.first);
            }
        }
    }
}

void movieGraph::dfs(string src) const {
    stack<string> s;
    set<string> visited;

    s.push(src);
    visited.insert(src);

    while (!s.empty()) {
        string temp = s.top();
        cout << temp << " ";
        s.pop();

        for (pair<string, int> n : this->graph.at(temp)) {

            if (visited.find(n.first) == visited.end()) {
                visited.insert(n.first);
                s.push(n.first);
            }
        }
    }
}