#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 1000000000

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    ll M = 1e9+7;
    int n,m;
    cin>>n>>m;
    vector<vector<array<ll,3>>>G(n+1);//[to,w,edge]
    vector<array<ll,3>>E(m);//[from,to,w]
    vector<ll>ats(m);

    for(int i=0; i<m; i++)
    {
        ll u,v,w;
        cin>>u>>v>>w;
        E[i]={u,v,w};
        G[u].push_back({v,w,i});
    }

    for(int s=1; s<=n; s++)
    {
        vector<ll>to(n+1),from(n+1); //to - number of shortest`s paths from node s to u
                                     //from - number of shortest`s path from node u to any other node on shortest
                                     //path from s to some node

        to[s]=1;
        vector<ll>D(n+1,oo);
        vector<int>vs(n+1);
        D[s]=0;
        priority_queue<array<ll,3>, vector<array<ll,3>>, greater<array<ll,3>>>q;
        q.push({0,s,0});

        //Dijkstra goes in shortest path DAG order
        vector<int>order;
        while(!q.empty())
        {
            ll w = q.top()[0];
            ll c = q.top()[1];
            ll prev = q.top()[2];
            q.pop();

            if(vs[c])continue;
            vs[c]=1;
            order.push_back(c);

            for(auto&u : G[c])
                if(w+u[1] < D[u[0]])
                D[u[0]]=w+u[1],q.push({D[u[0]],u[0],c}),to[u[0]]=to[c];
                else if(w+u[1] == D[u[0]])
                to[u[0]] = (to[u[0]] + to[c])%M;
        }

        for(int i=order.size()-1; i>=0; i--)
        {
            int c = order[i];
            from[c]= (from[c] + 1)%M;
            for(auto& u : G[c])
                if(D[u[0]] == u[1] + D[c])
                from[c] = (from[u[0]] + from[c])%M;
        }

        for(int i=0; i<m; i++)
        {
            int u = E[i][0];
            int v = E[i][1];

            if(D[u] + E[i][2] == D[v])
            ats[i] = (ats[i] + to[u]*from[v])%M;
        }
    }

    for(int i=0; i<m; i++)
        cout<<ats[i]<<"\n";
}
