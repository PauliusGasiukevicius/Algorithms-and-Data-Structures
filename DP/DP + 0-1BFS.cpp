#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo INT_MAX/2

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    int n,m,st,en;
    cin>>n>>m;
    vector<vector<int>>G(n+1);
    deque<int>q;
    vector<int>DP(n+1,oo);
    vector<int>DEG(n+1,0);
    vector<int>visited(n+1,0);

    for(int i=0; i<m; i++)
    {
        int u,v;
        cin>>u>>v;
        G[v].push_back(u);//we must reverse graph, cause going from st->en might have dead-ends
        DEG[u]++;
    }
    cin>>en>>st;

    DP[st]=0;
    q.push_back(st);

    while(!q.empty())
    {
        int c = q.front();
        q.pop_front();

        if(visited[c])continue;
        visited[c]=1;

        for(auto&u:G[c])
            if(--DEG[u]==0 && DP[u] > DP[c]) //if all paths from node u lead to en with max cost
            DP[u]=DP[c],q.push_front(u);     //of DP[c], we can choose path at random
            else if(DP[u] > DP[c]+1)         //otherwise we can send order to force other movement
            DP[u]=DP[c]+1,q.push_back(u);
    }

    cout<<(DP[en]==oo ? -1 : DP[en]);
}
