#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

int main()
{
    ios::sync_with_stdio(0);
    int t,n,m,u,v;
    cin>>t;

    while(t--)
    {
        cin>>n;
        vector<int>O(n+1);
        for(int i=1,x; i<=n; i++)
            cin>>x,O[x]=i;

        cin>>m;
        vector<vector<int>>G(n+1);
        vector<int>in(n+1);
        vector<vector<int>>M(n+1,vector<int>(n+1));
        while(m--)
        {
            cin>>u>>v;
            if(O[u] < O[v])swap(u,v);
            G[u].push_back(v);
            in[v]++;
            M[u][v]=M[v][u]=1;
        }

        for(int i=1; i<=n; i++)
            for(int j=i+1; j<=n; j++)
            if(!M[i][j])
        {
            int u=i,v=j;
            if(O[u] < O[v])swap(u,v);
            G[v].push_back(u);
            in[u]++;
        }

        vector<int>ats;
        int mx = 0;
        priority_queue<pair<int,int>>q;
        for(int i=1; i<=n; i++)
            if(in[i]==0)q.push({-O[i],i});

        while(!q.empty())
        {
            //mx=max(mx,(int)q.size());
            int c = q.top().second;
            q.pop();
            ats.push_back(c);

            for(auto&u:G[c])
                if(--in[u]==0)q.push({-O[u],u});
        }

        if(ats.size() < n)
            cout<<"IMPOSSIBLE\n";
        else if(mx > 1)cout<<"?\n";
        else
        {
            for(int i=0; i<n; i++)
                cout<<ats[i]<<(i+1==n?"\n":" ");
        }
    }
}

