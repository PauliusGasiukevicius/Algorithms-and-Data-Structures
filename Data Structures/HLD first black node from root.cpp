#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

const int N = 100001;
vector<int>G[N];
int P[N], ID[N], sz[N], head[N], D[N], seg[4*N], node[N];
int nxt = 0, n;

void dfs(int c, int p = 0)
{
    D[c]=D[p]+1;
    P[c]=p;
    sz[c]=1;
    for(auto&u : G[c])
        if(u!=p)
    {
        dfs(u,c);
        sz[c]+=sz[u];
    }
}

void HLD(int c, int p = -1, bool newChain = false)
{
    ID[c]=++nxt;
    node[nxt]=c;
    head[c] = (newChain ? c : head[p]);

    int heavy = -1;
    for(auto&u : G[c])
        if(u!=p && (heavy==-1 || sz[heavy] < sz[u]))
        heavy = u;

    if(heavy==-1)return;

    HLD(heavy,c);

    for(auto&u : G[c])
        if(u!=p && u!=heavy)
        HLD(u,c,1);
}

void build(int c, int l, int r)
{
    if(l==r)
    {
        seg[c]=oo;
        return;
    }
    int m = (l+r)/2;
    build(2*c,l,m);
    build(2*c+1,m+1,r);
    seg[c]=min(seg[2*c],seg[2*c+1]);
}

void flip(int c, int l, int r, int pos)
{
    if(l==r)
    {
        seg[c]=(seg[c]==oo ? r : oo);
        return;
    }
    int m = (l+r)/2;
    if(pos<=m)flip(2*c,l,m,pos);
    else flip(2*c+1,m+1,r,pos);
    seg[c]=min(seg[2*c],seg[2*c+1]);
}

int get(int c, int l, int r, int L, int R)
{
    if(l>r || l>R || r<L)return oo;
    if(l>=L && r<=R)return seg[c];
    int m = (l+r)/2;
    return min(get(2*c,l,m,L,R),get(2*c+1,m+1,r,L,R));
}

int query(int u)
{
    int ats = oo;
    while(u)
    {
        ats=min(ats,get(1,1,n,ID[head[u]],ID[u]));
        u=P[head[u]];
    }
    return (ats==oo ? -1 : node[ats]);
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    int q;
    cin>>n>>q;
    for(int i=1; i<n; i++)
    {
        int u,v;
        cin>>u>>v;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    dfs(1);
    HLD(1,0,1);
    build(1,1,n);
    D[0]=oo;
    while(q--)
    {
        int tp,u;
        cin>>tp>>u;
        if(tp==0)
            flip(1,1,n,ID[u]);
        else
            cout<<query(u)<<"\n";
    }
}
