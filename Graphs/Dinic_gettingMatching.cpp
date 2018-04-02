#include <bits/stdc++.h>
using namespace std;
#define ll long long
int n,m,en;
int oo = 666666666;

void build(vector<vector<vector<int>>>&G,vector<pair<int,int>>&E, int cap)
{
    for(int i=1; i<=n; i++)
    {
        int ri = G[i].size();
        int r0 = G[0].size();
        G[0].push_back({i,0,cap,ri});
        G[i].push_back({0,oo,oo,r0});
    }

    for(int i=1+n; i<=n+m; i++)
     {
        int ri = G[i].size();
        int ren = G[en].size();
        G[en].push_back({i,oo,oo,ri});
        G[i].push_back({en,0,1,ren});
    }

    for(int k=0; k<E.size(); k++)
    {
        auto& e = E[k];
        int i = e.first;
        int j = e.second;
        int ri = G[i].size();
        int rk = G[k+1+n].size();

        G[i].push_back({k+1+n,0,1,rk});
        G[k+1+n].push_back({i,1,1,ri});

        int rj = G[j].size();
        rk = G[k+1+n].size();
        G[j].push_back({k+1+n,0,1,rk});
        G[k+1+n].push_back({j,1,1,rj});
    }
}


int BFS(vector<vector<vector<int>>>&G, vector<int>&L)
{
    L[0]=1;
    queue<int>q;
    q.push(0);

    while(!q.empty())
    {
        int c = q.front();
        q.pop();

        for(auto&e:G[c])
            if(e[1] < e[2] && L[e[0]]==0)
            L[e[0]]=L[c]+1,q.push(e[0]);
    }

    return L[en];
}

int DFS(vector<vector<vector<int>>>&G, vector<int>&L, vector<int>&nxt, int c, int flow)
{
    if(c==en)return flow;

    for(;nxt[c]<G[c].size();nxt[c]++)
    {
        auto& e = G[c][nxt[c]];

        if(L[e[0]] == L[c] + 1 && e[1] < e[2])
        {
            int f = DFS(G,L,nxt,e[0],min(flow,e[2]-e[1]));

            if(f>0)
            {
                e[1]+=f;
                G[e[0]][e[3]][1]-=f;
                return f;
            }
        }
    }
    return 0;
}

int Dinic(vector<vector<vector<int>>>&G)
{
    int mf = 0;
    vector<int>L(en+1);
    vector<int>nxt(en+1);

    while(BFS(G,L))
    {
        while(int f = DFS(G,L,nxt,0,666666))
            mf+=f;
        fill(L.begin(),L.end(),0);
        fill(nxt.begin(),nxt.end(),0);
    }
    return mf;
}

int main()
{
    ios::sync_with_stdio(0);
    cin>>n>>m;
    vector<vector<vector<int>>>G(n+m+2);
    vector<pair<int,int>>E(m);
    en = n+m+1;

    for(auto&e:E)cin>>e.first>>e.second;

    int l = 0, r= n;

    while(l<r)
    {
        int cap = (l+r)/2;
        auto G2 = G;
        build(G2,E,cap);
        int mf = Dinic(G2);

        if(mf>=m)
            r=cap;
        else
            l=cap+1;
    }

    build(G,E,r);
    Dinic(G);

    cout<<r<<"\n";

    for(int i=1; i<=n; i++)
        for(auto&e : G[i])
        if(e[1]==e[2] && e[0])
    {
        auto& edge = E[e[0]-n-1];
        cout<<i<<" "<<edge.first+edge.second-i<<endl;
    }
}
