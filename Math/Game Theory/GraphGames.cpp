#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 1234567890

void dfs(int c, vector<vector<int>>&g, vector<vector<int>>&rg, vector<string>&res, vector<int>&cntOfWinningEdgesIncoming)
{
    for(auto&u:rg[c])
        if(res[u]=="DRAW" && res[c]=="SECOND")
    {
        res[u]="FIRST";
        dfs(u,g,rg,res,cntOfWinningEdgesIncoming);
    }
    else if(res[u]=="DRAW" && res[c]=="FIRST" && ++cntOfWinningEdgesIncoming[u]==g[u].size())
    {
        res[u]="SECOND";
        dfs(u,g,rg,res,cntOfWinningEdgesIncoming);
    }
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n,m;
    while(cin>>n>>m)
    {
        vector<vector<int>>g(n+1),rg(n+1);
        vector<int>cnt(n+1);
        vector<string>res(n+1,"DRAW");

        for(int i=0; i<m; i++)
        {
            int u,v;
            cin>>u>>v;
            g[u].push_back(v);
            rg[v].push_back(u);
        }

        for(int i=1; i<=n; i++)
            if(g[i].empty())
                {
                    res[i]="SECOND";
                    dfs(i,g,rg,res,cnt);
                }

        for(int i=1; i<=n; i++)
            cout<<res[i]<<"\n";
        cout<<"\n";
    }
}
