#include <bits/stdc++.h>
using namespace std;
#define ll long long

void dfs(int c, vector<int>&low, vector<int>&disc, vector<pair<int,int>>G[],
         vector<int>&inStack,vector<int>&S,vector<vector<int>>&SCC)
{
    static int tm = 1;
    low[c]=disc[c]=tm++;
    inStack[c]=1;
    S.push_back(c);

    for(auto&u:G[c])
    if(disc[u.second]==0)
    {
        dfs(u.second,low,disc,G,inStack,S,SCC);
        low[c]=min(low[c],low[u.second]);
    }else if(inStack[u.second])low[c]=min(low[c],disc[u.second]);

    if(disc[c]==low[c])
    {
        vector<int>comp;
        inStack[c]=0;
        comp.push_back(c);
        while(S.back()!=c)
            inStack[S.back()]=0,comp.push_back(S.back()),S.pop_back();
        S.pop_back();
        SCC.push_back(comp);
    }
}

int main()
{
    ios::sync_with_stdio(0);
    int t,n,m,cs=1,u,v,w;
    cin>>t;
    while(t--)
    {
        cin>>n>>m;
        vector<pair<int,int>>G[51];
        for(int i=0; i<m; i++)
        {
            cin>>u>>v>>w;
            int found = 0;
            for(int j=0; j<G[u].size(); j++)
                if(G[u][j].second==v)
                found=1,G[u][j].first=min(G[u][j].first,w);
            if(!found)
            G[u].push_back({w,v});
        }
        vector<int>low(n+1),disc(n+1),inStack(n+1),S;
        vector<vector<int>>SCC;
        for(int i=1; i<=n; i++)
            if(disc[i]==0)dfs(i,low,disc,G,inStack,S,SCC);

        //now graph is split into SCC, hence we can apply karp

        vector<int>ID(n+1);
        for(int i=0; i<SCC.size(); i++)
            for(int j=0; j<SCC[i].size(); j++)
            ID[SCC[i][j]]=i;

        double best = DBL_MAX;

        for(int k=0; k<SCC.size(); k++)
        {
            vector<pair<int,int>>T[51];
            int nxt=1;
            int mp[51]={};
            for(int i=1; i<=n; i++)
                for(int j=0; j<G[i].size(); j++)
                if(ID[i]==k && ID[G[i][j].second]==k)
                {
                    if(mp[i]==0)mp[i]=nxt++;
                    if(mp[G[i][j].second]==0)mp[G[i][j].second]=nxt++;
                    T[mp[i]].push_back({G[i][j].first,mp[G[i][j].second]});
                }

            vector<vector<ll>>DP(51,vector<ll>(51,LLONG_MAX/100));
            DP[1][0]=0;

            for(int j=1; j<=n; j++)
            for(int i=1; i<nxt; i++)
                for(auto&p : T[i])
                    DP[p.second][j]=min(DP[p.second][j],p.first + DP[i][j-1]);

            int N = nxt-1;
            vector<double>MX(N+1);
            for(int i=1; i<=N; i++) // vertex
            for(int j=0; j<=N-1; j++)
                MX[i]=max(MX[i],1.0*(DP[i][N]-DP[i][j])/(1.0*N-j));

            for(int j=1; j<=N; j++)
                best=min(best,MX[j]);
        }

        if(best > 1e17)
            cout<<"Case #"<<cs++<<": No cycle found.\n";
        else
            cout<<"Case #"<<cs++<<": "<<setprecision(2)<<fixed<<best<<"\n";
    }
}
