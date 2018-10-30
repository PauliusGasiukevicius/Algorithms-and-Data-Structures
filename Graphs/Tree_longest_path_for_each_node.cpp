#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666
 
vector<int>G[500005];
int DOWN[500005];
int DOWN2[500005];
int UP[500005];
 
int dfs(int c, int p = 0)
{
    int mx = 0;
    for(auto&u:G[c])
        if(u!=p)
    {
        int val = 1 + dfs(u,c);
        mx = max(mx, val);
        if(DOWN[u]+1 > DOWN[c])
            DOWN2[c]=DOWN[c],DOWN[c]=DOWN[u]+1;
        else DOWN2[c]=max(DOWN2[c],DOWN[u]+1);
    }
    return mx;
}
 
void dfs2(int c, int p = 0)
{
    UP[c]=UP[p]+1;
 
    if(DOWN[c]+1 == DOWN[p])
        UP[c]=max(UP[c], 1+DOWN2[p]);
    else UP[c]=max(UP[c], 1+DOWN[p]);
 
    for(auto&u:G[c])
        if(u!=p)dfs2(u,c);
}
 
int main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    int n;
    cin>>n;
    for(int i=1; i<n; i++)
    {
        int u,v;
        cin>>u>>v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
 
    UP[0]=DOWN2[0]=DOWN[0]=-1;
    dfs(1);
    dfs2(1);
 
    for(int i=1; i<=n; i++)
        cout<<max(UP[i],DOWN[i])<<" ";
}
