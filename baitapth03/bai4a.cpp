#include <bits/stdc++.h>
using namespace std;

int n, x, y, z;
vector<vector<int>> adj;
vector<bool> visited;

void bfs(int start, int skipEdgeU=-1, int skipEdgeV=-1, int skipVertex=-1) {
    queue<int> q;
    q.push(start);
    visited[start] = true;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (int v : adj[u]) {
            if ((u == skipEdgeU && v == skipEdgeV) || (u == skipEdgeV && v == skipEdgeU))
                continue; // bỏ cạnh (x,y)
            if (v == skipVertex) continue; // bỏ đỉnh z
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }
}

int countComponents(int skipEdgeU=-1, int skipEdgeV=-1, int skipVertex=-1) {
    visited.assign(n+1, false);
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (i == skipVertex) continue;
        if (!visited[i]) {
            cnt++;
            bfs(i, skipEdgeU, skipEdgeV, skipVertex);
        }
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> x >> y >> z;
    adj.assign(n+1, {});

    for (int u = 1; u <= n; u++) {
        while (true) {
            int v; cin >> v;
            if (v == -1) break;
            adj[u].push_back(v);
        }
    }

    // Kiểm tra cạnh (x,y) có là cầu không
    int comp1 = countComponents();
    int comp2 = countComponents(x, y);
    if (comp2 > comp1) cout << "canh cau\n";
    else cout << "khong la canh cau\n";

    // Kiểm tra đỉnh z có là đỉnh khớp không
    int comp3 = countComponents();
    int comp4 = countComponents(-1, -1, z);
    if (comp4 > comp3) cout << "dinh khop\n";
    else cout << "khong la dinh khop\n";

    return 0;
}
