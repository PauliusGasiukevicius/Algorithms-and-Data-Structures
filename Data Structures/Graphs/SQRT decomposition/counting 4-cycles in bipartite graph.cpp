#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

vector<int>g[200001];
int cnt[200001];

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n,m,k;
    cin>>n>>m>>k;
    int K = sqrt(n)+1;
    for(int i=0; i<k; i++)
    {
        int u,v;
        cin>>u>>v;
        g[u].push_back(v+n);
        g[v+n].push_back(u);
    }

    ll ats = 0;
    map<pair<int,int>,ll>mp;

    for(int i=1; i<=n; i++)
        if(g[i].size() < K)//small
    {
        for(int j=0; j<g[i].size(); j++)
            for(int z=j+1; z<g[i].size(); z++)
            mp[minmax(g[i][j],g[i][z])]++;
    }

    for(auto p : mp)
        ats+=(p.second)*(p.second-1)/2;

    for(int i=1; i<=n; i++)
        if(g[i].size() >= K)//large
    {
        for(auto&u:g[i])
        for(auto&v:g[u])
        cnt[v]++;

        for(int j=1; j<=n; j++)
            {
                if(j!=i && g[j].size() < K)
            ats+=cnt[j]*(cnt[j]-1LL)/2;
            else if(j < i)
            ats+=cnt[j]*(cnt[j]-1LL)/2;

            cnt[j]=0;
            }
    }

    cout<<ats;
}
