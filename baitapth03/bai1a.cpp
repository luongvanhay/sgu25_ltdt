#include <bits/stdc++.h>
using namespace std;

int main() {
    
    // Mở file input và output
    ifstream fin("test1a.inp");
    ofstream fout("test1a.out");

    int n, x;
    fin >> n >> x;

    vector<vector<int>> adj(n + 1);
    for (int i = 1; i <= n; i++) {
        int v;
        while (fin >> v && v != -1) {
            adj[i].push_back(v);
        }
    }

    vector<bool> visited(n + 1, false);
    queue<int> q;
    vector<int> result;

    visited[x] = true;
    q.push(x);

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                result.push_back(v);
                q.push(v);
            }
        }
    }

    fout << result.size() << "\n";
    for (int v : result) fout << v << " ";
    fout << "\n";

    fin.close();
    fout.close();

    return 0;
}
