#pragma GCC opointimize("Ofast")

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 1234567890

ll dp[1<<16];

ll solve(vector<vector<ll>>&sp, vector<int>&odd, int mask)
{
    if(mask+1 == (1<<odd.size()))return 0;
    if(dp[mask] != -1)return dp[mask];

    bitset<16>b(mask);

    dp[mask]=LLONG_MAX/100;
    for(int i=0; i<odd.size(); i++)
    for(int j=i+1; j<odd.size() && !b[i]; j++)
        if(!b[j])
        dp[mask]=min(dp[mask], solve(sp,odd,(mask|(1<<j))|(1<<i)) + sp[odd[i]][odd[j]]);

    return dp[mask];
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n,m;
    while(cin>>n && n)
    {
        cin>>m;
        ll res = 0;
        vector<vector<ll>>sp(n,vector<ll>(n,LLONG_MAX/100));
        vector<ll>in(n);
        for(int i=0; i<m; i++)
        {
            ll u,v,w;
            cin>>u>>v>>w;
            u--;v--;
            sp[u][v]=min(sp[u][v],w);
            sp[v][u]=min(sp[v][u],w);
            res+=w;
            in[u]++;
            in[v]++;
        }

        for(int k=0; k<n; k++)
        for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            sp[i][j]=min(sp[i][j],sp[i][k]+sp[k][j]);

        vector<int>odd;
        for(int i=0; i<n; i++)
            if(in[i]&1)odd.push_back(i);

        memset(dp, -1, sizeof dp);
        res+=solve(sp,odd,0);
        cout<<res<<"\n";
    }
}
