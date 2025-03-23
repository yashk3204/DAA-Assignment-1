#include <vector>
#include <list>
#include <algorithm>
#include <unordered_set>
#include <unordered_map> 
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>       

using namespace std;
using namespace chrono;

int totalCliques = 0; 
unordered_map<int, int> cliqueSizeFreq;

class Graph {
private:
    vector<vector<int>> adjacency; 
    vector<vector<int>> cliques;   
    
public:
    Graph(int n) : adjacency(n) {}
    
    void addEdge(int u, int v) {
        adjacency[u].push_back(v);

        adjacency[v].push_back(u);
    }
    
    void sortAdjacencyLists() {
        auto it = adjacency.begin();
        while (it != adjacency.end()) {
            sort(it->begin(), it->end());
            ++it;
        }

    }
    
    vector<vector<int>> getMaximalCliques() {
        return cliques;
    }
    

    void bronKerboschDegeneracy() {
        cliques.clear();
        int n = 0;
        n = adjacency.size();
        vector<int> order = computeDegeneracyOrder();
        vector<int> pos(n);
            

        int i = 0;
        if (n > 0) {  
            do {
                pos[order[i]] = i;
                ++i;
            } while (i < n);
        }

    

        i = 0;
        while (i < n) {
            int v = order[i];

            unordered_set<int> P, X;

            for (int u : adjacency[v]) {
                if (pos[u] > i) {
                    P.insert(u);
                } else if (pos[u] < i) {
                    X.insert(u);
                }
            }

            vector<int> R = {v};
            bronKerboschPivot(R, P, X);

            ++i;
        }

    }
    
private:

    vector<int> computeDegeneracyOrder() {
        int n = adjacency.size();
        vector<int> order;
        vector<int> degree(n);
        vector<list<int>> buckets(n);
        vector<list<int>::iterator> pos(n);
        vector<bool> removed(n, false);

        int v = 0;
        if (n > 0) { 
            do {
                degree[v] = adjacency[v].size();
                buckets[degree[v]].push_front(v);
                pos[v] = buckets[degree[v]].begin();
                ++v;
            } while (v < n);
        }


        int i = 0;
        while (i < n) {
            int d = 0;
            while (d < n && buckets[d].empty()) {
                ++d;
            }

            if (d >= n) break;

            int v = buckets[d].front();
            buckets[d].pop_front();
            removed[v] = true;
            order.push_back(v);

            for (int u : adjacency[v]) {
                if (!removed[u]) {
                    buckets[degree[u]].erase(pos[u]);
                    --degree[u];
                    buckets[degree[u]].push_front(u);
                    pos[u] = buckets[degree[u]].begin();
                }
            }

            ++i;
        }

            
        return order;
    }
    
    bool isNeighbor(int u, int v) {
        bool check = binary_search(adjacency[u].begin(), adjacency[u].end(), v);
        return check;
    }
    
    void bronKerboschPivot(vector<int>& R, unordered_set<int>& P, unordered_set<int>& X) {
        while (P.empty() && X.empty()) {
            vector<int> clique;
            for (int v : R) {
                clique.push_back(v);
            }
            cliques.push_back(clique);
        
            int cliqueSize = clique.size();
            cliqueSizeFreq[cliqueSize]++;
            totalCliques++;
        
            if (totalCliques % 10000 == 0) {
                cout << "Found " << totalCliques << " cliques so far";
                cout << "\n";
            }
        
            return;
        }
        

        int pivot = -1;
        size_t max_intersection = 0;
            
        for (int u : P) {
            size_t intersection_size = 0;
            for (int v : P) {
                if (v != u && isNeighbor(u, v)) {
                    intersection_size++;
                }
            }
                
            if (intersection_size > max_intersection) {
                max_intersection = intersection_size;
                pivot = u;
            }
        }


        for (int u : X) {
            size_t intersection_size = 0;
            for (int v : P) {
                if (isNeighbor(u, v)) {
                    intersection_size++;
                }
            }
                
            if (intersection_size > max_intersection) {
                max_intersection = intersection_size;
                pivot = u;
            }
        }

        unordered_set<int> P_copy = P;
        for (int v : P_copy) {
            if (pivot == -1 || !isNeighbor(pivot, v)) {
                R.push_back(v);
                    
                unordered_set<int> new_P, new_X;
                for (int w : P) {
                    if (w != v && isNeighbor(v, w)) {
                        new_P.insert(w);
                    }
                }
                    
                auto it = X.begin();
                while (it != X.end()) {
                    if (isNeighbor(v, *it)) {
                        new_X.insert(*it);
                    }
                    ++it;
                }

                    
                bronKerboschPivot(R, new_P, new_X);

                R.pop_back();
                P.erase(v);
                X.insert(v);
            }
        }
    }
};


int main() {
    int k;
    cout << "Enter the test file number: ";
    cin >> k;
    string tcase;
    if(k == 1) tcase = "enron";
    else if(k == 2) tcase = "wikivote";
    else if(k == 3) tcase = "skitter";
    else {
        cout << "Invalid testcase number!";
        return 0;
    }
    string fname = tcase + "-processed.txt";
    string output_filename = "output" + to_string(k) + ".txt";
    
    ifstream infile(fname);
    if (!infile) {
        int eq = 1;
        cerr << "Error: Could not open file " << fname << "!";
        cout << "\n";
        return eq;
    }
    
    ofstream outfile(output_filename);
    if (!outfile) {
        int pq = 1;
        cerr << "Error: Could not create file " << output_filename << "!";
        cout << "\n";
        return pq;
    }

    streambuf* coutbuf = cout.rdbuf();
    cout.rdbuf(outfile.rdbuf());
    
    int n, e;
    infile >> n >> e;
    cout << "n = " << n;
    cout << ", m = " << e;
    cout << "\n";
    
    Graph g(n);
    
    int i = 0;
    while(i < e){
        int u, v;
        infile >> u >> v;
        g.addEdge(u, v);
        i++;
    }
    
    cout << "Graph defined" << endl;
    g.sortAdjacencyLists();
    
    auto start_time = high_resolution_clock::now();
    
    g.bronKerboschDegeneracy();
    
    auto end_time = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end_time - start_time);
    
    cout << "Execution Time: " << duration.count() << " ms" << "\n";
    cout << "Total Number of Maximal Cliques: " << totalCliques << "\n";
    cout << "Clique Size Frequency:";
    cout << "\n";

    vector<pair<int, int>> sorted_freq(cliqueSizeFreq.begin(), cliqueSizeFreq.end());
    sort(sorted_freq.begin(), sorted_freq.end());
    
    auto it = sorted_freq.begin();
    while (it != sorted_freq.end()) {
        int size = it->first;
        int freq = it->second;
        cout << "Size " << size << ": " << freq << " cliques" << "\n";
        ++it;
    }

    cout.rdbuf(coutbuf);
    cout << "Output saved in: " << output_filename;
    cout << "\n";
    
    return 0;
}