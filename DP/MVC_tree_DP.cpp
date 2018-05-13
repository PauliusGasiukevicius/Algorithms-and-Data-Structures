#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

int DFS(vector<vector<int>>&DP, vector<int>G[], int c, int p)
{
    for(auto&u:G[c])
        if(u!=p)DFS(DP,G,u,c);

    DP[c][0]=0;
    DP[c][1]=1;
    for(auto&u:G[c])
        if(u!=p)
        DP[c][0]+=DP[u][1], DP[c][1]+=min(DP[u][0],DP[u][1]);

    return min(DP[c][1],DP[c][0]);
}

int main()
{
    ios::sync_with_stdio(0);
    int n;
    cin>>n;
    vector<int>G[100001];
    vector<vector<int>>DP(n+1,vector<int>(2));
    for(int i=1,u,v; i<n; i++)
        cin>>u>>v,G[u].push_back(v),G[v].push_back(u);

    cout<<DFS(DP,G,1,-1)<<"\n";
}
