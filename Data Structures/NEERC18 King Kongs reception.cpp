#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

ll sum[4000005]; //sum of visit times
ll mx[4000005]; //time when all of knights in interval will be done

void add(int c, int l, int r, int pos, ll val)
{
    if(l==r)
    {
        sum[c]+=val;
        mx[c]=r+sum[c];
        return;
    }
    int m = (l+r)/2;
    if(pos<=m)add(2*c,l,m,pos,val);
    else add(2*c+1,m+1,r,pos,val);

    sum[c]=sum[2*c]+sum[2*c+1];
    mx[c]=max(mx[2*c+1], mx[2*c]+sum[2*c+1]);
}

void query(int c, int l, int r, int tm, ll& ats)
{
    if(r<=tm)
    {
        ats=max(ats+sum[c],mx[c]);
        return;
    }
    int m = (l+r)/2;
    query(2*c,l,m,tm,ats);
    if(tm > m)query(2*c+1,m+1,r,tm,ats);
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int t;
    char ch;
    cin>>t;
    vector<array<int,2>>Q(t+1);
    int n = 1000000;

    for(int i=1; i<=1000000; i++)
        add(1,1,n,i,0);

    for(int i=1; i<=t; i++)
    {
        cin>>ch;
        if(ch=='+')
        {
            int pos,val;
            cin>>pos>>val;
            add(1,1,n,pos,val);
            Q[i] = {pos,val};
        }
        else if(ch=='-')
        {
            int idx;
            cin>>idx;
            add(1,1,n,Q[idx][0],-Q[idx][1]);
        }
        else
        {
            int tm;
            cin>>tm;
            ll ats = 0;
            query(1,1,n,tm,ats);
            cout<<ats-tm<<"\n";
        }
    }
}
