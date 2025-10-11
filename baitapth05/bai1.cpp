#include <bits/stdc++.h>
using namespace std;

const long long INF = 2000000000000000000LL; // giá trị vô cùng lớn

struct Edge {
    int v;          // đỉnh kề
    long long w;    // trọng số cạnh
};

void dijkstra(int n, int S, vector<vector<Edge>> &E,
              vector<long long> &D, vector<int> &trace) {
    D.assign(n + 1, INF);
    trace.assign(n + 1, -1);
    vector<bool> P(n + 1, false);

    D[S] = 0;

    for (int i = 1; i <= n; i++) {
        int uBest = -1;
        long long Min = INF;
        for (int u = 1; u <= n; u++) {
            if (!P[u] && D[u] < Min) {
                Min = D[u];
                uBest = u;
            }
        }
        if (uBest == -1) break; // không còn đỉnh nào có thể cập nhật

        P[uBest] = true;

        for (auto x : E[uBest]) {
            int v = x.v;
            long long w = x.w;
            if (D[v] >= D[uBest] + w) {   
                D[v] = D[uBest] + w;
                trace[v] = uBest;
            }
        }
    }
}

vector<int> getPath(int s, int t, vector<int> trace) {
    vector<int> path;
    if (trace[t] == -1 && s != t) return path; // không có đường đi
    for (int v = t; v != -1; v = trace[v])
        path.push_back(v);
    reverse(path.begin(), path.end());
    return path;
}

int main() {
    freopen("test.inp", "r", stdin);
    freopen("test.out", "w", stdout);

    int n, m, s, t;
    cin >> n >> m >> s >> t;

    vector<vector<Edge>> E(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        E[u].push_back({v, w});
    }

    for (int i = 1; i <= n; i++) {
        sort(E[i].begin(), E[i].end(), [](Edge a, Edge b){
            return a.v < b.v;
        });
    }

    vector<long long> D;
    vector<int> trace;
    dijkstra(n, s, E, D, trace);

    if (D[t] == INF) {
        cout << "Khong co duong di tu " << s << " den " << t << "\n";
        return 0;
    }

    vector<int> path = getPath(s, t, trace);

    cout << D[t] << "\n";
    for (int v : path) cout << v << " ";
    cout << "\n";

    return 0;
}
