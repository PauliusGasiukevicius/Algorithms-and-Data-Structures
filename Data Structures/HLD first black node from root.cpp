#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

const int N = 100001;
vector<int>G[N];
int chain[N],head[N],segID[N],seg[4*N],depth[N],sz[N],P[N],node[N];
int nxt = 1, nxtChain=1, n;

int dfs(int c, int p)
{
    sz[c]=1;
    P[c]=p;
    depth[c]=depth[p]+1;

    for(auto&u : G[c])
        if(u!=p)
            sz[c]+=dfs(u,c);

    return sz[c];
}

void HLD(int c, int chainID)
{
    segID[c]=nxt++;
    node[nxt-1]=c;
    if(chainID < 0)chainID=nxtChain++,head[chainID]=c;
    chain[c]=chainID;

    if(G[c].empty() || G[c].size()==1 && G[c][0]==P[c])return;

    int mx = (G[c][0]==P[c] ? G[c][1] : G[c][0]);

    for(auto&u : G[c])
        if(u!=P[c] && sz[u] > sz[mx])
        mx=u;

    HLD(mx,chainID);

    for(auto&u : G[c])
        if(u!=mx && u!=P[c])
        HLD(u,-1);
}

void update(int c, int l, int r, int pos)
{
    if(l==r)
    {
        seg[c] = (seg[c]==oo ? r : oo);
        return;
    }
    int m = (l+r)/2;
    if(pos<=m)
        update(2*c,l,m,pos);
    else
        update(2*c+1,m+1,r,pos);

    seg[c] = min(seg[2*c],seg[2*c+1]);
}

int RMQ(int c, int l, int r, int L, int R)
{
    if(l>r || r<L || l>R)return oo;
    if(l>=L && r<=R)return seg[c];
    int m = (l+r)/2;
    return min(RMQ(2*c,l,m,L,R), RMQ(2*c+1,m+1,r,L,R));
}

int firstBlack(int u)
{
    int ats = oo;
    while(u)
    {
        ats= min(ats,RMQ(1,1,n,segID[head[chain[u]]],segID[u]));
        u=P[head[chain[u]]];
    }
    return ats;
}

int main()
{
    ios::sync_with_stdio(0);
    int q;
    cin>>n>>q;

    for(int i=1,u,v; i<n; i++)
    {
        cin>>u>>v;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    dfs(1,0);
    HLD(1,-1);
    fill(seg,seg+4*N,oo);

    while(q--)
    {
        int x,y;
        cin>>x>>y;
        if(x)
        {
            int ats = firstBlack(y);
            if(ats==oo)ats=-1;
            else ats = node[ats];
            cout<<ats<<"\n";
        }
        else
            update(1,1,n,segID[y]);
    }
}
