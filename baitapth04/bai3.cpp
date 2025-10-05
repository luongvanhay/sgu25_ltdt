#include <bits/stdc++.h>
using namespace std;

int n;
vector<vector<int>> adj;
vector<int> degree;
vector<int> eulerPath;

void dfs(int u, vector<bool> &visited) {
    visited[u] = true;
    for (int v = 0; v < n; v++) {
        if (adj[u][v] && !visited[v]) dfs(v, visited);
    }
}

bool isConnected() {
    vector<bool> visited(n, false);
    int start = -1;
    for (int i = 0; i < n; i++) {
        if (degree[i] > 0) { start = i; break; }
    }
    if (start == -1) return true; // không có cạnh
    dfs(start, visited);
    for (int i = 0; i < n; i++)
        if (degree[i] > 0 && !visited[i])
            return false;
    return true;
}

void findEuler(int u) {
    for (int v = 0; v < n; v++) {
        while (adj[u][v]) {
            adj[u][v] = adj[v][u] = 0;
            findEuler(v);
        }
    }
    eulerPath.push_back(u + 1); // 1-based
}

int main() {
    ifstream fin("test3.inp");
    ofstream fout("test3.out");

    if (!fin.is_open()) {
        cerr << "Khong mo duoc file test3.inp\n";
        return 1;
    }

    fin >> n;
    adj.assign(n, vector<int>(n, 0));
    degree.assign(n, 0);

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            fin >> adj[i][j];
            if (adj[i][j]) degree[i]++;
        }

    if (!isConnected()) {
        fout << 0;
        return 0;
    }

    vector<int> oddVertices;
    for (int i = 0; i < n; i++)
        if (degree[i] % 2 != 0)
            oddVertices.push_back(i);

    if (oddVertices.size() != 2 && oddVertices.size() != 0) {
        fout << 0;
        return 0;
    }

    fout << 1 << "\n";

    int start = (oddVertices.size() == 2) ? oddVertices[0] : 0;
    findEuler(start);

    reverse(eulerPath.begin(), eulerPath.end());
    for (int i = 0; i < (int)eulerPath.size(); i++) {
        fout << eulerPath[i];
        if (i + 1 < (int)eulerPath.size()) fout << " ";
    }

    fin.close();
    fout.close();
    return 0;
}
