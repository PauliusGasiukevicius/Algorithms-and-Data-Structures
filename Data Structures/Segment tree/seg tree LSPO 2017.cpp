#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

const int N = 200001;
int n,q;
ll seg[4*N][3];//[lazy][sum of a][sum of a^2]
ll A[N];
ll M = 1e9+7; //a prime

ll powm(ll a, ll n)
{
    if(n==0)return 1%M;
    if(n&1)return (a*powm(a,n-1)%M)%M;
    return powm((a*a)%M,n/2)%M;
}

void build(int c, int l, int r)
{
    if(l==r)
    {
        seg[c][1]=A[r]%M;
        seg[c][2]=(A[r]*A[r])%M;
        return;
    }
    int m = (l+r)/2;
    build(2*c,l,m);
    build(2*c+1,m+1,r);
    seg[c][1] = (seg[2*c][1] + seg[2*c+1][1])%M;
    seg[c][2] = (seg[2*c][2] + seg[2*c+1][2])%M;
}

void lazy(int c, int l, int r)
{
    ll x = seg[c][0];
    if(l!=r)
    {
        seg[2*c][0] = (seg[2*c][0] + x)%M;
        seg[2*c+1][0] = (seg[2*c+1][0] + x)%M;
    }
    seg[c][0]=0;

    seg[c][2] = (seg[c][2] + ((r-l+1)*(x*x%M))%M + 2*(x*seg[c][1])%M)%M;
    seg[c][1] = (seg[c][1] + (r-l+1)*x)%M;
}

void update(int c, int l, int r, int L, int R, ll x)
{
    lazy(c,l,r);

    if(l>r || l>R || r<L)return;
    if(l>=L && r<=R)
    {
        seg[c][0]+=x;
        lazy(c,l,r);
        return;
    }
    int m = (l+r)/2;
    update(2*c,l,m,L,R,x);
    update(2*c+1,m+1,r,L,R,x);
    seg[c][1] = (seg[2*c][1] + seg[2*c+1][1])%M;
    seg[c][2] = (seg[2*c][2] + seg[2*c+1][2])%M;
}

void updateSingle(int c, int l, int r, int pos, ll x)
{
    lazy(c,l,r);
    //cout<<c<<" "<<l<<" "<<r<<" "<<seg[c][1]<<"\n";

    if(pos > r || pos < l)return; //this instead of if to make lazy propagation work

    if(l==r)
    {
        seg[c][1]=x%M;
        seg[c][2]=(x*x)%M;
        return;
    }

    int m = (l+r)/2;
    updateSingle(2*c,l,m,pos,x);
    updateSingle(2*c+1,m+1,r,pos,x);

    seg[c][1] = (seg[2*c][1] + seg[2*c+1][1])%M;
    seg[c][2] = (seg[2*c][2] + seg[2*c+1][2])%M;
}

void bruteUpdateRange(int l, int r, ll x)
{
    for(int i=l; i<=r; i++)
        A[i]+=x;
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    ll inv2 = powm(2,M-2)%M;
    char ch;
    cin>>n>>q;
    for(int i=1; i<=n; i++)
        cin>>A[i];

    build(1,1,n);
    cout<< (((seg[1][1]*seg[1][1])%M - seg[1][2] + M)%M * inv2)%M <<"\n";

    while(q--)
    {
        cin>>ch;
        if(ch=='!')
        {
            ll pos,val;
            cin>>pos>>val;
            updateSingle(1,1,n,pos,val);
        }
        else
        {
            ll a,b,x;
            cin>>a>>b>>x;
            update(1,1,n,a,b,x);
        }

        cout<< (((seg[1][1]*seg[1][1])%M - seg[1][2] + M)%M * inv2)%M <<"\n";
    }
}
