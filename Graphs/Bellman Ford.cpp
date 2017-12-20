#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(0);
    int t;
    cin>>t;
    while(t--)
    {
    int n,m;
    cin>>n>>m;
    vector<int>dist(n,666666);
    vector<int>prev(n,-1);
    int from[2001], to[2001], w[2001];

    for(int i=0; i<m; i++)
        cin>>from[i]>>to[i]>>w[i];

    dist[0]=0;
    int lastUpdate = 0;
    for(int i=1; i<=n; i++)
    for(int j=0; j<m; j++)
        if(dist[from[j]] + w[j] < dist[to[j]])
            dist[to[j]]=dist[from[j]]+w[j], prev[to[j]]=from[j],lastUpdate=i;

cout<<(lastUpdate==n?"negative cycle exists\n":"there`s no negative cycle\n");
    }

}
