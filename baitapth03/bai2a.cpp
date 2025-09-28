#include <bits/stdc++.h>
using namespace std;

int main() {

    ifstream fin("test2a.inp");
    ofstream fout("test2a.out");

    int n, x, y;
    fin >> n >> x >> y;

    vector<vector<int>> adj(n + 1);
    for (int i = 1; i <= n; i++) {
        int v;
        while (fin >> v && v != -1) {
            adj[i].push_back(v);
        }
    }

    vector<int> parent(n + 1, -1);
    vector<bool> visited(n + 1, false);
    queue<int> q;

    visited[x] = true;
    q.push(x);

    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                parent[v] = u;
                q.push(v);
                if (v == y) break; // tìm thấy y thì dừng sớm
            }
        }
    }

    vector<int> path;
    if (!visited[y]) {
        fout << 0 << "\n"; // không có đường đi
    } else {
        for (int cur = y; cur != -1; cur = parent[cur]) {
            path.push_back(cur);
        }
        reverse(path.begin(), path.end());

        fout << path.size() << "\n";
        for (int v : path) fout << v << " ";
        fout << "\n";
    }

    fin.close();
    fout.close();
    return 0;
}
