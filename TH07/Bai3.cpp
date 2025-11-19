#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std;

#define FI "test2.inp"
#define FO "test2.out"

vector<int> parent;
vector<int> RankArr;

void MakeSet(int n)
{
    parent.resize(n);
    RankArr.resize(n);
    for (int i = 0; i < n; i++)
    {
        parent[i] = i;
        RankArr[i] = 1;
    }
}

int find(int i)
{
    if (parent[i] != i)
    {
        parent[i] = find(parent[i]);
    }
    return parent[i];
}

bool unite(int x, int y)
{
    int s1 = find(x);
    int s2 = find(y);
    if (s1 != s2)
    {
        if (RankArr[s1] < RankArr[s2])
        {
            parent[s1] = s2;
        }
        else if (RankArr[s2] < RankArr[s1])
        {
            parent[s2] = s1;
        }
        else
        {
            parent[s2] = s1;
            RankArr[s1]++;
        }
        return true;
    }

    return false;
}
bool comparator(vector<int> &a, vector<int> &b)
{
    return a[2] < b[2];
}
vector<tuple<int, int, int>> mst;
int kruskalsMST(int V, vector<vector<int>> &edges)
{
    sort(edges.begin(), edges.end(), comparator);
    MakeSet(V);

    int TotalWeight = 0;
    int demCanh = 0;
    for (auto &e : edges)
    {
        int u = e[0], v = e[1], w = e[2];
        if (unite(u, v))
        {
            mst.push_back({u, v, w});
            TotalWeight += w;
            demCanh++;
            if (demCanh == V - 1)
                break;
        }
    }
    // int cost = 0, count = 0;
    // for (auto &e : edges) {
    //     int x = e[0], y = e[1], w = e[2];
    //     if (find(x) != find(y)) {
    //         unite(x, y);
    //         cost += w;
    //         if (count++ == V - 1) break; // ts fr is useless :sob:
    //     }

    return TotalWeight;
}

int main()
{
    ifstream fi(FI);
    int n, m;
    fi >> n >> m;

    vector<vector<int>> edges(m);

    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        fi >> u >> v >> w;
        edges[i] = {u - 1, v - 1, w};
    }
    int tong = kruskalsMST(n, edges);
    cout << mst.size() << " " << tong << endl;

    for (auto &[u, v, w] : mst)
    {
        cout << u + 1 << " " << v + 1 << " " << w << endl;
        ;
    }
    return 0;
}