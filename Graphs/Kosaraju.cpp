#include <bits/stdc++.h>
using namespace std;
#define ll long long

void dfs(vector<int>G[], int c, vector<int>&A, vector<int>&visited)
{
    visited[c]=1;
    for(auto&u:G[c])
        if(!visited[u])dfs(G,u,A,visited);
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
       vector<int>G[n+1];
       vector<int>R[n+1];

       for(int i=0,u,v; i<m; i++)
        cin>>u>>v,G[u].push_back(v),R[v].push_back(u);
        vector<int>A,visited(n+1);
        for(int i=1; i<=n; i++)
            if(!visited[i])dfs(G,i,A,visited);

        vector<vector<int>>SCC;
        vector<int>ID(n+1);
        vector<int>in(n+1);
        fill(visited.begin(),visited.end(),0);

        for(int i=A.size()-1; i>=0; i--)
        if(!visited[A[i]])
        {
            vector<int>B;
            dfs(R,A[i],B,visited);
            SCC.push_back(B);
            for(auto&u:SCC.back())ID[u]=SCC.size()-1;
        }

        for(int i=1; i<=n; i++)
            for(auto&u:G[i])
            if(ID[i]!=ID[u])in[ID[u]]++;

        int ats = 0;
        for(int i=0; i<SCC.size(); i++)
            if(in[i]==0)ats++;

        cout<<ats<<"\n";
   }
}
