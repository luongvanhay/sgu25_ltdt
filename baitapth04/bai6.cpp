#include <bits/stdc++.h>
using namespace std;

// Hàm tìm chu trình Euler 
vector<int> findEulerCycle(vector<vector<int>> &adj, int start) {
    int n = adj.size();
    vector<int> path;
    stack<int> st;
    st.push(start);

    // sao chép danh sách kề vì ta sẽ xóa cạnh trong quá trình tìm
    vector<multiset<int>> g(n);
    for (int i = 0; i < n; i++)
        g[i].insert(adj[i].begin(), adj[i].end());

    while (!st.empty()) {
        int u = st.top();
        if (!g[u].empty()) {
            int v = *g[u].begin();
            g[u].erase(g[u].find(v));
            g[v].erase(g[v].find(u)); // vì đồ thị vô hướng
            st.push(v);
        } else {
            path.push_back(u);
            st.pop();
        }
    }

    reverse(path.begin(), path.end());
    return path;
}


int main() {
    
    int n, m;
    cin >> n >> m; // số đỉnh, số cạnh
    vector<vector<int>> adj(n + 1);

    for (int i = 0; i < m; i++) {
        int u, v; 
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u); // vì vô hướng
    }

    // kiểm tra có ít nhất 1 cạnh không
    int start = -1;
    for (int i = 1; i <= n; i++)
        if (!adj[i].empty()) { start = i; break; }

    if (start == -1) {
        cout << 0 << "\n"; // không có cạnh nào
        return 0;
    }

    // kiểm tra tính liên thông
    vector<bool> vis(n + 1, false);
    stack<int> st; st.push(start);
    while (!st.empty()) {
        int u = st.top(); st.pop();
        if (vis[u]) continue;
        vis[u] = true;
        for (int v : adj[u]) if (!vis[v]) st.push(v);
    }
    for (int i = 1; i <= n; i++)
        if (!adj[i].empty() && !vis[i]) {
            cout << 0 << "\n"; // đồ thị không liên thông
            return 0;
        }

    // kiểm tra bậc chẵn
    for (int i = 1; i <= n; i++)
        if (adj[i].size() % 2 != 0) {
            cout << 0 << "\n"; // không phải đồ thị Euler
            return 0;
        }

    // tìm chu trình Euler
    vector<int> cycle = findEulerCycle(adj, start);

    cout << 1 << "\n";
    for (int x : cycle) cout << x << " ";
    cout << "\n";

    return 0;
}
