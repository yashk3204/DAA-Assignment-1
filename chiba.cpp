#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <unordered_map>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace std::chrono;

using Graph = vector<vector<int>>;

// --------- CHIBA ALGORITHM CLASS ---------
class ChibaAlgorithm {
private:
    const Graph& graph;
    vector<vector<int>> maximalCliques;

    void findCliques(vector<int>& R, vector<int>& P, vector<int>& X) {
        if (P.empty() && X.empty()) {
            maximalCliques.push_back(R);
            return;
        }

        int pivot = -1;
        int maxCount = -1;

        for (int u : P) {
            int count = 0;
            for (int v : P) {
                if (binary_search(graph[u].begin(), graph[u].end(), v))
                    count++;
            }
            if (count > maxCount) {
                maxCount = count;
                pivot = u;
            }
        }

        vector<int> P_copy = P;
        for (int v : P_copy) {
            if (pivot != -1 && binary_search(graph[pivot].begin(), graph[pivot].end(), v)) continue;

            R.push_back(v);
            vector<int> newP, newX;
            for (int u : P) {
                if (binary_search(graph[v].begin(), graph[v].end(), u))
                    newP.push_back(u);
            }
            for (int u : X) {
                if (binary_search(graph[v].begin(), graph[v].end(), u))
                    newX.push_back(u);
            }

            findCliques(R, newP, newX);
            R.pop_back();
            P.erase(remove(P.begin(), P.end(), v), P.end());
            X.push_back(v);
        }
    }

public:
    ChibaAlgorithm(const Graph& g) : graph(g) {}

    vector<vector<int>> enumerateMaximalCliques() {
        maximalCliques.clear();

        vector<pair<int, int>> vertexDegrees;
        for (size_t v = 0; v < graph.size(); ++v) {
            if (!graph[v].empty())
                vertexDegrees.emplace_back(graph[v].size(), v);
        }

        sort(vertexDegrees.begin(), vertexDegrees.end());

        for (const auto& [deg, v] : vertexDegrees) {
            vector<int> R = {v};
            vector<int> P, X;

            for (int u : graph[v]) {
                if (graph[u].size() > graph[v].size() || 
                    (graph[u].size() == graph[v].size() && u > v)) {
                    P.push_back(u);
                } else if (graph[u].size() < graph[v].size() || 
                           (graph[u].size() == graph[v].size() && u < v)) {
                    X.push_back(u);
                }
            }

            findCliques(R, P, X);
        }

        return maximalCliques;
    }
};

// --------- RUNNER FUNCTION ---------
pair<vector<vector<int>>, double> runChiba(const Graph& graph) {
    ChibaAlgorithm chiba(graph);

    auto start = high_resolution_clock::now();
    vector<vector<int>> cliques = chiba.enumerateMaximalCliques();
    auto end = high_resolution_clock::now();

    double time = duration_cast<milliseconds>(end - start).count() / 1000.0;
    return {cliques, time};
}

// --------- FILE PARSING ---------
Graph readGraphFromFile(const string& filename) {
    ifstream infile(filename);
    if (!infile) {
        cerr << "Cannot open file: " << filename << endl;
        exit(1);
    }

    int n, m;
    infile >> n >> m;

    Graph graph(n);
    int u, v;
    while (infile >> u >> v) {
        graph[u].push_back(v);
        graph[v].push_back(u); // Undirected
    }

    for (auto& neighbors : graph)
        sort(neighbors.begin(), neighbors.end());  // Required for binary_search

    return graph;
}

// --------- OUTPUT TO FILE ---------
void writeOutput(const vector<vector<int>>& cliques, double timeTaken, const string& outputFile) {
    ofstream out(outputFile);
    if (!out) {
        cerr << "Cannot open output file.\n";
        exit(1);
    }

    unordered_map<int, int> sizeDist;
    int maxSize = 0;
    for (const auto& clique : cliques) {
        int size = clique.size();
        sizeDist[size]++;
        maxSize = max(maxSize, size);
    }

    out << "1. Largest Clique Size: " << maxSize << "\n";
    out << "2. Total Max Cliques: " << cliques.size() << "\n";
    out << "3. Time Taken: " << timeTaken << " seconds\n";
    out << "4. Distribution of clique sizes:\n";

    vector<int> sizes;
    for (auto& p : sizeDist) sizes.push_back(p.first);
    sort(sizes.begin(), sizes.end());

    for (int sz : sizes)
        out << "Size " << sz << ": " << sizeDist[sz] << " cliques\n";
    
    out.close();
}

// --------- MAIN ---------
int main() {
    string inputFile = "test1.txt";
    string outputFile = "output.txt";

    Graph g = readGraphFromFile(inputFile);
    auto [cliques, timeTaken] = runChiba(g);
    writeOutput(cliques, timeTaken, outputFile);

    cout << "Chiba algorithm completed. Output written to " << outputFile << endl;
    return 0;
}