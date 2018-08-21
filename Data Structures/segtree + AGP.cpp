#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666
ll t,n,q,R,mod,mod2,tp;
ll A[200001];

ll powm(ll a, ll deg, ll M)
{
    if(deg==0)return 1%M;
    if(deg&1)return a*powm(a,deg-1,M)%M;
    return powm(a*a%M,deg/2,M);
}

void precalc(int n, vector<ll>&Ri, vector<ll>&RS, vector<ll>&RD, ll M)
{
    Ri[0]=RS[0]=1%M;
    RD[0]=0;
    for(int i=1; i<=n; i++)
        Ri[i]=(Ri[i-1]*R)%M;

    for(int i=1; i<=n; i++)
        RS[i]=(RS[i-1]+Ri[i])%M;

    for(int i=1; i<=n; i++)
        RD[i]=(RD[i-1] + i*Ri[i])%M;
}

void build(vector<array<ll,3>>&seg, int c, int l, int r, ll M)
{
    seg[c][1]=seg[c][2]=0;
    if(l==r)
    {
        seg[c][0]=A[r]%M;
        return;
    }
    int m = (l+r)/2;
    build(seg,2*c,l,m,M);
    build(seg,2*c+1,m+1,r,M);
    seg[c][0]=(seg[2*c][0] + seg[2*c+1][0])%M;
}

void lazy(vector<array<ll,3>>&seg, int c, int l, int r, ll M, vector<ll>&Ri, vector<ll>&RS, vector<ll>&RD)
{
    if(seg[c][1]==0 && seg[c][2]==0)return;
    ll S = seg[c][1], D = seg[c][2];
    ll x = r-l;
    seg[c][0] = (seg[c][0] + ((S*RS[x])%M) + ((D*RD[x])%M))%M;

    if(l!=r)
    {
        seg[2*c][1]=(seg[2*c][1]+S)%M;
        seg[2*c][2]=(seg[2*c][2]+D)%M;
        ll m =(l+r)/2;
        ll skip = m-l+1;
        S = (S*Ri[skip])%M;
        D = (D*Ri[skip])%M;
        S = (S+skip*D)%M;

        seg[2*c+1][1]=(seg[2*c+1][1]+S)%M;
        seg[2*c+1][2]=(seg[2*c+1][2]+D)%M;
    }
    seg[c][1]=seg[c][2]=0;
}

void change(vector<array<ll,3>>&seg, int c, int l, int r, int pos, ll val, ll M, vector<ll>&Ri, vector<ll>&RS, vector<ll>&RD)
{
    lazy(seg,c,l,r,M,Ri,RS,RD);

    if(l==r)
    {
        seg[c][0]=val%M;
        return;
    }
    int m = (l+r)/2;
    if(pos<=m)change(seg,2*c,l,m,pos,val,M,Ri,RS,RD);
    else change(seg,2*c+1,m+1,r,pos,val,M,Ri,RS,RD);

    lazy(seg,2*c,l,m,M,Ri,RS,RD);
    lazy(seg,2*c+1,m+1,r,M,Ri,RS,RD);
    seg[c][0]=(seg[2*c][0] + seg[2*c+1][0])%M;
}

ll get(vector<array<ll,3>>&seg, int c, int l, int r, int L, int R, ll M, vector<ll>&Ri, vector<ll>&RS, vector<ll>&RD)
{
    lazy(seg,c,l,r,M,Ri,RS,RD);
    if(l>r || l>R || r<L)return 0;
    if(l>=L && r<=R)return seg[c][0];
    int m = (l+r)/2;
    return (get(seg,2*c,l,m,L,R,M,Ri,RS,RD) + get(seg,2*c+1,m+1,r,L,R,M,Ri,RS,RD))%M;
}

void AGP(vector<array<ll,3>>&seg, int c, int l, int r, int L, int R, ll M, ll S, ll D,
 vector<ll>&Ri, vector<ll>&RS, vector<ll>&RD)
{
    lazy(seg,c,l,r,M,Ri,RS,RD);
    if(l>r || l>R || r<L)return;
    if(l>=L && r<=R)
    {
        ll idx = l-L;
        D = (D*Ri[idx])%M;
        S = (S*Ri[idx])%M;
        S = (S + idx*D)%M;
        seg[c][1]=S;
        seg[c][2]=D;
        lazy(seg,c,l,r,M,Ri,RS,RD);
        return;
    }
    int m = (l+r)/2;
    AGP(seg,2*c,l,m,L,R,M,S,D,Ri,RS,RD);
    AGP(seg,2*c+1,m+1,r,L,R,M,S,D,Ri,RS,RD);
    seg[c][0] = (seg[2*c][0] + seg[2*c+1][0])%M;
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    cin>>t;
    while(t--)
    {
        cin>>n>>q>>R>>mod>>mod2;
        vector<array<ll,3>>seg1(4*n+4); //[sum % mod][lazyS][lazyD]
        vector<array<ll,3>>seg2(4*n+4); //[sum % mod2][lazyS][lazyD]
        vector<ll>Ri1(n+1);//R[i] = R^i
        vector<ll>RS1(n+1);//R[i] = 1 + R + R^2 + ... + R^i
        vector<ll>RD1(n+1);//R[i] = 0 + R + 2*R^2 + ... + i*R^i
        vector<ll>Ri2(n+1);//R[i] = R^i
        vector<ll>RS2(n+1);//R[i] = 1 + R + R^2 + ... + R^i
        vector<ll>RD2(n+1);//R[i] = 0 + R + 2*R^2 + ... + i*R^i

        for(int i=1; i<=n; i++)
            cin>>A[i];

        build(seg1,1,1,n,mod);
        build(seg2,1,1,n,mod2);
        precalc(n,Ri1,RS1,RD1,mod);
        precalc(n,Ri2,RS2,RD2,mod2);

        while(q--)
        {
            cin>>tp;
            if(tp==0)
            {
                ll S,D,L,R;
                cin>>S>>D>>L>>R;
                AGP(seg1,1,1,n,L,R,mod,S,D,Ri1,RS1,RD1);
                AGP(seg2,1,1,n,L,R,mod2,S,D,Ri2,RS2,RD2);

               // for(int i=1; i<=n; i++)
               //     cout<<get(seg1,1,1,n,i,i,mod,Ri1,RS1,RD1)<<(i==n?" <-after adding AGP\n":" ");
            }
            else if(tp==1)
            {
                ll x,g;
                cin>>x>>g;
                ll val = get(seg2,1,1,n,x,x,mod2,Ri2,RS2,RD2);
                val=powm(val,g,mod2);
                change(seg1,1,1,n,x,val,mod,Ri1,RS1,RD1);
                change(seg2,1,1,n,x,val,mod2,Ri2,RS2,RD2);
            }
            else
            {
                ll L,R;
                cin>>L>>R;
                cout<<get(seg1,1,1,n,L,R,mod,Ri1,RS1,RD1)<<"\n";
            }
        }
    }
}
