#include <bits/stdc++.h>
using namespace std;
const long long INF = 1e15;

int main() {
    freopen("test3.inp", "r", stdin);
    freopen("test3.out", "w", stdout);

    int n, m;
    cin >> n >> m;

    vector<vector<long long>> dist(n + 1, vector<long long>(n + 1, INF));

    // Khởi tạo khoảng cách ban đầu
    for (int i = 1; i <= n; i++) dist[i][i] = 0;

    // Đọc danh sách cạnh
    for (int i = 0; i < m; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        dist[u][v] = min(dist[u][v], w); // nếu có nhiều cạnh, lấy cạnh nhỏ nhất
        dist[v][u] = min(dist[v][u], w); // đồ thị vô hướng
    }

    // Thuật toán Floyd–Warshall
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (dist[i][k] + dist[k][j] < dist[i][j])
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }

    // Xuất kết quả
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (dist[i][j] >= INF / 2) cout << 0 << " ";
            else cout << dist[i][j] << " ";
        }
        cout << "\n";
    }

    return 0;
}
