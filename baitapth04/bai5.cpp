#include <bits/stdc++.h>
using namespace std;

int n;
vector<vector<int>> adj;
vector<int> degree;

bool isConnected() {
    vector<bool> visited(n, false);
    stack<int> st;
    int start = -1;
    for (int i = 0; i < n; i++)
        if (degree[i] > 0) { start = i; break; }
    if (start == -1) return true; // đồ thị không có cạnh

    st.push(start);
    while (!st.empty()) {
        int u = st.top(); st.pop();
        if (!visited[u]) {
            visited[u] = true;
            for (int v = 0; v < n; v++)
                if (adj[u][v] && !visited[v])
                    st.push(v);
        }
    }
    for (int i = 0; i < n; i++)
        if (degree[i] > 0 && !visited[i])
            return false;
    return true;
}

vector<int> findEulerCycle(int start) {
    vector<int> res;
    stack<int> st;
    st.push(start);

    vector<vector<int>> temp = adj; // copy vì ta sẽ xóa cạnh

    while (!st.empty()) {
        int u = st.top();
        int v = -1;
        for (int i = 0; i < n; i++) {
            if (temp[u][i]) { v = i; break; }
        }
        if (v != -1) {
            // Xóa cạnh (u, v)
            temp[u][v] = temp[v][u] = 0;
            st.push(v);
        } else {
            res.push_back(u + 1); // 1-based
            st.pop();
        }
    }
    reverse(res.begin(), res.end());
    return res;
}

int main() {
    ifstream fin("test5.inp");
    ofstream fout("test5.out");

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

    // kiểm tra tất cả đỉnh đều có bậc chẵn
    for (int i = 0; i < n; i++) {
        if (degree[i] % 2 != 0) {
            fout << 0;
            return 0;
        }
    }

    fout << 1 << "\n";
    vector<int> cycle = findEulerCycle(0);
    for (int i = 0; i < (int)cycle.size(); i++) {
        fout << cycle[i];
        if (i + 1 < (int)cycle.size()) fout << " ";
    }

    fin.close();
    fout.close();
    return 0;
}
