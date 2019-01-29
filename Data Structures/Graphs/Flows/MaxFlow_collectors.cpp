#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main()
{
    ios::sync_with_stdio(0);
    int t,n,m,k,x,cs=1;
    cin>>t;

    while(t--)
    {
        cin>>n>>m;
        int cnt[31][31]={};
        for(int i=1; i<=n; i++)
        {
            cin>>k;
            while(k--)
                cin>>x,cnt[i][x]++;
        }

        int maxflow=0;
        vector<int>G[640];
        int M[640][640]={};
        int out=n*m;
        int en = 511;
        int ppl = 512;

        for(int j=1; j<=m; j++)
        {
            G[0].push_back(j);
            G[j].push_back(0);
            M[0][j]=cnt[1][j];

            G[j].push_back(en);
            G[en].push_back(j);
            M[j][en]=1;

            for(int i=2; i<=n; i++) // who we buy it from
            if(cnt[i][j]==0)
            {
                int P = ppl + i;
                G[j].push_back(P);
                G[P].push_back(j);
                M[j][P]=1;

                for(int k=1; k<=m; k++) //what can we trade
                    if(cnt[i][k] > 1)
                {
                int node = (i-1)*m+k;
                G[P].push_back(node);
                G[node].push_back(P);
                M[P][node]=cnt[i][k]-1;

                G[node].push_back(k);
                G[k].push_back(node);
                M[node][k]=666;
                }
            }
        }

        while(1)
        {
            bitset<1024>visited(0);
            vector<int>P(1024,-1);
            visited[0]=1;
            queue<int>q;
            q.push(0);

            while(!q.empty() && q.front()!=en)
            {
                int c = q.front();
                q.pop();

                for(auto&u : G[c])
                    if(!visited[u] && M[c][u] > 0)
                {
                    visited[u]=1;
                    P[u]=c;
                    q.push(u);
                }
            }

            if(q.empty())break;
            int c = en;
            vector<int>path;
            while(c!=-1)
                path.push_back(c),c=P[c];

            reverse(path.begin(),path.end());
            int flow = 666666;
            for(int i=1; i<path.size(); i++)
                flow=min(flow,M[path[i-1]][path[i]]);

            for(int i=1; i<path.size(); i++)
                M[path[i-1]][path[i]]-=flow,M[path[i]][path[i-1]]+=flow;

            maxflow+=flow;
        }

        cout<<"Case #"<<cs++<<": "<<maxflow<<"\n";
    }
}
