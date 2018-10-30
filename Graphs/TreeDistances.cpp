#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666
vector<int>g[500005];
int cnt[500005];
ll ats[500005];
int n;

ll dfs(int c, int p, int d=0)
{
    cnt[c]=1;
    ats[c]=d;
    for(auto&u:g[c])
        if(u!=p)
        ats[c]+=dfs(u,c,d+1),cnt[c]+=cnt[u];
    return ats[c];
}
/*
After first dfs, ans[root] stores the sum of distances for root node and all paths that start at root
So if we explore some node u thats a child of root
we can see that sum of path of its subtree will be less by cnt[u] - subtree size of u
because we are one closer to all those nodes
similarly all other nodes are 1 more edge away
so ats[u]=ats[root] - cnt[u] + (n-cnt[u])
using induction it`s easy to see why it works for all nodes
*/
void dfs2(int c, int p)
{
    for(auto&u:g[c])
        if(u!=p)
    {
        ats[u] = ats[c] - cnt[u] + (n-cnt[u]);
        dfs2(u,c);
    }
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n;
    for(int i=1; i<n; i++)
    {
        int u,v;
        cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    dfs(1,0);
    dfs2(1,0);
    for(int i=1; i<=n; i++)
        cout<<ats[i]<<" ";
}
