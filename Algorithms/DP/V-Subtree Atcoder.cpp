#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

ll n,m;
vector<int>g[100001];
vector<ll>pf[100001];
vector<ll>sf[100001];
ll UP[100001];
ll DOWN[100001];

void dfs(int c, int p = 0)
{
    DOWN[c]=1;

    for(auto&u:g[c])
        if(u!=p)
    {
        dfs(u,c);
        DOWN[c] = (DOWN[c] * (DOWN[u]+1)) % m;
    }
}

void dfs2(int c, int p=0, ll up = 1)
{
    UP[c]=up;

    for(int i=0; i<g[c].size(); i++)
        if(g[c][i]==p)
    {
        swap(g[c][i],g[c].back());
        g[c].pop_back();
        break;
    }

    pf[c][0]=sf[c][g[c].size()]=1;

    for(int i=0; i<g[c].size(); i++)
        pf[c][i+1]=(pf[c][i]*(DOWN[g[c][i]]+1))%m;

    for(int i=g[c].size()-1; i>=0; i--)
        sf[c][i]=(sf[c][i+1]*(DOWN[g[c][i]]+1))%m;

    for(int i=0; i<g[c].size(); i++)
    {
        ll ways = (pf[c][i] * sf[c][i+1])%m;
        ways = (ways * up)%m;
        dfs2(g[c][i],c,(ways+1)%m);
    }
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin>>n>>m;

    for(int i=1; i<n; i++)
    {
        int u,v;
        cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    for(int i=1; i<=n; i++)
        pf[i].resize(g[i].size()+2),sf[i].resize(g[i].size()+2);

    dfs(1);
    dfs2(1);

    for(int i=1; i<=n; i++)
        {
            //cout<<i<<" "<<DOWN[i]<<" "<<UP[i]<<"\n";
            cout<<(DOWN[i]*UP[i])%m<<"\n";
        }
}
