#include <bits/stdc++.h>
using namespace std;

int low[100001];
int disc[100001];
int P[100001];

void DFS(int c, vector<int>G[], vector<vector<vector<int>>>&BC, stack<vector<int>>&S)
{
    static int tm = 1;
    disc[c]=low[c]=tm++;

    for(int&u:G[c])
        if(u!=P[c])
    {
        S.push({c,u});

    if(disc[u]==0)
    {
        P[u]=c;
        DFS(u,G,BC,S);
        low[c]=min(low[c],low[u]);
    }
    else if(u!=P[c])
        low[c]=min(disc[u],low[c]);

        if(low[u] >= disc[c])
        {
            vector<vector<int>>B;
            vector<int>e = {c,u};
            vector<int>e2 = {u,c};
            while(S.top()!=e && S.top()!=e2)
                B.push_back(S.top()),S.pop();
            B.push_back(S.top());
            S.pop();
            BC.push_back(B);
        }
    }
}

int main()
{
    ios::sync_with_stdio(0);
    int n,m;
    cin>>n>>m;
    vector<int>G[100001];
    map<pair<int,int>,int>mp;

    for(int i=0,u,v; i<m; i++)
        cin>>u>>v,G[u].push_back(v),G[v].push_back(u),mp[{u,v}]=mp[{v,u}]=i+1;

    vector<vector<vector<int>>>BC;

    for(int i=1; i<=n; i++)
        if(disc[i]==0)
    {
        stack<vector<int>>S;
        DFS(i,G,BC,S);
    }

    set<int>ats;

    for(auto&b : BC)
    {
        set<int>v;
        set<int>E;
        for(auto&e:b)
            v.insert(e[0]),v.insert(e[1]),E.insert(mp[{e[0],e[1]}]);

        if(v.size()==E.size())
            for(auto e:E)
            ats.insert(e);
    }

    cout<<ats.size()<<"\n";
    for(auto x : ats)cout<<x<<" ";
}
