#ifndef MOVIE_GRAPH_HEADER
#define MOVIE_GRAPH_HEADER

#include <unordered_map>
#include <set>
#include <queue>
#include <stack>
#include <iostream>
using namespace std;

class movieGraph
{
private:

public:
    unordered_map<string, set<pair<string, int>>> graph;

    movieGraph();
    void insertEdge(string from, string to, int weight);
    void insertVertex(string from);
    int getWeight(string from, string to);
    set<pair<string, int>> getAdjacent(string vertex);
    void bfs(string src) const;
    void dfs(string src) const;
};

#endif