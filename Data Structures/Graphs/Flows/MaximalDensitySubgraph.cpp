#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 1234567890

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
        while(ll F = flow(G,L,nxt,s,t,oo))f+=F; //infinity constant here might be too low
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

int n,m,source,sink;
vector<array<int,2>>edges;

bool check(int top, int bot) //checks if some value x = top/bot is maximum density of the graph
{
    vector<vector<array<ll,4>>>g(n+m+2);
    //edges s->node are x initially, we multiply all edges by bot so it becomes top
    for(int i=1; i<=n; i++)AddEdge(g,source,i,top);
    //edges edgeNode->t are 1 initially, we multiply all edges by bot so it becomes bot
    for(int j=1; j<=m; j++)AddEdge(g,n+j,sink,bot);
    //All other edges are from nodes to
    for(int j=0; j<m; j++)
    {
        AddEdge(g,edges[j][0],j+1+n,oo);
        AddEdge(g,edges[j][1],j+1+n,oo);
    }

    return m*bot > Dinic(g,source,sink,n+m+2);
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin>>n>>m;
    source = 0, sink = n+m+1;

    for(int i=1; i<=m; i++)
    {
        int u,v;
        cin>>u>>v;
        edges.push_back({u,v});
    }

    vector<array<int,2>>fr; //fractions
    for(int i=0; i<=m; i++)
        for(int j=1; j<=n; j++)
        fr.push_back({i,j});

    sort(fr.begin(),fr.end(),[](array<int,2>a, array<int,2>b){return a[0]*b[1] < b[0]*a[1];});
    int l = 0, r = fr.size();

    while(l < r)
    {
        int x = (l+r)/2;
        if(check(fr[x][0],fr[x][1]))l=x+1;
        else r=x;
    }

    int top = fr[r][0], bot = fr[r][1];
    //cout<<top<<" "<<bot<<"\n";
    vector<vector<array<ll,4>>>g(n+m+2);
    //edges s->node are x initially, we multiply all edges by bot so it becomes top
    for(int i=1; i<=n; i++)AddEdge(g,source,i,top);
    //edges edgeNode->t are 1 initially, we multiply all edges by bot so it becomes bot
    for(int j=1; j<=m; j++)AddEdge(g,n+j,sink,bot);
    //All other edges are from nodes to
    for(int j=0; j<m; j++)
    {
        AddEdge(g,edges[j][0],j+1+n,oo);
        AddEdge(g,edges[j][1],j+1+n,oo);
    }

    Dinic(g,source,sink,n+m+2);
    vector<int>res,L(n+m+2);
    BFS(g,L,source,sink);

    for(int i=1; i<=n; i++)
        if(L[i]==0)
        res.push_back(i);

    //cout<<"Max density is: "<<top<<" "<<bot<<"\n";
    if(res.empty())res={1};
    sort(res.begin(),res.end());
    cout<<res.size()<<"\n";
    for(auto&x:res)cout<<x<<"\n";
}
