#include <iostream>
#include <algorithm>
#include <fstream>

using namespace std;

#define FI "test.inp"
#define FO "test.out"

vector<vector<int>> adj;
vector<bool> visited;
vector<int> tree;
vector<pair<int, int>> adjtree;

// Mã real

void dfs_spanningtree(int start)
{
    visited[start] = true;
    tree.push_back(start);
    for (int u : adj[start])
    {
        if (visited[u] == false)
        {
            adjtree.push_back({start, u});
            dfs_spanningtree(u);
            
        }
    }
}

int main()
{
    ifstream fi(FI);

    int n, m;

    fi >> n >> m;
    fi.ignore();

    adj.resize(n + 1);
    visited.resize(n + 1, false);

    

    int u, v;
    for (int i = 0; i < m; i++)
    {
        fi >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    dfs_spanningtree(1);
   


    cout << adjtree.size() << endl;
    for (auto [u, v] : adjtree)
    {
        cout <<u<<" "<<v<< endl;
    }

    return 0;
}