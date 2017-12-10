#include <bits/stdc++.h>
using namespace std;

int Find(vector<int>&P, int u)
{return (P[u] < 0 ? u : P[u] = Find(P,P[u]));}

void Union(vector<int>&P, int u, int v)
{
    if((u=Find(P,u)) == (v=Find(P,v)))return;

    if(P[u] > P[v])swap(u,v);

    P[u]+=P[v];
    P[v]=u;
}

int main()
{
    ios::sync_with_stdio(0);
    int n,m;
    cin>>n>>m;
    vector<vector<int>>edges(m,vector<int>(3));
    vector<int>P(n+1,-1);

    for(int i=0; i<m; i++)
        cin>>edges[i][1]>>edges[i][2]>>edges[i][0];
    sort(edges.begin(),edges.end());

    int ats = 0;

    for(int i=0; i<m && n!=0; i++)
    if(Find(P,edges[i][1]) != Find(P,edges[i][2]))
        ats+=edges[i][0],Union(P,edges[i][1],edges[i][2]),n--;

    cout<<ats<<"\n";
}
