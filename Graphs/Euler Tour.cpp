#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

/*
PROG: fence
LANG: C++14
*/

void euler(multiset<int>G[], int c, vector<int>&E)
{
    for(auto it = G[c].begin(); it!=G[c].end();)
    {
        int u = *it;
        G[c].erase(G[c].find(u));
        G[u].erase(G[u].find(c));
        euler(G,u,E);
        it = G[c].begin();
    }
    E.push_back(c);
}

int main()
{
    ios::sync_with_stdio(0);
    freopen("fence.in","r",stdin);
    freopen("fence.out","w",stdout);
    int n;
    cin>>n;
    multiset<int>G[501];

    for(int i=0,u,v; i<n; i++)
        cin>>u>>v,G[u].insert(v),G[v].insert(u);

    vector<int>E; // stores euler tour/path
    int st = 1;

    for(int i=1; i<=500; i++)
        if(G[i].size()&1) // we should start from first odd node if any
    {                     // this assumes euler tour/path exists
        st=i;
        break;
    }

    euler(G,st,E);
    reverse(E.begin(),E.end());

    for(int i=0; i<E.size(); i++)
        cout<<E[i]<<"\n";
}
