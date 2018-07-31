#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666
const int N = 300005;
ll A[N];
ll seg[4*N][3]; //[sum][lazyA][lazyB]
ll F[N];
ll M = 1e9+9;

ll Fib(ll n, ll M, ll F1, ll F2)
{
    if(n==0)return 0;
    if(n==1)return F1;
    if(n==2)return F2;
    return (F[n-1]*F2 + F[n-2]*F1)%M;
}

ll FibSum(ll n, ll M, ll F1, ll F2)
{
    return (Fib(n+2,M,F1,F2)-F2+M)%M;
}

void build(int c, int l, int r)
{
    if(l==r)
    {
        seg[c][0]=A[r]%M;
        return;
    }
    int m = (l+r)/2;
    build(2*c,l,m);
    build(2*c+1,m+1,r);
    seg[c][0]=(seg[2*c][0] + seg[2*c+1][0])%M;
}

void lazyUpdate(int c, int l, int r)
{
    if(seg[c][1]==0 && seg[c][2]==0)return;
    int n = (r-l+1);
    ll sum = (FibSum(n,M,seg[c][1],seg[c][2]))%M;
    //cout<<"Sum of F("<<n<<") starting with: "<<seg[c][1]<<" "<<seg[c][2]<<" = "<<sum<<"\n";
    seg[c][0] = (seg[c][0]+sum)%M;
    if(l!=r)
    {
        // left child depends on current F0,F1
        seg[2*c][1]=(seg[2*c][1]+seg[c][1])%M;
        seg[2*c][2]=(seg[2*c][2]+seg[c][2])%M;

        ll m = (l+r)/2;
        ll n2 = (m-l+1);
        ll F0 = Fib(n2+1,M,seg[c][1],seg[c][2]);
        ll F1 = Fib(n2+2,M,seg[c][1],seg[c][2]);

        seg[2*c+1][1]=(seg[2*c+1][1]+F0)%M;
        seg[2*c+1][2]=(seg[2*c+1][2]+F1)%M;
    }
    seg[c][1]=seg[c][2]=0;
}

void update(int c, int l, int r, int L, int R, int idx)
{
    //cout<<"Now at ["<<l<<","<<r<<"]\n";
    lazyUpdate(c,l,r);
    if(l>r || l>R || r<L)return;
    if(l>=L && r<=R)
    {
        //cout<<"Interval "<<l<<" "<<r<<" is updated with "<<F[idx]<<" "<<F[idx+1]<<"\n";
        seg[c][1]=(seg[c][1]+F[idx])%M;
        seg[c][2]=(seg[c][2]+F[idx+1])%M;
        lazyUpdate(c,l,r);
        return;
    }
    int m = (l+r)/2;
    update(2*c,l,m,L,R,idx);
    int idxR = idx + max(m-max(L,l)+1,0);
    update(2*c+1,m+1,r,L,R,idxR);
    seg[c][0] = (seg[2*c][0] + seg[2*c+1][0])%M;
}

ll query(int c, int l, int r, int L, int R)
{
    lazyUpdate(c,l,r);
    if(l>r || r < L || l > R)return 0;
    if(l>=L && r<=R)return seg[c][0]%M;

    int m = (l+r)/2;
    return (query(2*c,l,m,L,R)%M + query(2*c+1,m+1,r,L,R)%M)%M;
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    F[1]=F[2]=1;
    for(int i=3; i<N; i++)
        F[i]=(F[i-1]+F[i-2])%M;

    int n,m,tp,L,R;
    cin>>n>>m;
    for(int i=1; i<=n; i++)
        cin>>A[i];

    build(1,1,n);
    while(m--)
    {
        cin>>tp>>L>>R;
        if(tp&1)
        update(1,1,n,L,R,1);
        else
        cout<<query(1,1,n,L,R)<<"\n";
    }
}
