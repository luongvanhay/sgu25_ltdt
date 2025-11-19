#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

#define FI "test3.inp"
#define FO "test3.out"

vector<int> key;
vector<bool> mstSet;
vector<int> parent;

int minKey(vector<int> &Key, vector<bool> &mstSet)
{
    int min = INT_MAX, GTmin=-1;

    for (int i = 0; i < mstSet.size(); i++)
    {
        if (mstSet[i] == false && key[i] < min)
        {
            min = Key[i], GTmin = i;
        }
    }
    return GTmin;
}

vector<tuple<int, int, int>> mst;
int TotalWeight=0;

void PrimMST(vector<vector<pair<int, int>>> &adj, int n) {
    key.assign(n + 1, INT_MAX);
    mstSet.assign(n + 1, false);
    parent.assign(n + 1, -1);

    key[1] = 0;

    for (int count = 1; count <= n; count++) {
        int j = minKey(key, mstSet);
        if (j == -1) break;
        mstSet[j] = true;
        for (auto &[v, w] : adj[j]) {
            if (!mstSet[v] && w < key[v]) {
                key[v] = w;
                parent[v] = j;
            }
        }
    }

    for (int k = 2; k <= n; k++) {
        if (parent[k] != -1) {
            mst.push_back({parent[k], k, key[k]});
            TotalWeight += key[k];
        }
    }
}

int main()
{
    ifstream fi(FI);

    int n, m;
    fi >> n >> m;

    vector<vector<pair<int, int>>> adj(n+1);
    for (int i = 0; i < m; i++)
    {
        int u,v,w;
        fi>>u>>v>> w;

        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }
    PrimMST(adj,n);

    cout << mst.size() << " " << TotalWeight<<endl;
    for (auto [u, v, w] : mst)
    {
        cout << u << " " << v << " " << w << endl;
    }

    return 0;
}