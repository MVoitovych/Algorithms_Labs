#include <iostream>
#include <vector>
#include <map>
#include <set>

using namespace ::std;

void recursive_queue(map<string, vector<string>> graph, string last_major_doc, set<string> &visited) {
    for (string next_doc: graph[last_major_doc]) {
        recursive_queue(graph, next_doc, visited);
    }
    if (!visited.count(last_major_doc))
        cout << last_major_doc << endl;

    visited.insert(last_major_doc);
}


void dfs(map<string, vector<string>> &graph) {
    set<string> visited;
    for (auto it = graph.begin(); it != graph.end(); it++) {
        recursive_queue(graph, it->first, visited);
    }
}

map<string, vector<string>> getGraph() {

    freopen("cond.txt", "r", stdin);

    map<string, vector<string>> graph;
    string major_doc, minor_doc;

    while (cin >> major_doc >> minor_doc) {
        graph[major_doc].push_back(minor_doc);
    }
    fclose(stdin);

    return graph;
}

int main() {
    map<string, vector<string>> graph = getGraph();
    dfs(graph);
}


