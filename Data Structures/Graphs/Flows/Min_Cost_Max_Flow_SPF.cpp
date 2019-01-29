#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

int main()
{
    ios::sync_with_stdio(0);
    int n,m,st,en;
    cin>>n>>m>>st>>en;

    vector<vector<int>>G[251];

    for(int i=0,u,v,w,cap; i<m; i++)
    {
        cin>>u>>v>>cap>>w;
        int ru = G[u].size();
        int rv = G[v].size();

        G[u].push_back({v,0,cap,rv,w});
        G[v].push_back({u,cap,cap,ru,-w});
    }

    ll mf = 0;
    ll mfc = 0;

    while(1)
    {
        vector<int>from(256,-1);
        vector<int>edge(256,-1);
        vector<int>SP(256,oo);
        bitset<256>inQueue(0);
        SP[st]=0;

        /*Shortest-Path-Faster*/
        inQueue[st]=1;
        queue<int>q;
        q.push(st);

        while(!q.empty())
        {
            int c = q.front();
            q.pop();
            inQueue[c]=0;

            for(int j=0; j<G[c].size(); j++)
        {
            auto&e = G[c][j];
            if(SP[e[0]] > SP[c] + e[4] && e[1] < e[2])
        {
            SP[e[0]]=SP[c]+e[4],from[e[0]]=c,edge[e[0]]=j;
            if(!inQueue[e[0]])
                q.push(e[0]),inQueue[e[0]]=1;
        }
        }

        }

        if(SP[en]>=oo)break;

        vector<int>path;
        vector<int>E;
        int c = en;
        while(c!=-1)
            path.push_back(c),E.push_back(edge[c]),c=from[c];

        reverse(path.begin(),path.end());
        reverse(E.begin(),E.end());

        int flow = oo;

        for(int i=1; i<path.size(); i++)
            flow=min(flow,G[path[i-1]][E[i]][2] - G[path[i-1]][E[i]][1]);

        for(int i=1; i<path.size(); i++)
            {
                auto&e = G[path[i-1]][E[i]];
                mfc+=e[4]*flow;
                e[1]+=flow;
                G[e[0]][e[3]][1]-=flow;
            }

        mf+=flow;
    }

    cout<<mf<<" "<<mfc<<"\n";
}
