#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

const int N = 200001;
const int lgN = 25;
vector<int>P(N,-1);
vector<int>G[N]; //stores MST tree
vector<int>W[N]; //stores MST edges weight
int up[N][lgN+1];
ll mx[N][lgN+1];
int in[N],out[N];
int tt=0;

int Find(int u)
{
    return P[u] < 0 ? u : P[u]=Find(P[u]);
}

void Union(int u, int v)
{
    u=Find(u);
    v=Find(v);
    if(u!=v)P[u]=v;
}

void dfs(int c, int p)
{
    in[c]=++tt;
    up[c][0] = p;

    for(int i=1; i<=lgN; i++)
    {
        up[c][i]=up[up[c][i-1]][i-1];
        mx[c][i]=max(mx[c][i-1],mx[up[c][i-1]][i-1]);
    }

    for(int i=0; i<G[c].size(); i++)
        if(G[c][i] != p)
    {
        mx[G[c][i]][0] = W[c][i];
        dfs(G[c][i],c);
    }
    out[c]=++tt;
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

ll maxEdge(int u, int v)
{
    int lca = LCA(u,v);
    ll ats = 0;

    for(int i=lgN; i>=0; i--)
        if(!ancestor(up[u][i],lca))
    {
        ats=max(ats,mx[u][i]);
        u=up[u][i];
    }

    for(int i=lgN; i>=0; i--)
        if(!ancestor(up[v][i],lca))
    {
        ats=max(ats,mx[v][i]);
        v=up[v][i];
    }

    if(u!=lca)ats=max(ats,mx[u][0]);
    if(v!=lca)ats=max(ats,mx[v][0]);

    return ats;
}

int main()
{
    ios::sync_with_stdio(0);
    int n,m;
    cin>>n>>m;
    vector<vector<ll>>E(m,vector<ll>(4));
    vector<ll>ats(m,-1);
    for(int i=0; i<m; i++)
        cin>>E[i][1]>>E[i][2]>>E[i][0],E[i][3]=i;

    sort(E.begin(),E.end());

    ll mst = 0;
    for(int i=0; i<m; i++)
        if(Find(E[i][1]) != Find(E[i][2]))
        {
            Union(E[i][1],E[i][2]);
            mst+=E[i][0];
            ats[E[i][3]]=0;
            G[E[i][1]].push_back(E[i][2]);
            G[E[i][2]].push_back(E[i][1]);
            W[E[i][1]].push_back(E[i][0]);
            W[E[i][2]].push_back(E[i][0]);
        }

    dfs(1,1);

    for(int i=0; i<m; i++)
        if(ats[E[i][3]]==0)ats[E[i][3]]=mst;
    else
        {
            ats[E[i][3]] = mst - maxEdge(E[i][1],E[i][2]) + E[i][0];
            //cout<<"Max edge between "<<E[i][1]<<" "<<E[i][2]<<" = "<<maxEdge(E[i][1],E[i][2]) << "\n";
        }

    for(auto&x:ats)
        cout<<x<<"\n";
}
