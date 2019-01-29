#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

int M = 10007;

void DFS(vector<vector<int>>&DP, vector<int>G[], int c, int p, vector<vector<int>>&cnt)
{
    for(auto&u:G[c])
        if(u!=p)DFS(DP,G,u,c,cnt);

    DP[c][0]=0;
    DP[c][1]=1;
    cnt[c][0]=1;
    cnt[c][1]=1;

    for(auto&u:G[c])
        if(u!=p)
        {
            DP[c][0]+=DP[u][1];
            DP[c][1]+=min(DP[u][0],DP[u][1]);
            cnt[c][0]=(cnt[c][0] * cnt[u][1])%M;

            if(DP[u][0]==DP[u][1])
            cnt[c][1]=(cnt[c][1] * (cnt[u][1] + cnt[u][0]))%M;
            else if(DP[u][0] < DP[u][1])
            cnt[c][1]=(cnt[c][1] * cnt[u][0])%M;
            else
            cnt[c][1]=(cnt[c][1] * cnt[u][1])%M;
        }

    return;
}

int main()
{
    ios::sync_with_stdio(0);
    int t,n;
    cin>>t;
    while(t--)
    {
    cin>>n;
    vector<int>G[100001];
    vector<vector<int>>DP(n+1,vector<int>(2));
    vector<vector<int>>cnt(n+1,vector<int>(2));
    for(int i=1,u,v; i<n; i++)
        cin>>u>>v,G[u].push_back(v),G[v].push_back(u);
    DFS(DP,G,1,-1,cnt);
        if(DP[1][0] == DP[1][1])
            cout<<DP[1][0]<<" "<<(cnt[1][0] + cnt[1][1])%M<<"\n";
        else if(DP[1][0] < DP[1][1])
            cout<<DP[1][0]<<" "<<(cnt[1][0])%M<<"\n";
        else
            cout<<DP[1][1]<<" "<<(cnt[1][1])%M<<"\n";
    }
}
