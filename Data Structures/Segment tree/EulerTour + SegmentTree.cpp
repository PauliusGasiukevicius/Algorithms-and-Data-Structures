#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

void DFS(vector<vector<int>>&G, int c, int p, vector<int>&st, vector<int>&en)
{
    static int tm = 0;
    st[c]=++tm;
    for(auto&u:G[c])
        if(u!=p)DFS(G,u,c,st,en);
    en[c]=tm;
}

void lazyUpdate(vector<ll>&seg, vector<ll>&lazy, int c, int l, int r)
{
    if(lazy[c]==0)return;
    seg[c]=lazy[c];
    if(l!=r)lazy[2*c]=lazy[2*c+1]=lazy[c];
    lazy[c]=0;
}

void update(vector<ll>&seg,vector<ll>&lazy, int c, int l, int r, int L, int R, ll v)
{
    lazyUpdate(seg,lazy,c,l,r);
    if(l>r || l>R || r<L)return;
    lazyUpdate(seg,lazy,c,l,r);

    if(l>=L && r<=R)
    {
        seg[c]=v;
        //cout<<seg[c]<<" "<<l<<" "<<r<<"\n";
        if(l!=r)lazy[2*c]=lazy[2*c+1]=v;
        return;
    }

    int m = (l+r)/2;
    update(seg,lazy,2*c,l,m,L,R,v);
    update(seg,lazy,2*c+1,m+1,r,L,R,v);
    seg[c]=seg[2*c]|seg[2*c+1];
}


ll query(vector<ll>&seg, vector<ll>&lazy, int c, int l, int r, int L, int R)
{
    lazyUpdate(seg, lazy, c, l, r);
    if(l>r || l>R || r<L)return 0LL;
    lazyUpdate(seg,lazy,c,l,r);

    if(l>=L && r<=R)
        return seg[c];

    int m = (l+r)/2;
    return query(seg,lazy,2*c,l,m,L,R) | query(seg,lazy,2*c+1,m+1,r,L,R);
}

int main()
{
    ios::sync_with_stdio(0);
    int n,m,type;
    cin>>n>>m;
    vector<ll>A(n+1);
    vector<int>st(n+1);
    vector<int>en(n+1);
    vector<vector<int>>G(n+1);

    for(int i=1; i<=n; i++)
        cin>>A[i];
    for(int i=1,u,v; i<n; i++)
        cin>>u>>v,G[u].push_back(v),G[v].push_back(u);

    DFS(G,1,0,st,en);
    cout<<"DFS: \n";
    for(int i=1; i<=n; i++)cout<<st[i]<<" ";
    cout<<"\n";
    for(int i=1; i<=n; i++)cout<<en[i]<<" ";
    cout<<"\n";

    vector<ll>seg(4*n),lazy(4*n);

    for(int i=1; i<=n; i++)
        update(seg,lazy,1,1,n,st[i],st[i],1LL << A[i]);

    while(m--)
    {
        cin>>type;
        if(type==1)
        {
            ll vertex,color;
            cin>>vertex>>color;
            update(seg,lazy,1,1,n,st[vertex],en[vertex],(1LL<<color));
        }
        else
        {
            int vertex;
            cin>>vertex;
            cout<<bitset<64>(query(seg,lazy,1,1,n,st[vertex],en[vertex])).count()<<"\n";
        }
    }
}
