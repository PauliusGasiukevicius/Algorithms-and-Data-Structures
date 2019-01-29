#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666
 
int A[100001];
int seg[400001][7];//[total sum][sum x^2][sum x][???][lazy a][lazy b][lazy c]
int MOD = 10007;
 
void build(int c, int l, int r)
{
    if(l==r)
    {
        seg[c][1]=A[r]*A[r]%MOD;
        seg[c][2]=A[r]%MOD;
        return;
    }
    int m = (l+r)/2;
    build(2*c,l,m);
    build(2*c+1,m+1,r);
    seg[c][1] = (seg[2*c][1] + seg[2*c+1][1]) %MOD;
    seg[c][2] = (seg[2*c][2] + seg[2*c+1][2]) %MOD;
    //cout<<c<<" "<<seg[c][1]<<" "<<seg[c][2]<<"\n";
}
 
void lazy(int c, int l, int r)
{
    seg[c][0]+=((seg[c][6]*(r-l+1))%MOD + (seg[c][5]*seg[c][2])%MOD + (seg[c][4]*seg[c][1])%MOD)%MOD;
    seg[c][0]%=MOD;
    if(l!=r)
    {
        seg[2*c][6]+=seg[c][6];
        seg[2*c][5]+=seg[c][5];
        seg[2*c][4]+=seg[c][4];
        seg[2*c+1][6]+=seg[c][6];
        seg[2*c+1][5]+=seg[c][5];
        seg[2*c+1][4]+=seg[c][4];
 
        seg[2*c][6]%=MOD;
        seg[2*c][5]%=MOD;
        seg[2*c][4]%=MOD;
        seg[2*c+1][6]%=MOD;
        seg[2*c+1][5]%=MOD;
        seg[2*c+1][4]%=MOD;
    }
    seg[c][4]=seg[c][5]=seg[c][6]=0;
}
 
void add(int c, int l, int r, int L, int R, int A, int B, int C)
{
    lazy(c,l,r);
    if(l>r || l>R || r<L)return;
    if(l>=L && r<=R)
    {
        seg[c][4]+=A;
        seg[c][5]+=B;
        seg[c][6]+=C;
 
        seg[c][4]%=MOD;
        seg[c][5]%=MOD;
        seg[c][6]%=MOD;
        lazy(c,l,r);
        return;
    }
    int m = (l+r)/2;
    add(2*c,l,m,L,R,A,B,C);
    add(2*c+1,m+1,r,L,R,A,B,C);
    seg[c][0] = (seg[2*c][0] + seg[2*c+1][0]) %MOD;
}
 
ll get(int c, int l, int r, int L, int R)
{
    lazy(c,l,r);
    if(l>r || l>R || r<L)return 0;
    if(l>=L && r<=R)return seg[c][0]%MOD;
    int m = (l+r)/2;
    return (get(2*c,l,m,L,R) + get(2*c+1,m+1,r,L,R))%MOD;
}
 
int main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    int n,m;
    cin>>n>>m;
    for(int i=1; i<=n; i++)
        A[i]=(i-1)%MOD;
 
    build(1,1,n);
 
    while(m--)
    {
        int tp;
        cin>>tp;
        if(tp==0)
        {
            int l,r,a,b,c;
            cin>>l>>r>>a>>b>>c;
           add(1,1,n,l+1,r+1,a%MOD,b%MOD,c%MOD);
        }
        else
        {
            int l,r;
            cin>>l>>r;
            cout<<get(1,1,n,l+1,r+1)%MOD<<"\n";
        }
    }
}
