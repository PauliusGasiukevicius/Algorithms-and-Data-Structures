#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

vector<array<int,2>>G[200005],R[200005];
vector<int>g[200005];
int v[200005];
int vi[200005];
int can[200005];
ll SP[200005];
int topoID[200005];
vector<int>topo;

void dfs(int c)
{
    vi[c]=1;
    for(auto&u:g[c])
        if(!vi[u])dfs(u);
    topo.push_back(c);
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n,m;
    cin>>n>>m;
    for(int i=0; i<m; i++)
    {
        int u,v,w;
        cin>>u>>v>>w;
        G[u].push_back({w,v});
        R[v].push_back({w,u});
    }

    for(int i=2; i<=n; i++)SP[i]=LLONG_MAX/10;

    priority_queue<array<ll,2>,vector<array<ll,2>>,greater<array<ll,2>>>q;
    q.push({0,1});

    while(!q.empty())
    {
        ll w = q.top()[0];
        ll c = q.top()[1];
        q.pop();
        if(v[c])continue;
        v[c]=1;

        for(auto& u : G[c])
            if(SP[u[1]] > w + u[0])
            SP[u[1]]=w+u[0],q.push({w+u[0],u[1]});
    }

    queue<int>Q;
    Q.push(n);
    can[n]=1;
    while(!Q.empty())
    {
        int c = Q.front();
        Q.pop();

        for(auto&u:R[c])
            if(SP[u[1]] + u[0] == SP[c])
            {
                if(!can[u[1]])
                {
                    can[u[1]]=1;
                    Q.push(u[1]);
                }

                g[u[1]].push_back(c);
            }
    }

    dfs(1);
    reverse(topo.begin(),topo.end());
    //for(int&x:topo)cout<<x<<" ";cout<<"\n";

    for(int i=0; i<topo.size(); i++)
        topoID[topo[i]]=i;

    vector<int>ats;
    int nxt = 0;
    for(int i=0; i<topo.size(); i++)
    {
        if(nxt==i)ats.push_back(topo[i]);
        for(auto&u:g[topo[i]])nxt=max(nxt,topoID[u]);
    }

    sort(ats.begin(),ats.end());
    cout<<ats.size()<<"\n";
    for(int&x:ats)cout<<x<<" ";
}
