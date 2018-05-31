#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

void dfs(vector<int>G[], vector<int>&A, int c, vector<int>&visited)
{
    visited[c]=1;
    for(auto&u:G[c])
        if(!visited[u])
            dfs(G,A,u,visited);
    A.push_back(c);
}

int main()
{
    ios::sync_with_stdio(0);
    int t,n,m;
    cin>>t;
    while(t--)
    {
        cin>>n>>m;
        vector<int>G[1001];
        vector<int>R[1001];

        for(int i=0,u,v; i<m; i++)
            cin>>u>>v,G[u].push_back(v),R[v].push_back(u);

        vector<int>A,visited(n+1);
        for(int i=1; i<=n; i++)
            if(!visited[i])
            dfs(G,A,i,visited);

        vector<vector<int>>SCC;
        vector<int>ID(1001);
        int nxt = 1;

        fill(visited.begin(),visited.end(),0);
        for(int i=A.size()-1; i>=0; i--)
            if(!visited[A[i]])
        {
            visited[A[i]]=1;
            vector<int>comp;
            dfs(R,comp,A[i],visited);
            SCC.push_back(comp);
            for(auto&u:comp)ID[u]=nxt;
            nxt++;
        }

        set<pair<int,int>>E;
        vector<int>SCCG[1001];

        for(int i=1; i<=n; i++)
            for(auto&u : G[i])
        if(ID[i] != ID[u] && !E.count({ID[i],ID[u]}))
            SCCG[ID[i]].push_back(ID[u]), E.insert({ID[i],ID[u]});

        vector<int>topo;
        fill(visited.begin(),visited.end(),0);
        for(int i=1; i<nxt; i++)
            if(!visited[i])
            dfs(SCCG,topo,i,visited);

        reverse(topo.begin(),topo.end());
        vector<int>DP(1001);

        for(auto& c : topo)
        {
            DP[c]+=SCC[c-1].size();
            for(auto& u : SCCG[c])
                DP[u]=max(DP[u],DP[c]);
        }

        cout<< *max_element(DP.begin(),DP.end()) << "\n";
    }
}
