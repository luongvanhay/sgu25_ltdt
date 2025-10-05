#include <bits/stdc++.h>
using namespace std;

int n;
vector<vector<int>> adj;
vector<int> degree;
vector<int> eulerPath;

// DFS kiểm tra liên thông
void dfs(int u, vector<bool> &visited) {
    visited[u] = true;
    for (int v = 0; v < n; v++) {
        if (adj[u][v] && !visited[v])
            dfs(v, visited);
    }
}

// Kiểm tra đồ thị liên thông
bool isConnected() {
    vector<bool> visited(n, false);
    int start = -1;
    for (int i = 0; i < n; i++) {
        if (degree[i] > 0) {
            start = i;
            break;
        }
    }
    if (start == -1) return true; // không có cạnh nào
    dfs(start, visited);
    for (int i = 0; i < n; i++) {
        if (degree[i] > 0 && !visited[i]) return false;
    }
    return true;
}

// tìm chu trình Euler
void findEuler(int u) {
    for (int v = 0; v < n; v++) {
        if (adj[u][v]) {
            adj[u][v] = adj[v][u] = 0;
            findEuler(v);
        }
    }
    eulerPath.push_back(u + 1); // lưu đỉnh theo chỉ số 1-based
}

int main() {

    // Mở file input/output
    ifstream fin("test1.inp");
    ofstream fout("test1.out");

    if (!fin.is_open()) {
        cerr << "Khong mo duoc file DoThiEuler.in\n";
        return 1;
    }

    fin >> n;
    adj.assign(n, vector<int>(n, 0));
    degree.assign(n, 0);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fin >> adj[i][j];
            if (adj[i][j]) degree[i]++;
        }
    }

    // Kiểm tra điều kiện Euler
    if (!isConnected()) {
        fout << 0;
        return 0;
    }
    for (int i = 0; i < n; i++) {
        if (degree[i] % 2 != 0) {
            fout << 0;
            return 0;
        }
    }

    // Là đồ thị Euler
    fout << 1 << "\n";

    findEuler(0);
    for (int i = 0; i < (int)eulerPath.size(); i++) {
        fout << eulerPath[i];
        if (i + 1 < (int)eulerPath.size()) fout << " ";
    }

    fin.close();
    fout.close();
    return 0;
}
