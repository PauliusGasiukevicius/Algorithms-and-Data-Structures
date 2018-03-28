#include <bits/stdc++.h>
using namespace std;
#define ll long long

//BFS used for SSSP to generate level graph
bool BFS(vector<vector<ll>>G[], vector<int>&L, int s, int t)
{
    queue<int>q;
    q.push(s);
    L[s]=1;

    while(!q.empty())
    {
        int c = q.front();
        q.pop();

        for(auto& v : G[c])
            if(v[1] < v[2] && L[v[0]]==0)
            L[v[0]]=L[c]+1,q.push(v[0]);
    }
    return L[t];
}

//flow is essentially dfs that finds augmenting paths on level graph
ll flow(vector<vector<ll>>G[], vector<int>&L, vector<int>&nxt, int c, int t, ll f)
{
    if(c==t)return f;
    for(nxt[c]; nxt[c]<G[c].size(); nxt[c]++)
    {
        int j= nxt[c];
        int u = G[c][j][0];
        if(L[u] == L[c]+1 && G[c][j][1] < G[c][j][2])
    {
        ll F = flow(G,L,nxt,G[c][j][0],t, min(f,G[c][j][2]-G[c][j][1]) );
        if(F > 0) //if after all recursions we actually find augmenting path
        {
            int rev = G[c][j][3];
            G[c][j][1]+=F;
            G[u][rev][1]-=F;
            return F;
        }
    }
    }

    return 0LL; // no more augmenting paths
}

ll Dinic(vector<vector<ll>>G[], int s, int t, int n)
{
    if(s==t)return LLONG_MAX;
    ll maxFlow = 0;
    vector<int>L(n+1);

    while(BFS(G,L,s,t))
    {
        ll f = 0;
        vector<int>nxt(n+1,0); // this is used to avoid cycles?
        while(ll F = flow(G,L,nxt,s,t,666666666))f+=F; //infinity constant here might be too low
        fill(L.begin(),L.end(),0);
        maxFlow+=f;
    }
    return maxFlow;
}

int main()
{
    ios::sync_with_stdio(0);
    int n,m;
    cin>>n>>m;
    vector<vector<ll>>G[5001]; //[to][flow][cap][reverseID]

    for(int i=0,u,v,c; i<m; i++)
    {
        cin>>u>>v>>c;
        int ru = G[u].size();
        int rv = G[v].size();
        G[u].push_back({v,0,c,rv});
        G[v].push_back({u,0,c,ru}); //flow is 0 cause edges are undirected
    }

    cout<<Dinic(G,1,n,n)<<"\n";
}
