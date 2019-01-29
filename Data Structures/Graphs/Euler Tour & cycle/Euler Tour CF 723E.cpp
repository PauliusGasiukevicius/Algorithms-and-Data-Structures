#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo INT_MAX/2

void dfs(vector<multiset<int>>&G, int c, multiset<pair<int,int>>&E, vector<pair<int,int>>&ats)
{
    while(!G[c].empty())
    {
        int u = *G[c].begin();
        G[c].erase(G[c].find(u));
        G[u].erase(G[u].find(c));
        if(E.count({c,u}))
            {
                ats.push_back({c,u});
                E.erase(E.find({c,u}));
                E.erase(E.find({u,c}));
            }
        dfs(G,u,E,ats);
    }
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    int t,n,m;
    cin>>t;
    while(t--)
    {
        cin>>n>>m;
        vector<int>odd;
        vector<multiset<int>>G(n+1);
        multiset<pair<int,int>>E;
        vector<pair<int,int>>ats;
        for(int i=0; i<m; i++)
        {
            int u,v;
            cin>>u>>v;
            G[u].insert(v);
            G[v].insert(u);
            E.insert({u,v});
            E.insert({v,u});
        }

        for(int i=1; i<=n; i++)
            if(G[i].size()&1)odd.push_back(i);

        for(int i=0; i<odd.size(); i+=2)
        {
            int u = odd[i];
            int v = odd[i+1];
            G[u].insert(v);
            G[v].insert(u);
        }

        for(int i=1; i<=n; i++)
            if(!G[i].empty())
                dfs(G,i,E,ats);

        cout<<(n-odd.size())<<"\n";
        for(auto&p:ats)
            cout<<p.first<<" "<<p.second<<"\n";
    }
}
