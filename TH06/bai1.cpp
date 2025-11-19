#include <iostream>
#include <vector>
#include <cmath>
#include <queue>
#include <algorithm>
using namespace std;

struct Circle {
    double x, y, r;
};

double edgeDistance(const Circle &a, const Circle &b) {
    double d = sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
    return max(0.0, d - (a.r + b.r));
}

struct State {
    int node;
    int jumps;
    int steps;
    State(int n, int j, int s) : node(n), jumps(j), steps(s) {}
};

struct CompareState {
    bool operator()(const State& a, const State& b) {
        if (a.jumps != b.jumps) return a.jumps > b.jumps;
        return a.steps > b.steps;
    }
};

int main() {
    int N, S, T;
    cin >> N >> S >> T;
    vector<Circle> c(N + 1);
    for (int i = 1; i <= N; i++) 
        cin >> c[i].x >> c[i].y >> c[i].r;

    vector<vector<pair<int,int>>> adj(N + 1);

    // Xây dựng đồ thị
    for (int i = 1; i <= N; i++) {
        for (int j = i + 1; j <= N; j++) {
            double d = edgeDistance(c[i], c[j]);
            if (d <= 50.0 + 1e-9) {
                adj[i].push_back({j, 0});
                adj[j].push_back({i, 0});
            } else if (d <= 60.0 + 1e-9) {
                adj[i].push_back({j, 1});
                adj[j].push_back({i, 1});
            }
        }
    }

    const int INF = 1e9;
    vector<int> jumps(N + 1, INF);
    vector<int> steps(N + 1, INF);
    vector<int> parent(N + 1, -1);
    vector<int> edgeType(N + 1, -1);
    
    jumps[S] = 0;
    steps[S] = 1;
    
    priority_queue<State, vector<State>, CompareState> pq;
    pq.push(State(S, 0, 1));

    while (!pq.empty()) {
        State cur = pq.top();
        pq.pop();
        
        int u = cur.node;
        if (cur.jumps > jumps[u] || (cur.jumps == jumps[u] && cur.steps > steps[u])) 
            continue;
            
        for (auto [v, type] : adj[u]) {
            int newJumps = jumps[u] + (type == 1 ? 1 : 0);
            int newSteps = steps[u] + 1;
            
            if (newJumps < jumps[v] || (newJumps == jumps[v] && newSteps < steps[v])) {
                jumps[v] = newJumps;
                steps[v] = newSteps;
                parent[v] = u;
                edgeType[v] = type;
                pq.push(State(v, newJumps, newSteps));
            }
        }
    }

    if (jumps[T] == INF) {
        cout << "0\n";
        return 0;
    }

    // Truy vết đường đi
    vector<int> path_nodes;
    vector<int> path_actions;
    
    for (int v = T; v != S; v = parent[v]) {
        path_nodes.push_back(v);
        path_actions.push_back(edgeType[v]);
    }
    path_nodes.push_back(S);
    reverse(path_nodes.begin(), path_nodes.end());
    reverse(path_actions.begin(), path_actions.end());

    // ✅ In kết quả đúng format đề bài
    cout << "1\n";
    cout << jumps[T] << " " << path_nodes.size() << "\n";
    for (int i = 0; i < (int)path_actions.size(); i++) {
        cout << path_nodes[i + 1] << " " << path_actions[i] << "\n";
    }

    return 0;
}
