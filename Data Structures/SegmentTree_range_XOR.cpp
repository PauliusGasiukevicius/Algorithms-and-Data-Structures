#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define oo INT_MAX/10

ll seg[400001][20];
ll lazy[400001];

void update(int c, int l, int r, int L, int R, int x)
{
    if(lazy[c])
    {
        for(int j=0; j<20; j++)
            if(lazy[c]&(1<<j))
            seg[c][j]= r-l+1 - seg[c][j];

        if(l!=r)
            lazy[2*c]^=lazy[c],lazy[2*c+1]^=lazy[c];
        lazy[c]=0;
    }

    if(l>r || l>R || r<L)return;

    if(l>=L && r<=R)
    {
        for(int j=0; j<20; j++)
            if(x&(1<<j))
            seg[c][j]= r-l+1 - seg[c][j];

        if(l!=r)
            lazy[2*c]^=x,lazy[2*c+1]^=x;
        return;
    }

    int m = (l+r)/2;
    update(2*c,l,m,L,R,x);
    update(2*c+1,m+1,r,L,R,x);

    for(int j=0; j<20; j++)
        seg[c][j]=seg[2*c][j]+seg[2*c+1][j];
}

ll query(int c, int l, int r, int L, int R)
{
    if(lazy[c])
    {
        for(int j=0; j<20; j++)
            if(lazy[c]&(1<<j))
            seg[c][j]= r-l+1 - seg[c][j];

        if(l!=r)
            lazy[2*c]^=lazy[c],lazy[2*c+1]^=lazy[c];
        lazy[c]=0;
    }

     if(l>r || l>R || r<L)return 0;

    if(l>=L && r<=R)
    {
        ll ats = 0;
        for(int j=0; j<20; j++)
            ats+=seg[c][j]*(1<<j);
        return ats;
    }
    int m = (l+r)/2;
    return query(2*c,l,m,L,R) + query(2*c+1,m+1,r,L,R);
}


int main()
{
    ios::sync_with_stdio(0);
    int n,q,t,L,R,x;
    cin>>n;
    vector<int>A(n+1);
    for(int i=1; i<=n; i++)
        cin>>A[i],update(1,1,n,i,i,A[i]);

    cin>>q;
    while(q--)
    {
        cin>>t>>L>>R;
        if(t==1)
            cout<<query(1,1,n,L,R)<<"\n";
        else
        {
            cin>>x;
            update(1,1,n,L,R,x);
        }
    }
}
