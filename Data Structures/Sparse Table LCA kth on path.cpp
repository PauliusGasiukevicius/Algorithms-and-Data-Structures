#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 1666666666

const int N = 10001;
const int lgN = 25;
int t,n,u,v,w,k,cs=1,tt,up[N][lgN+1],in[N],out[N],depth[N],sum[N];
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
        sum[G[c][i]]+=W[c][i] + sum[c];
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

int dist(int u, int v)
{
    return sum[u] + sum[v] - 2 * sum[LCA(u,v)];
}

int kth(int u, int v, int k)
{
    int lca = LCA(u,v);
    if(depth[u] - depth[lca] < k)
    {
        k = depth[u] + depth[v] - 2*depth[lca] - k + 1;
        swap(u,v);
    }else k--;
    //now k means how much up we need to jump from node u

    for(int i=lgN; i>=0; i--)
        if(k >= (1<<i))
        u=up[u][i],k-=(1<<i);
    return u;
}

int main()
{
    ios::sync_with_stdio(0);
    cin>>t;
    while(t--)
    {
        cin>>n;
        tt=0;
        G.clear();
        W.clear();
        G.resize(n+1);
        W.resize(n+1);
        fill(sum,sum+N,0);
        for(int i=1; i<n; i++)
        {
            cin>>u>>v>>w;
            G[u].push_back(v);
            W[u].push_back(w);
            G[v].push_back(u);
            W[v].push_back(w);
        }

        dfs(1,1);
        string s;

        while(cin>>s && s[1]!='O')
            if(s[0]=='D')
            {
                cin>>u>>v;
                cout<<dist(u,v)<<"\n";
            }
            else
            {
                cin>>u>>v>>k;
                cout<<kth(u,v,k)<<"\n";
            }

    }
}
