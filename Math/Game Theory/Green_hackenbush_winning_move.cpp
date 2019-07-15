#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 1234567890

vector<array<int,2>>g[100001];
int nim[100001];
int winningNim[100001];

int dfs(int c, int p)
{
    for(auto&u:g[c])
        if(u[1]!=p)
        {
            int nim_of_subtree = 1 + dfs(u[1],c);
            nim[c]^=nim_of_subtree;
        }

    return nim[c];
}

int winningEdge;

void dfs2(int c, int p, int need = 0)
{
    for(auto&u:g[c])
        if(u[1]!=p)
        {
            int nim_of_subtree = 1 + nim[u[1]];
            int want_for_child = (need^nim[c]^nim_of_subtree) - 1;

            if(want_for_child == -1)
                winningEdge = u[0];

            dfs2(u[1], c, want_for_child);
        }
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n,r;
    cin>>n>>r;
    for(int i=1; i<n; i++)
    {
        int u,v;
        cin>>u>>v;
        g[u].push_back({i,v});
        g[v].push_back({i,u});
    }

    int nimSum = dfs(r,0);
    cout<<(nimSum ? 1 : 2)<<"\n";

    dfs2(r,0,0);

    if(nimSum)
    cout<<winningEdge<<"\n";
}
