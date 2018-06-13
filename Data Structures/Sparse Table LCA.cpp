#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 1666666666

const int N = 10001;
const int lgN = 25;
int t,n,u,v,w,cs=1,tt,up[N][lgN+1],in[N],out[N],depth[N],sum[N];
vector<vector<int>>G;
vector<vector<int>>W;

void dfs(int c, int p)
{
    in[c]=++tt;
    up[c][0] = p;
    depth[c] = depth[p] + 1;

    for(int i=1; i<=lgN; i++)
        up[c][i]=up[up[c][i-1]][i-1];

    for(int i=0; i<G[c].size(); i++)
        if(G[c][i]!=p)
    {
       // sum[G[c][i]]+=W[c][i];
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

int main()
{
    ios::sync_with_stdio(0);
    cin>>t;
    while(t--)
    {
        cin>>n;
        G.clear();
        G.resize(n+1);
        tt=0;

        for(int i=1; i<=n; i++)
        {
            int m;
            cin>>m;
            while(m--)
            {
                cin>>u;
                G[i].push_back(u);
                G[u].push_back(i);
            }
        }

        dfs(1,1);
        int q;
        cin>>q;
        cout<<"Case "<<cs++<<":\n";
        while(q--)
        {
            cin>>u>>v;
            cout<<LCA(u,v)<<"\n";
        }
    }
}
