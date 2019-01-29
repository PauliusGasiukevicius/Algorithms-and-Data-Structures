#include <bits/stdc++.h>
using namespace std;
 
#define ll long long
 
void build(vector<ll>&seg, vector<ll>&A, int c, int l, int r)
{
    if(l==r)
    {
        seg[c]=A[r-1];
        return;
    }
 
    int m = l + (r-l)/2;
    build(seg,A,2*c,l,m);
    build(seg,A,2*c+1,m+1,r);
    seg[c] = seg[2*c] + seg[2*c+1];
}
 
void modify(vector<ll>&seg, int c, int l, int r,int L, int R)
{
    if(seg[c] <= r-l+1)return;
    if(L > r || R < l)return;
 
    if(l==r)
    {
        seg[c] = sqrt(seg[c]);
        return;
    }
 
    int m = l + (r-l)/2;
    modify(seg,2*c,l,m,L,R);
    modify(seg,2*c+1,m+1,r,L,R);
    seg[c] = seg[2*c] + seg[2*c+1];
}
 
ll query(vector<ll>&seg, int c, int l, int r, int L, int R)
{
    if(L > r || R < l)return 0;
 
    if(l>=L && r<=R)return seg[c];
 
    int m = l + (r-l)/2;
    return query(seg,2*c,l,m,L,R) + query(seg,2*c+1,m+1,r,L,R);
}
int main()
{
    ios::sync_with_stdio(0);
    int n,m,type,L,R,cs=1;
 
    while(cin>>n)
    {
        vector<ll>A(n);
        vector<ll>seg(4*n);
        for(ll&x:A)cin>>x;
        build(seg,A,1,1,n);
        cin>>m;
        cout<<"Case #"<<cs++<<":\n";
        while(m--)
        {
            cin>>type>>L>>R;
            if(type==0)
                modify(seg,1,1,n,min(L,R),max(L,R));
            else
                cout<<query(seg,1,1,n,min(L,R),max(L,R))<<"\n";
        }
        cout<<"\n";
    }
}
