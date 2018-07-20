#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo INT_MAX/2

const int N = 100001;
int low[N], disc[N], out[N], P[N], AP[N], AP_st[N], AP_en[N];
vector<int>G[N];
vector<int>childs[N];
int n,m,q,tt=0;

void dfs(int c)
{
    disc[c]=low[c]=++tt;
    int child = 0;
    bool ap = 0;

    for(auto&u:G[c])
        if(disc[u]==0)
    {
        child++;
        P[u]=c;
        dfs(u);
        low[c]=min(low[c],low[u]);
        if(P[c]>0 && low[u] >= disc[c])ap=1,childs[c].push_back(u);
    }else if(u!=P[c])low[c]=min(low[c],disc[u]);

    out[c]=tt;
    if(child > 1 && P[c]==0)
    {
        ap=1;
        for(auto&u : G[c])
            childs[c].push_back(u);
    }

    if(ap)
    AP[c]=1;
}

bool inSubtree(int u, int v)
{
    return disc[u]>=disc[v] && out[u] <= out[v];
}

int getChild(int u, int v)
{
    if(childs[v].empty())return -1;
    int l = 0, r = childs[v].size()-1;

    while(l<r)
    {
        int mi = (l+r+1)/2;
        if(disc[childs[v][mi]] <= disc[u])
            l=mi;
        else r=mi-1;
    }

    if(inSubtree(u,childs[v][r]))return r+1;
    else return -1;
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>n>>m;

        for(int i=0; i<m; i++)
        {
            int u,v;
            cin>>u>>v;
            G[u].push_back(v);
            G[v].push_back(u);
        }
    cin>>q;

    for(int i=1; i<=n; i++)
        if(disc[i]==0)
        dfs(i);

    while(q--) //note: Queries assume that u, v and uu, vv are distinct (need some more ifs if they can be the same)
    {
        int tp;
        cin>>tp;
        if(tp&1)
        {
            int u,v,uu,vv;
            cin>>u>>v>>uu>>vv; //Query if edge uu vv is removed can we reach u from v?
            if(disc[vv] > disc[uu])swap(uu,vv);

            if(low[uu] > disc[vv] && (inSubtree(u,uu) ^ inSubtree(v,uu)))//if edge is a bridge
                cout<<"ne\n";                                            //and st and en are on different parts
            else cout<<"da\n";
        }
        else
        {
            int u,v,uu;
            cin>>u>>v>>uu; //Query if vertex uu is removed can we reach u from v?
            if(AP[uu] && (getChild(u,uu) ^ getChild(v,uu)))
            cout<<"ne\n";
            else cout<<"da\n";
        }
    }
}

