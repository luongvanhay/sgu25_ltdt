#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int u, v, w, id;
};

vector<int> parent, RankArr;

void MakeSet(int n) {
    parent.assign(n, 0);
    RankArr.assign(n, 1);
    for (int i = 0; i < n; i++) parent[i] = i;
}

int findSet(int i) {
    if (parent[i] != i)
        parent[i] = findSet(parent[i]);
    return parent[i];
}

bool unite(int x, int y) {
    int s1 = findSet(x);
    int s2 = findSet(y);
    if (s1 == s2) return false;
    if (RankArr[s1] < RankArr[s2]) swap(s1, s2);
    parent[s2] = s1;
    if (RankArr[s1] == RankArr[s2]) RankArr[s1]++;
    return true;
}

bool cmp(const Edge &a, const Edge &b) {
    if (a.w != b.w) return a.w < b.w;
    return a.id < b.id;
}

// Tính trọng số MST (có thể bỏ cạnh targetID)
long long computeMST(int n, vector<Edge> &edges, int targetID = -1) {
    vector<Edge> temp = edges;
    sort(temp.begin(), temp.end(), cmp);
    
    MakeSet(n);
    long long total = 0;
    int count = 0;
    
    for (auto &e : temp) {
        if (e.id == targetID) continue; // bỏ cạnh target
        if (unite(e.u, e.v)) {
            total += e.w;
            count++;
            if (count == n - 1) break;
        }
    }
    
    if (count != n - 1) return -1; // không liên thông
    return total;
}

// Kiểm tra liên thông khi bỏ cạnh targetID
bool isConnectedWithout(int n, vector<Edge> &edges, int targetID) {
    MakeSet(n);
    int count = 0;
    for (auto &e : edges) {
        if (e.id == targetID) continue;
        if (unite(e.u, e.v)) {
            count++;
            if (count == n - 1) break;
        }
    }
    return count == n - 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--) {
        int n, m, q;
        cin >> n >> m >> q;
        vector<Edge> edges(m);
        for (int i = 0; i < m; i++) {
            int u, v, w;
            cin >> u >> v >> w;
            edges[i] = {u - 1, v - 1, w, i};
        }

        for (int i = 0; i < q; i++) {
            int k, g;
            cin >> k >> g;
            k--;

            vector<Edge> modified = edges;
            for (int j = 0; j < g; j++) {
                int id, newW;
                cin >> id >> newW;
                id--;
                if (id >= 0 && id < m)
                    modified[id].w = newW;
            }

            // kiểm tra liên thông
            if (!isConnectedWithout(n, modified, k)) {
                cout << "NO\n";
                continue;
            }

            long long mstNormal = computeMST(n, modified);
            long long mstWithoutK = computeMST(n, modified, k);

            if (mstWithoutK == -1) { // mất liên thông
                cout << "NO\n";
                continue;
            }

            // nếu MST thường == MST bỏ k → k không nằm trong bất kỳ MST nào
            if (mstNormal == mstWithoutK)
                cout << "YES\n";
            else
                cout << "NO\n";
        }
    }

    return 0;
}



// code của best submission

// #include <iostream>
// #include <vector>
// #define N 100005
// #define M 1000005
// using namespace std;
// int t, n, m, q, k, sl;
// int Cost[M], f[M], d[N];
// pair<int,int> B[M];
 
// void ReadInt(int &x) {
//     char c = getchar();
//     while (!isdigit(c)) c = getchar();
//     x = 0;
//     while (isdigit(c)) x = (x<<3) + (x<<1) + c - '0', c = getchar();
// }
 
// void Enter() {
//     ReadInt(n);
//     ReadInt(m);
//     ReadInt(q);
//     int u, v;
//     for(int i=1; i<=m; i++) {
//         ReadInt(B[i].first);
//         ReadInt(B[i].second);
//         ReadInt(Cost[i]);
//     }
// }
 
// int getD(int x) {
//     if (d[x]>0) return d[x] = getD(d[x]);
//         else return x;
// }
 
// void Union(int u, int v) {
//     if (d[u] > d[v]) {
//         d[u] += d[v];
//         d[v] = u;
//     } else {
//         d[v] += d[u];
//         d[u] = v;
//     }
// }
 
// void Process() {
//     while (q--) {
//         ReadInt(k);
//         ReadInt(sl);
//         int x, v;
//         for(int i=1; i<=m; i++) f[i] = Cost[i];
//         while (sl--) {
//             ReadInt(x);
//             ReadInt(v);
//             f[x] = v;
//         }
//         fill(d+1, d+n+1, -1);
//         int ok = false;
//         for(int i=1; i<=m; i++) if (f[i] < f[k]) {
//             int u = getD(B[i].first);
//             int v = getD(B[i].second);
//             if (u!=v) {
//                 Union(u, v);
//                 if (getD(B[k].first) == getD(B[k].second)) {
//                     cout << "YES\n";
//                     ok = true;
//                     break;
//                 }
//             }
//         }
//         if (!ok) cout << "NO\n";
//     }
// }
 
