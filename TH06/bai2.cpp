#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
using namespace std;

struct Cell {
    int x, y;
};

struct State {
    int x, y;
    int cost;
    State(int _x, int _y, int _cost) : x(_x), y(_y), cost(_cost) {}
};

struct CompareState {
    bool operator()(const State& a, const State& b) {
        return a.cost > b.cost;
    }
};

int dx[4] = {-1, 1, 0, 0};
int dy[4] = {0, 0, -1, 1};

int main() {
    int N, M, XI, YI, XJ, YJ;
    cin >> N >> M >> XI >> YI >> XJ >> YJ;
    
    vector<vector<int>> A(N + 1, vector<int>(M + 1));
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            cin >> A[i][j];
        }
    }
    
    // Kiểm tra ô đầu và ô cuối có bằng 0 không
    if (A[XI][YI] == 0 || A[XJ][YJ] == 0) {
        cout << "0\n";
        return 0;
    }
    
    vector<vector<int>> dist(N + 1, vector<int>(M + 1, INT_MAX));
    vector<vector<Cell>> parent(N + 1, vector<Cell>(M + 1, {-1, -1}));
    
    priority_queue<State, vector<State>, CompareState> pq;
    dist[XI][YI] = 0;
    pq.push(State(XI, YI, 0));
    
    while (!pq.empty()) {
        State cur = pq.top();
        pq.pop();
        
        int x = cur.x, y = cur.y;
        if (cur.cost > dist[x][y]) continue;
        
        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            
            if (nx >= 1 && nx <= N && ny >= 1 && ny <= M && A[nx][ny] != 0) {
                int newCost = dist[x][y];
                
                // Nếu không phải là ô đích, cộng thêm chi phí của ô hiện tại
                // (KHÔNG tính ô đầu và ô cuối)
                if (!(x == XI && y == YI) && !(nx == XJ && ny == YJ)) {
                    newCost += A[x][y];
                }
                
                if (newCost < dist[nx][ny]) {
                    dist[nx][ny] = newCost;
                    parent[nx][ny] = {x, y};
                    pq.push(State(nx, ny, newCost));
                }
            }
        }
    }
    
    if (dist[XJ][YJ] == INT_MAX) {
        cout << "0\n";
    } else {
        cout << "1\n";
        cout << dist[XJ][YJ] << "\n";
        
        // Truy vết đường đi
        vector<Cell> path;
        Cell cur = {XJ, YJ};
        while (!(cur.x == -1 && cur.y == -1)) {
            path.push_back(cur);
            cur = parent[cur.x][cur.y];
        }
        reverse(path.begin(), path.end());
        
        // In đường đi
        for (const Cell& cell : path) {
            cout << cell.x << " " << cell.y << "\n";
        }
    }
    
    return 0;
}