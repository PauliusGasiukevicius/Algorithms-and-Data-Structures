#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo INT_MAX/2

void dfs(vector<multiset<int>>&G, int c, map<array<int,2>,int>&mp, vector<array<int,2>>&E)
{
    while(!G[c].empty())
    {
    int u = *G[c].begin();
    G[c].erase(G[c].find(u));
    G[u].erase(G[u].find(c));
    if(!mp.count({c,u}))
        {
            int idx = mp[{u,c}];
            swap(E[idx][0],E[idx][1]);
        }
    mp.erase({c,u});
    dfs(G,u,mp,E);
    }
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    int n,m;
    cin>>n>>m;
    vector<multiset<int>>G(n+1);
    map<array<int,2>,int>mp;
    vector<array<int,2>>E(m);

    for(auto&e:E)
    {
        cin>>e[0]>>e[1];
        int idx = mp.size();
        mp[e]=idx;
        G[e[1]].insert(e[0]);
        G[e[0]].insert(e[1]);
    }

    bool ok = 1;
    for(int i=1; i<=n; i++)
        if(G[i].size()&1)ok=0;

    bitset<100001>v(0);
    queue<int>q;
    q.push(1);
    while(!q.empty())
    {
        int c = q.front();
        q.pop();
        for(auto u : G[c])
            if(!v[u])
            v[u]=1,q.push(u);
    }

    if(v.count()!=n)ok=0;

    dfs(G,1,mp,E);

    if(ok)
    {
        cout<<"YES\n";
        for(auto&e:E)
            cout<<e[0]<<" "<<e[1]<<"\n";
    }
    else cout<<"NO\n";
}
