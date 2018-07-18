#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo INT_MAX/2

int Find(vector<ll>&P, int u)
{
    return P[u] < 0 ? u : P[u] = Find(P,P[u]);
}

void Union(vector<ll>&P, int u, int v)
{
    u = Find(P,u);
    v = Find(P,v);
    if(u==v)return;
    P[u]+=P[v];
    P[v]=u;
}

/*
You are given an undirected graph with N verticies and M edges, where the weights are unique. 

There is a function Cost(u, v), which is defined as follows:

While there is a path between vertex u and v, delete the edge with the smallest weight. Cost(u,v) is the sum of the weights of the edges that were deleted in this process.
*/

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    int n,m;
    cin>>n>>m;
    vector<array<ll,3>>E(m);
    vector<ll>P(n+1,-1);
    for(int i=0; i<m; i++)
        cin>>E[i][1]>>E[i][2]>>E[i][0];

    sort(E.rbegin(),E.rend());
    ll ats = 0, M = 1000000000LL;
    ll pairs = 0;

    for(auto&e:E)//might nit work for unconnected one, to make it work gotta run on all components
        {//while keeping distinct pairs variable for each component
            int x = Find(P,e[1]);
            int y = Find(P,e[2]);
            if(x!=y)
            pairs+=P[x]*P[y],Union(P,e[1],e[2]);

            pairs%=M;
            ats = (ats + pairs*e[0]%M)%M;
        }


    cout<<(ats+M)%M<<"\n";
}
