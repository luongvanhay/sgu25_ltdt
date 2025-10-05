#include <bits/stdc++.h>
using namespace std;

int n;
vector<vector<int>> adj;
vector<int> degree;
vector<pair<int,int>> path; // lưu các quân domino (x, y)

void findEuler(int u) {
    for (int v = 0; v < 7; v++) {
        while (adj[u][v] > 0) {
            adj[u][v]--;
            adj[v][u]--;
            findEuler(v);
            path.push_back({u, v}); // ghi lại quân domino khi quay lui
        }
    }
}

int main() {
    ifstream fin("test2.inp");
    ofstream fout("test2.out");

    if (!fin.is_open()) {
        cerr << "Khong mo duoc file test2.inp\n";
        return 1;
    }

    fin >> n;
    adj.assign(7, vector<int>(7, 0));
    degree.assign(7, 0);

    for (int i = 0; i < n; i++) {
        int x, y;
        fin >> x >> y;
        adj[x][y]++;
        adj[y][x]++;
        degree[x]++;
        degree[y]++;
    }

    // Tìm đỉnh bắt đầu (đỉnh có bậc > 0 đầu tiên)
    int start = -1;
    for (int i = 0; i < 7; i++)
        if (degree[i]) { start = i; break; }

    if (start == -1) { // không có cạnh nào
        fout << 0;
        return 0;
    }

    // Kiểm tra liên thông
    vector<bool> visited(7, false);
    function<void(int)> dfs = [&](int u) {
        visited[u] = true;
        for (int v = 0; v < 7; v++)
            if (adj[u][v] > 0 && !visited[v])
                dfs(v);
    };
    dfs(start);

    for (int i = 0; i < 7; i++) {
        if (degree[i] > 0 && !visited[i]) {
            fout << 0;
            return 0;
        }
    }

    // Kiểm tra bậc chẵn
    for (int i = 0; i < 7; i++) {
        if (degree[i] % 2 != 0) {
            fout << 0;
            return 0;
        }
    }

    // Có chu trình Euler
    findEuler(start);

    fout << 1 << "\n";
    reverse(path.begin(), path.end());
    for (auto [x, y] : path)
        fout << x << " " << y << "\n";

    fin.close();
    fout.close();
    return 0;
}
