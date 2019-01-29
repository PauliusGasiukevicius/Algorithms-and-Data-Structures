#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

ll M[505][505]={};
ll O[505][505]={};

int main()
{
    ios::sync_with_stdio(0);
    int n,m,st,en;
    cin>>n>>m>>st>>en;

    vector<int>G[505];

    for(ll i=0,u,v,w; i<m; i++)
    {
        cin>>u>>v>>w;
        G[u].push_back(v);
        G[v].push_back(u);
        O[u][v]+=w;
        M[u][v]+=w;
    }

    ll mf = 0;
    while(1)
    {
        queue<int>q;
        q.push(st);
        bitset<2005>visited(0);
        vector<int>P(2005,-1);
        visited[st]=1;

        while(!q.empty() && q.front()!=en)
        {
            int c = q.front();
            q.pop();

            for(auto&u:G[c])
                if(!visited[u] && M[c][u]>0)
                visited[u]=1,P[u]=c,q.push(u);
        }
        if(q.empty())break;
        int c = en;
        vector<int>path;
        while(c!=-1)path.push_back(c),c=P[c];
        reverse(path.begin(),path.end());

        ll f = 666666666;
        for(int i=1; i<path.size(); i++)
            f=min(f,M[path[i-1]][path[i]]);

        for(int i=1; i<path.size(); i++)
            M[path[i-1]][path[i]]-=f,M[path[i]][path[i-1]]+=f;
        mf+=f;
    }

    vector<vector<int>>E;

    for(int i=0; i<=n; i++)
        for(int j=0; j<=n; j++)
        if(M[i][j] < O[i][j])
        E.push_back({i,j,O[i][j]-M[i][j]});

    cout<<n<<" "<<mf<<" "<<E.size()<<"\n";
    for(auto&e:E)
        cout<<e[0]<<" "<<e[1]<<" "<<e[2]<<"\n";
}

