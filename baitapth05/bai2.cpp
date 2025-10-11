#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll INF = (ll)4e18;

struct Edge {
    int v; ll w;
};

void dijkstra(int n, int s, const vector<vector<Edge>>& E,
              vector<ll>& D, vector<int>& trace) {
    D.assign(n + 1, INF);
    trace.assign(n + 1, -1);
    D[s] = 0;
    using T = pair<ll,int>;
    priority_queue<T, vector<T>, greater<T>> pq;
    pq.push({0, s});
    while (!pq.empty()) {
        auto [du, u] = pq.top(); pq.pop();
        if (du != D[u]) continue;
        for (auto e : E[u]) {
            int v = e.v; ll w = e.w;
            if (v < 1 || v > n) continue;
            if (D[v] > D[u] + w) {
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
    freopen("test2.inp", "r", stdin);
    freopen("test2.out", "w", stdout);

    int n, m, s, x, t;
    cin >> n >> m >> s >> x >> t;

    vector<vector<Edge>> E(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v; ll w;
        cin >> u >> v >> w;
        E[u].push_back({v, w});
    }

    vector<ll> D1, D2;
    vector<int> trace1, trace2;
    dijkstra(n, s, E, D1, trace1);
    dijkstra(n, x, E, D2, trace2);

    if (D1[x] == INF || D2[t] == INF) {
        cout << "Khong co duong di qua dinh trung gian\n";
        return 0;
    }

    ll total = D1[x] + D2[t];
    vector<int> path1 = getPath(s, x, trace1);
    vector<int> path2 = getPath(x, t, trace2);

    if (!path1.empty()) path1.pop_back(); // bỏ trùng x
    path1.insert(path1.end(), path2.begin(), path2.end());

    cout << path1.size() << " " << total << "\n";
    for (int v : path1) cout << v << " ";
    cout << "\n";
}
