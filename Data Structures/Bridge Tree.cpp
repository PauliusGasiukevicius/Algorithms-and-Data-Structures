#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666
//CF 555E
const int N = 200001;
const int lgN = 18;
int n,m,q,tt=0;
int disc[N],low[N],up[N][lgN+1],P[N],depth[N], in[N], out[N], UV[N], VU[N], parent[N];
vector<int>G[N],T[N],D[N+1];
vector<pair<int,int>>bridges;
map<pair<int,int>,int>mp;

int Find(int u)
{
    return P[u]<0 ? u : P[u]=Find(P[u]);
}

void Union(int u, int v)
{
    u = Find(u);
    v = Find(v);
    if(u==v)return;
    P[u]=v;
}

void dfs(int c, int p = -1)
{
    disc[c]=low[c]=++tt;
    for(auto&u :G[c])
        if(disc[u]==0)
    {
        dfs(u,c);
        low[c]=min(low[c],low[u]);
        if(low[u] > disc[c] && mp[minmax(c,u)]==1)bridges.push_back({c,u});
        else Union(c,u);
    }else if(u!=p)low[c]=min(low[c],disc[u]);
}

void dfs2(int c, int p = 0)
{
    in[c]=++tt;
    parent[c]=p;
    depth[c] = depth[p]+1;
    D[depth[c]].push_back(c); //saves tree by levels

    up[c][0]=p;
    for(int i=1; i<=lgN; i++)
        up[c][i]=up[up[c][i-1]][i-1];

    for(auto& u : T[c])
        if(u!=p)
        dfs2(u,c);

    out[c]=++tt;
}

void buildBridgeTree()
{
    for(auto&b:bridges)
    {
        int u = Find(b.first);
        int v = Find(b.second);
        T[u].push_back(v);
        T[v].push_back(u);
    }
    tt=1;
    out[0]=oo;
    depth[0]=1;

    for(int i=1; i<=n; i++)
        if(P[i] < 0 && depth[i]==0)
        dfs2(i);
}

bool ancestor(int u, int v)
{
    return in[u]<=in[v] && out[u]>=out[v];
}

int LCA(int u, int v)
{
    if(ancestor(u,v))return u;
    if(ancestor(v,u))return v;

    for(int i=lgN; i>=0; i--)
        if(!ancestor(up[u][i],v))
        u=up[u][i];

    return up[u][0];
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m>>q;
    fill(P,P+N,-1);
    for(int i=0; i<m; i++)
    {
        int u,v;
        cin>>u>>v;
        G[u].push_back(v);
        G[v].push_back(u);
        mp[minmax(u,v)]++;
    }

    for(int i=1; i<=n; i++)
        if(disc[i]==0)
        dfs(i);

    buildBridgeTree();

    while(q--)
    {
        int u,v;
        cin>>u>>v;
        u = Find(u);
        v = Find(v);
        int lca = LCA(u,v);
        if(lca==0)return cout<<"No",0; //nodes not in same tree

        int d1 = depth[u]-depth[lca];//how many edges need to be u->v going from u to lca
        int d2 = depth[v]-depth[lca];//how many edges need to be u<-v going from v to lca
        UV[u]=max(UV[u],d1);
        VU[v]=max(VU[v],d2);
    }

    for(int d = N; d>1; d--)
        for(auto& c : D[d])
        {
            if(min(UV[c],VU[c]) > 0)return cout<<"No",0;
            int u = parent[c];
            UV[u]=max(UV[u],UV[c]-1);
            VU[u]=max(VU[u],VU[c]-1);
        }
    cout<<"Yes\n";
}
