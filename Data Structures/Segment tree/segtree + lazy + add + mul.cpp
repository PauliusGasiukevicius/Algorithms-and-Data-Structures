#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

ll A[100005];
ll seg[400005][4];//[sum][mul][add][lazy]
ll M = 1e9+7;

void build(int c, int l, int r)
{
    if(l==r)
    {
        seg[c][0]=A[r]%M;
        seg[c][1]=1;
        return;
    }
    int m = (l+r)/2;
    build(2*c,l,m);
    build(2*c+1,m+1,r);
    seg[c][0] = (seg[2*c][0] + seg[2*c+1][0])%M;
    seg[c][1]=1;
}

void lazy(int c, int l, int r)
{
    if(!seg[c][3])return;
    seg[c][0]= ((seg[c][0]*seg[c][1])%M + ((r-l+1LL)*seg[c][2])%M)%M;

    if(l!=r)
    {
        seg[2*c][1]*=seg[c][1];
        seg[2*c][2]*=seg[c][1];
        seg[2*c][2]%=M;
        seg[2*c][2]+=seg[c][2];
        seg[2*c][1]%=M;
        seg[2*c][2]%=M;
        seg[2*c][3]=1;

        seg[2*c+1][1]*=seg[c][1];
        seg[2*c+1][2]*=seg[c][1];
        seg[2*c+1][2]%=M;
        seg[2*c+1][2]+=seg[c][2];
        seg[2*c+1][1]%=M;
        seg[2*c+1][2]%=M;
        seg[2*c+1][3]=1;
    }
    seg[c][1]=1;
    seg[c][2]=0;
    seg[c][3]=0;
}

void mul(int c, int l, int r, int L, int R, ll v)
{
    lazy(c,l,r);
    if(l > r || l > R || r < L)return;
    if(l>=L && r<=R)
    {
        seg[c][1]*=v;
        seg[c][2]*=v;
        seg[c][1]%=M;
        seg[c][2]%=M;
        seg[c][3]=1;
        lazy(c,l,r);
        return;
    }
    int m = (l+r)/2;
    mul(2*c,l,m,L,R,v);
    mul(2*c+1,m+1,r,L,R,v);
    seg[c][0] = (seg[2*c][0] + seg[2*c+1][0])%M;
}

void add(int c, int l, int r, int L, int R, ll v)
{
    lazy(c,l,r);
    if(l > r || l > R || r < L)return;
    if(l>=L && r<=R)
    {
        seg[c][2]+=v;
        seg[c][2]%=M;
        seg[c][3]=1;
        lazy(c,l,r);
        return;
    }
    int m = (l+r)/2;
    add(2*c,l,m,L,R,v);
    add(2*c+1,m+1,r,L,R,v);
    seg[c][0] = (seg[2*c][0] + seg[2*c+1][0])%M;
}

ll get(int c, int l, int r, int L, int R)
{
    lazy(c,l,r);
    if(l > r || l > R || r < L)return 0;
    if(l>=L && r<=R)return seg[c][0]%M;
    int m = (l+r)/2;
    ll ats = (get(2*c,l,m,L,R)%M + get(2*c+1,m+1,r,L,R)%M)%M;
    seg[c][0] = (seg[2*c][0] + seg[2*c+1][0])%M;
    return ats;
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    int n,q;
    cin>>n>>q;

    for(int i=1; i<=n; i++)
        cin>>A[i];

    build(1,1,n);

    while(q--)
    {
        ll tp,l,r,v;
        cin>>tp>>l>>r;
        if(tp!=4)cin>>v;

        if(tp==1)add(1,1,n,l,r,v);
        else if(tp==2)mul(1,1,n,l,r,v);
        else if(tp==3)mul(1,1,n,l,r,0),add(1,1,n,l,r,v);
        else cout<<get(1,1,n,l,r)<<"\n";
    }
}
