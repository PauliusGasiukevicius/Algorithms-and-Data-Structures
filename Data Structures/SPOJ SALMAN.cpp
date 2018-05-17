#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

void Euler(vector<int>G[], vector<int>&st, vector<int>&en, int c, int& tm)
{
    st[c]=++tm;
    for(auto&u:G[c])
        Euler(G,st,en,u,tm);
    en[c]=tm;
}

void lazyUpdate(vector<ll>&seg, vector<ll>&lazy, vector<ll>&rmq, int c, int l, int r)
{
    if(lazy[c]==0)return;
    seg[c]+=lazy[c]*(r-l+1LL);
    if(l!=r)
    {
        lazy[c*2]+=lazy[c];
        lazy[2*c+1]+=lazy[c];
        rmq[c]=min(rmq[c*2]+lazy[2*c],rmq[c*2+1]+lazy[2*c+1]);
    }else rmq[c]=seg[c];
    lazy[c]=0;
}

void update(vector<ll>&seg, vector<ll>&lazy, vector<ll>&rmq, int c, int l, int r, int L, int R, ll val)
{
    lazyUpdate(seg,lazy,rmq,c,l,r);
    if(l>R || r<L || l>r)return;

    if(l>=L && r<=R)
    {
        seg[c]+=val*(r-l+1LL); //everyone in range get`s this so we can use lazy
        if(l!=r)
        {
            lazy[2*c]+=val;
            lazy[2*c+1]+=val;
            rmq[c]=min(rmq[2*c+1]+lazy[2*c+1],rmq[2*c]+lazy[2*c]);
        }else rmq[c]=seg[c];
        return;
    }

    int m = (l+r)/2;
    update(seg,lazy,rmq,2*c,l,m,L,R,val);
    update(seg,lazy,rmq,2*c+1,m+1,r,L,R,val);
    rmq[c]=min(rmq[2*c],rmq[2*c+1]);
    seg[c]=seg[2*c]+seg[2*c+1];
}

ll querySum(vector<ll>&seg, vector<ll>&lazy, vector<ll>&rmq, int c, int l, int r, int L, int R)
{
    lazyUpdate(seg,lazy,rmq,c,l,r);
    if(l>R || r<L || l>r)return 0;

    if(l>=L && r<=R)
    return seg[c];

    int m = (l+r)/2;
    return querySum(seg,lazy,rmq,2*c,l,m,L,R) + querySum(seg,lazy,rmq,2*c+1,m+1,r,L,R);
}

ll queryRMQ(vector<ll>&seg, vector<ll>&lazy, vector<ll>&rmq, int c, int l, int r, int L, int R)
{
    lazyUpdate(seg,lazy,rmq,c,l,r);
    if(l>R || r<L || l>r)return LLONG_MAX;

    if(l>=L && r<=R)
    return rmq[c];

    int m = (l+r)/2;
    return min(queryRMQ(seg,lazy,rmq,2*c,l,m,L,R), queryRMQ(seg,lazy,rmq,2*c+1,m+1,r,L,R));
}

int main()
{
    ios::sync_with_stdio(0);
    int t,n,q,type,x;
    cin>>t;

    for(int cs=1; cs<=t; cs++)
    {
        cin>>n>>q;
        cout<<"Case "<<cs<<":\n";
        vector<int>P(n+1),S(n+1),st(n+1),en(n+1);
        vector<int>G[100001];

        for(int i=1; i<=n; i++)
            cin>>P[i]>>S[i],G[P[i]].push_back(i);

        int tm = 0;
        Euler(G,st,en,1,tm);

        vector<ll>seg(4*n),lazy(4*n),rmq(4*n);
        for(int i=1; i<=n; i++)
            update(seg,lazy,rmq,1,1,n,st[i],st[i],S[i]);

        while(q--)
        {
            cin>>type>>x;
            if(type&1)
                cout<<querySum(seg,lazy,rmq,1,1,n,st[x],en[x])<<"\n";
            else
            {
                int mn = queryRMQ(seg,lazy,rmq,1,1,n,st[x],en[x]);
                mn=min(mn,1000);
                update(seg,lazy,rmq,1,1,n,st[x],en[x],mn);
            }
        }
    }
}
