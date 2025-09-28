#include <bits/stdc++.h>
using namespace std;

int main() {
    

    ifstream fin("test3a.inp");
    ofstream fout("test3a.out");

    int n;
    fin >> n;

    vector<vector<int>> adj(n + 1);
    for (int i = 1; i <= n; i++) {
        int v;
        while (fin >> v && v != -1) {
            adj[i].push_back(v);
        }
    }

    vector<bool> visited(n + 1, false);
    vector<vector<int>> components;

    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            vector<int> comp;
            queue<int> q;
            q.push(i);
            visited[i] = true;

            while (!q.empty()) {
                int u = q.front(); q.pop();
                comp.push_back(u);
                for (int v : adj[u]) {
                    if (!visited[v]) {
                        visited[v] = true;
                        q.push(v);
                    }
                }
            }

            sort(comp.begin(), comp.end()); 
            components.push_back(comp);
        }
    }

    fout << components.size() << "\n";
    for (auto &comp : components) {
        for (int v : comp) fout << v << " ";
        fout << "\n";
    }

    fin.close();
    fout.close();
    return 0;
}
