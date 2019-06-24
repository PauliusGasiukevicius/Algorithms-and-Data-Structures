#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 1234567890

const int maxW = 1000001;
vector<array<int,3>>edges[maxW+1];
string res[100001];
int P[100001];
int U[100005],V[100005];

int Find(int u)
{
    return P[u] < 0 ? u : P[u] = Find(P[u]);
}

void Union(int u, int v)
{
    u=Find(u);
    v=Find(v);
    if(u==v)return;
    P[u]=v;
}

void dfs(map<int,vector<array<int,2>>>&g, map<int,int>&parent, map<int,int>& low, map<int,int>& disc,
          map<int,int>& visited,vector<int>&bridges,int c)
{
    static int time = 0;
    low[c]=disc[c]=time++;
    visited[c]=1;

    for(auto&e : g[c])
    {
        int u = e[0];

        if(!visited[u])
        {
            parent[u]=c;
            dfs(g,parent,low,disc,visited,bridges,u);

            if(disc[c] < low[u])
                bridges.push_back(e[1]);
            else
                low[c]=min(low[c],low[u]);
        }
        else if(parent[c] != u)
            low[c]=min(low[c],disc[u]);
    }
}


int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n,m;
    cin>>n>>m;
    for(int i=0; i<m; i++)
    {
        int u,v,w;
        cin>>u>>v>>w;
        U[i]=u,V[i]=v;
        edges[w].push_back({u,v,i});
    }

    for(int i=1; i<=n; i++)
        P[i]=-1;

    for(int i=0; i<=maxW; i++)
    {
        map<int,vector<array<int,2>>>g;
        map<array<int,2>,int>edgesCnt;

        for(auto&e : edges[i])
            if(Find(e[0]) == Find(e[1]))res[e[2]]="none";
        else
        {
            int u = Find(e[0]);
            int v = Find(e[1]);
            int id = e[2];
            g[u].push_back({v,id});
            g[v].push_back({u,id});
            edgesCnt[{u,v}]++;
            edgesCnt[{v,u}]++;
            res[id] = "at least one";
        }

        vector<int>bridges;
        map<int,int>low,disc,visited,parent;

        for(auto&p : g)
            if(!visited[p.first])
            dfs(g,parent,low,disc,visited,bridges,p.first);

        for(auto&idx : bridges)
        if(edgesCnt[{Find(U[idx]),Find(V[idx])}] < 2)
            res[idx] = "any";

        for(auto&e : edges[i])
            if(Find(e[0]) != Find(e[1]))
            Union(e[0],e[1]);
    }

        for(int i=0; i<m; i++)
            cout<<res[i]<<"\n";
}
