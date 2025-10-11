#include <bits/stdc++.h>
using namespace std;
const long long INF = 1e15;

struct Edge {
    int v;
    long long w;
};

void dijkstra(int n, int s, const vector<vector<Edge>>& E,
              vector<long long>& D, vector<int>& trace) {
    D.assign(n + 1, INF);
    trace.assign(n + 1, -1);
    D[s] = 0;

    using T = pair<long long, int>; // {khoảng cách, đỉnh}
    priority_queue<T, vector<T>, greater<T>> pq;
    pq.push({0, s});

    while (!pq.empty()) {
        auto [du, u] = pq.top(); pq.pop();
        if (du != D[u]) continue;

        for (auto e : E[u]) {
            int v = e.v;
            long long w = e.w;
            if (D[v] > D[u] + w || 
                (D[v] == D[u] + w && (trace[v] == -1 || u < trace[v]))) {
                D[v] = D[u] + w;
                trace[v] = u;
                pq.push({D[v], v});
            }
        }
    }
}

vector<int> getPath(int s, int t, const vector<int>& trace) {
    vector<int> path;
    if (trace[t] == -1 && s != t) return path;
    for (int v = t; v != -1; v = trace[v])
        path.push_back(v);
    reverse(path.begin(), path.end());
    return path;
}

int main() {
    freopen("test4.inp", "r", stdin);
    freopen("test4.out", "w", stdout);

    int n, m, s, t;
    cin >> n >> m >> s >> t;

    vector<vector<Edge>> E(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        E[u].push_back({v, w});
    }

    // 🔹 Sắp xếp cạnh theo số đỉnh tăng
    for (int i = 1; i <= n; i++)
        sort(E[i].begin(), E[i].end(), [](Edge a, Edge b){ return a.v < b.v; });

    vector<long long> D;
    vector<int> trace;

    dijkstra(n, s, E, D, trace);

    if (D[t] == INF) {
        cout << "Khong co duong di tu " << s << " den " << t << "\n";
        return 0;
    }

    vector<int> path = getPath(s, t, trace);

    cout << path.size() << " " << D[t] << "\n";
    for (int v : path) cout << v << " ";
    cout << "\n";

    return 0;
}
