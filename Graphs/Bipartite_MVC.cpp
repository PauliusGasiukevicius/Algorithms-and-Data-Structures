#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main()
{
    ios::sync_with_stdio(0);
    int n,m,k;

    while(cin>>n>>m>>k && n)
    {
        vector<int>G[2002];
        vector<vector<int>>M(2048,vector<int>(2048,0));
        int t = n+m+1;
        for(int i=1; i<=n; i++)
        {
            G[i].push_back(0);
            G[0].push_back(i);
            M[0][i]=1;
        }

        for(int i=n+1; i<=n+m; i++)
        {
            G[i].push_back(t);
            G[t].push_back(i);
            M[i][t]=1;
        }

        int y,x;
        while(k--)
        {
            cin>>y>>x;
            G[y].push_back(x+n);
            G[x+n].push_back(y);
            M[y][x+n]=1;
        }

        int f=0;

        while(1)
        {
            queue<int>q;
            q.push(0);
            bitset<2048>visited(0);
            vector<int>P(2048,-1);
            visited[0]=1;

            while(!q.empty() && q.front()!=t)
            {
                int c = q.front();
                q.pop();

                for(auto&u:G[c])
                    if(!visited[u] && M[c][u] > 0)
                visited[u]=1,q.push(u),P[u]=c;
            }

            if(q.empty())break;
            vector<int>path;
            int c = t;
            while(c!=-1)
            path.push_back(c),c=P[c];
            reverse(path.begin(),path.end());
            for(int i=1; i<path.size(); i++)
                M[path[i-1]][path[i]]--,M[path[i]][path[i-1]]++;

            f++;
        }
        /*
        |MCBM| = |MVC| now we just need to find MVC
        according to Konig we can find MVC by:
        let set Z = all unmatched vertices in one side of bipartite graph(U,V)
        add to Z all nodes reachable from Z via alternating path
        that goes throught unmatched->matched->un... edges
        then MVC = (U\Z) Union (V Intersection Z)
        */

        vector<vector<int>>flow(2048,vector<int>(2048,0)); // hashed flow edges

        for(int i=1; i<=n; i++)
            for(int j=n+1; j<=n+m; j++)
            if(M[j][i]==1)flow[i][j]=flow[j][i]=1;

        bitset<2048>Z(0);
        int visited[2048][2]={};

        queue<pair<int,int>>q;
        for(int i=1; i<=n; i++)
            if(M[0][i]==1)Z[i]=1,visited[i][0]=1,q.push({i,0});

        while(!q.empty())
        {
            int c = q.front().first;
            int e = q.front().second;
            //cout<<c<<" "<<e<<" <--\n";
            Z[c]=1;
            q.pop();

            for(auto&u:G[c])
                if(!visited[u][!e] && u!=0 && u!=t && flow[c][u]==e)
                visited[u][!e]=1,q.push({u,!e});
        }
        cout<<f;

        for(int i=1; i<=n; i++)
            if(!Z[i])cout<<" r"<<i;

            for(int j=1+n; j<=m+n; j++)
            if(Z[j])cout<<" c"<<j-n;
        cout<<"\n";
    }
}