// int main()
// {
//     ReadInt(t);
//     while (t--) {
//         Enter();
//         Process();
//     }
// }


// code AI :(((((


// #include <bits/stdc++.h>
// using namespace std;
// using ll = long long;

// struct Edge {
//     int u, v;
//     ll w;
// };

// struct DSU {
//     int n;
//     vector<int> p, r;
//     DSU(int n=0){init(n);}
//     void init(int n_){
//         n = n_;
//         p.resize(n+1);
//         r.assign(n+1,0);
//         for(int i=1;i<=n;i++) p[i]=i;
//     }
//     int find(int x){ return p[x]==x?x:p[x]=find(p[x]); }
//     bool unite(int a,int b){
//         a = find(a); b = find(b);
//         if(a==b) return false;
//         if(r[a]<r[b]) swap(a,b);
//         p[b]=a;
//         if(r[a]==r[b]) r[a]++;
//         return true;
//     }
// };

// int main(){
//     ios::sync_with_stdio(false);
//     cin.tie(nullptr);
//     int T;
//     if(!(cin>>T)) return 0;
//     while(T--){
//         int N,M,Q;
//         cin>>N>>M>>Q;
//         vector<Edge> edges(M+1);
//         vector<vector<pair<int,int>>> adj(N+1);
//         for(int i=1;i<=M;i++){
//             int u,v; ll w;
//             cin>>u>>v>>w;
//             edges[i] = {u,v,w};
//             adj[u].push_back({v,i});
//             adj[v].push_back({u,i});
//         }

//         // Tarjan iterative to find bridges
//         vector<int> tin(N+1,0), low(N+1,0), visited(N+1,0);
//         vector<char> isBridge(M+1, 0);
//         int timer = 0;
//         // stack entries: node v, parent node p, parent edge pe, iterator index
//         struct NodeState { int v, p, pe, it; };
//         for(int s=1;s<=N;s++){
//             if(visited[s]) continue;
//             vector<NodeState> st;
//             st.push_back({s, -1, -1, 0});
//             while(!st.empty()){
//                 NodeState &cur = st.back();
//                 int v = cur.v;
//                 if(cur.it==0){
//                     visited[v]=1;
//                     tin[v]=low[v]=++timer;
//                 }
//                 if(cur.it < (int)adj[v].size()){
//                     auto [to, eid] = adj[v][cur.it++];
//                     if(eid == cur.pe) continue;
//                     if(visited[to]){
//                         // back edge
//                         low[v] = min(low[v], tin[to]);
//                     } else {
//                         // tree edge
//                         st.push_back({to, v, eid, 0});
//                     }
//                 } else {
//                     // finishing v
//                     if(cur.p != -1){
//                         // update parent's low and check bridge
//                         low[cur.p] = min(low[cur.p], low[v]);
//                         if(low[v] > tin[cur.p]){
//                             // edge cur.pe is a bridge
//                             isBridge[cur.pe] = 1;
//                         }
//                     }
//                     st.pop_back();
//                 }
//             }
//         }

//         // process Q queries
//         for(int qi=0; qi<Q; qi++){
//             int k; int g;
//             cin>>k>>g;
//             unordered_map<int,ll> mods;
//             mods.reserve(g*2+10);
//             for(int i=0;i<g;i++){
//                 int tp; ll cp;
//                 cin>>tp>>cp;
//                 mods[tp]=cp;
//             }

//             // If k is bridge (structure-based) -> removing disconnects -> cannot be "không tiềm năng"
//             if(isBridge[k]){
//                 cout<<"NO\n";
//                 continue;
//             }

//             // weight of edge k with modifications
//             ll wk = (mods.count(k) ? mods[k] : edges[k].w);
//             int u = edges[k].u, v = edges[k].v;

//             // if there exists path u-v using only edges with weight < wk -> k is not in any MST -> non-potential -> YES
//             DSU dsu(N);
//             bool connected = false;
//             for(int i=1;i<=M;i++){
//                 ll wi = (mods.count(i) ? mods[i] : edges[i].w);
//                 if(wi < wk){
//                     dsu.unite(edges[i].u, edges[i].v);
//                     if(dsu.find(u) == dsu.find(v)){
//                         connected = true;
//                         break;
//                     }
//                 }
//             }
//             if(connected) cout<<"YES\n"; else cout<<"NO\n";
//         }
//         // End of testcase
//     }
//     return 0;
// }