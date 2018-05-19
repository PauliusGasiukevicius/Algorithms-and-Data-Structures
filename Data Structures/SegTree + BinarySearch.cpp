#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

int mn[4*100001];
int mx[4*100001];
int lazy[4*100001];

void build(int c, int l, int r, vector<pair<int,int>>&A)
{
    if(l==r)
    {
        mn[c]=mx[c]=A[r-1].first;
        return;
    }
    int m = (l+r)/2;
    build(2*c,l,m,A);
    build(2*c+1,m+1,r,A);
    mn[c]=min(mn[2*c],mn[2*c+1]);
    mx[c]=max(mx[2*c],mx[2*c+1]);
}

void lazyUpdate(int c, int l, int r)
{
    if(lazy[c]==0)return;
    mn[c]+=lazy[c];
    mx[c]+=lazy[c];

    if(l!=r)
    {
    lazy[2*c]+=lazy[c],lazy[2*c+1]+=lazy[c];
    mn[c]=min(mn[2*c]+lazy[2*c],mn[2*c+1]+lazy[2*c+1]);
    mx[c]=max(mx[2*c]+lazy[2*c],mx[2*c+1]+lazy[2*c+1]);
    }
    lazy[c]=0;
}

void update(int c, int l, int r, int L, int R, int val)
{
    lazyUpdate(c,l,r);
    if(l>r || l>R || r<L)return;
    if(l>=L && r<=R)
    {
        mn[c]+=val;
        mx[c]+=val;
        if(l!=r)
        {
            lazy[2*c]+=val,lazy[2*c+1]+=val;
            mn[c]=min(mn[2*c]+lazy[2*c],mn[2*c+1]+lazy[2*c+1]);
            mx[c]=max(mx[2*c]+lazy[2*c],mx[2*c+1]+lazy[2*c+1]);
        }
        return;
    }

    int m = (l+r)/2;
    update(2*c,l,m,L,R,val);
    update(2*c+1,m+1,r,L,R,val);
    mn[c]=min(mn[2*c]+lazy[2*c],mn[2*c+1]+lazy[2*c+1]);
    mx[c]=max(mx[2*c]+lazy[2*c],mx[2*c+1]+lazy[2*c+1]);
}

int LowerBound(int c, int l, int r, int val) // finds lowest index with value at least val
{//assumes initial array is sorted, and will remain so
lazyUpdate(c,l,r);
    while(l!=r)
    {
        int m = (l+r)/2;
        lazyUpdate(2*c,l,m);
        lazyUpdate(2*c+1,m+1,r);
        //cout<<"Interval: "<<l<<" "<<r<<", m= "<<m<<", mx[2*c] = "<<mx[2*c]<<" mx[2*c+1]="<<mx[2*c+1]<<" "<<val<<"\n";
        if(mx[2*c]>=val)
            c=2*c,r=m;
        else
            c=2*c+1,l=m+1;
    }
    //cout<<l<<" "<<r<<"\n";
    //cout<<(mn[c]>=val ? r : r+1)<<" <- lowerBound\n";
    return mn[c]>=val ? r : r+1;
}

int getValue(int c, int l, int r, int index)
{
lazyUpdate(c,l,r);
    while(l!=r)
    {
        int m= (l+r)/2;
        lazyUpdate(2*c,l,m);
        lazyUpdate(2*c+1,m+1,r);

        if(index<=m)
            c=2*c,r=m;
        else
            c=2*c+1,l=m+1;
    }
    return mn[c];
}

int main()
{
    ios::sync_with_stdio(0);
    int n,m,type,x;
    cin>>n>>m;
    vector<pair<int,int>>A;
    vector<int>I(n+1),RI(n+1); //mapping indexes, and reverse mapping
    A.reserve(n);

    for(int i=1,x; i<=n; i++)
    cin>>x,A.push_back({x,i});

    sort(A.begin(),A.end());

    for(int i=0; i<A.size(); i++)
        I[A[i].second]=i+1,RI[i+1]=A[i].second;

    build(1,1,n,A);

    while(m--)
    {
        cin>>type>>x;
        if(type==1)
        {
            int val = getValue(1,1,n,I[x]);
            int lastIndex = LowerBound(1,1,n,val+1)-1;
            int idx = RI[lastIndex];

           // cout<<x<<" "<<I[x]<<" "<<lastIndex<<" "<<RI[lastIndex]<<"\n";

            swap(I[x],I[idx]);
            swap(RI[I[x]],RI[I[idx]]);

          //  cout<<x<<" "<<I[x]<<" "<<lastIndex<<" "<<RI[lastIndex]<<"\n";

           // cout<<getValue(1,1,n,lastIndex)<<" <- before update\n ";
            update(1,1,n,lastIndex,lastIndex,1);
           // cout<<getValue(1,1,n,lastIndex)<<" <- after update\n ";
        }
        else if(type==2)
            cout<<n+1-LowerBound(1,1,n,x)<<"\n";
        else
            update(1,1,n,LowerBound(1,1,n,x),n,-1);
    }
}
