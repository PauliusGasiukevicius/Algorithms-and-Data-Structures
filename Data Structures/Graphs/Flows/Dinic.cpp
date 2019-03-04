#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

//BFS used for SSSP to generate level graph
bool BFS(vector<vector<array<ll,4>>>&G, vector<int>&L, int s, int t)
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
ll flow(vector<vector<array<ll,4>>>&G, vector<int>&L, vector<int>&nxt, int c, int t, ll f)
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

ll Dinic(vector<vector<array<ll,4>>>&G, int s, int t, int n)
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

//[to][flow][cap][reverseID]

void AddEdge(vector<vector<array<ll,4>>>&G, int u, int v, int cap)
{
        int ru = G[u].size();
        int rv = G[v].size();
        G[u].push_back({v,0,cap,rv});
        G[v].push_back({u,0,0,ru});
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int t,n,m,k;
    cin>>t;
    while(t--)
    {
        cin>>n>>m>>k;
        vector<vector<array<ll,4>>>G(n+m+3);
        vector<vector<array<int,2>>>g(n+m+3);
        vector<int>ats(m+1);
        int source = n+m+1;
        int sink = n+m+2;

        for(int i=0; i<m; i++)
        {
            int u,v;
            cin>>u>>v;
            g[u].push_back({v,i+1});
            g[v].push_back({u,i+1});
        }

        int need = 0;

        for(int i=1; i<=n; i++)
            if(g[i].size() > k)
            {
                need+=2*(g[i].size()-k);
                AddEdge(G, source, i, 2*(g[i].size()-k));
            }

        for(int i=1; i<=n; i++)
            for(auto&u : g[i])
            AddEdge(G,i,n+u[1],1);

        for(int i=n+1; i<=n+m; i++)
            AddEdge(G,i,sink,1);

        if(Dinic(G,source,sink,n+m+3)==need)
        {
            int nxt = 1, add = 0;

            for(int i=1; i<=n; i++)
                for(auto&e : G[i])
                if(e[1] > 0)
                {
                    ats[e[0]-n]=nxt;
                    nxt+=add;
                    add^=1;
                }

            for(int i=1; i<=n; i++)
                for(auto&e:g[i])
                    if(ats[e[1]]==0)
                    ats[e[1]]=nxt++;
        }

        for(int i=1; i<=m; i++)
            cout<<ats[i]<<(i==m?"\n":" ");
    }
}
