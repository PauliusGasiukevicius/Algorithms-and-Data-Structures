#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 1234567890

vector<int>g[200005];
ll n,a[200005],dist[200005],sum[200005],sz[200005],res,currentSum;

void dfs(int c, int p = -1)
{
    dist[c]=(p==-1 ? 0 : dist[p]+1);
    sz[c]=1;
    sum[c]+=a[c];

    for(auto&u:g[c])
        if(u!=p)
    {
        dfs(u,c);
        sz[c]+=sz[u];
        sum[c]+=sum[u];
    }
    currentSum+=dist[c]*a[c];
}

void dfs2(int c, int p = -1)
{
    res=max(res,currentSum);
    for(auto&u:g[c])
        if(u!=p)
    {
        //we switch root from c to u, so on subtree of u all nodes will become one step closer,
        // so we lose sumOf(a[i]) for this subtree
        // Also all nodes moving up to c from u will become one step further away
        // so we also gain (sumOfAll(a[i]) - sumOf(a[i]) for this subtree)
        currentSum-=sum[u];
        currentSum+=(sum[1]-sum[u]);
        dfs2(u,c);
        currentSum+=sum[u];
        currentSum-=(sum[1]-sum[u]);
    }
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=1; i<=n; i++)
        cin>>a[i];

    for(int i=1; i<n; i++)
    {
        int u,v;
        cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    dfs(1);
    dfs2(1);
    cout<<res<<"\n";
}
