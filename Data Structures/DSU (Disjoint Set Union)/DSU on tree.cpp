#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo INT_MAX/2

const int N = 1000001;
vector<int>G[N];
vector<int>depth[N];
vector<int>dom[N];
int ats[N];
int sz[N];
int D[N];

int dfs(int c, int p=-1)
{
    depth[D[c]].push_back(c);
    sz[c]=1;
    for(auto&u:G[c])
        if(u!=p)
        D[u]=D[c]+1,sz[c]+=dfs(u,c);
    return sz[c];
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    int n;
    cin>>n;

    for(int i=1; i<n; i++)
    {
        int u,v;
        cin>>u>>v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    dfs(1);

    for(int d=n-1; d>=0; d--)
        for(auto&c : depth[d])
        {
            int v = -1;

            for(auto&u : G[c])
                if(D[u] > D[c])
            {
                if(v==-1 || dom[u].size() > dom[v].size())
                    v=u;
            }

            if(v!=-1)
            {
                swap(dom[v],dom[c]);
                if(ats[v]!=0)
                ats[c]=ats[v]+1;
            }

            dom[c].push_back(1);
            int s = dom[c].size();

            for(auto&u : G[c])
                if(D[u] > D[c] && u!=v)
            {
                for(int j=dom[u].size()-1,k=s-2; j>=0; j--,k--)
                {
                    dom[c][k]+=dom[u][j];
                    if(dom[c][k] > dom[c][s-1-ats[c]])
                        ats[c] = s-k-1;
                    else if(dom[c][k] == dom[c][s-1-ats[c]])
                        ats[c] = min(ats[c],s-k-1);
                }
            }
        }

    for(int i=1; i<=n; i++)
        cout<<ats[i]<<"\n";
}
