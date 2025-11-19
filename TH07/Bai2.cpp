#include<iostream>
#include<algorithm>
#include<queue>
#include<fstream>

using namespace std;

#define FI "test1.inp"
#define FO "test1.out"

vector<vector<int>>adj;
vector<bool>visited;
vector<int>tree;
vector<pair<int,int>>adjtree;


void bfs_spanningtree(int start)
{
    queue<int>q;
    visited[start]=true;
    q.push(start);

    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        tree.push_back(u);
      

        for (int v:adj[u])
        {
            if (!visited[v])
            {
                visited[v]=true;
                q.push(v);
                adjtree.push_back({u,v});
            }
        }
    }
}


int main(){
    ifstream fi (FI);

    int n,m;

    fi >> n >>m;

    adj.resize(n+1);
    visited.resize(n+1,false);
   

    int u,v;
    
    for (int i=1;i<=m;i++)
    {
        fi >> u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    bfs_spanningtree(1);



    cout<<tree.size()-1<<endl;

    for (auto &[u,v]:adjtree)
    {
        cout << u << " " <<v<<endl;
    }


return 0;


}
