#include <bits/stdc++.h>
using namespace std;
#define ll long long

void update(vector<ll>&seg, int c, int l, int r, int x, int val)
{
    if(l==r)
    {
        seg[c]=val;
        return;
    }

    int m = (l+r)/2;
    if(x<=m)update(seg,2*c,l,m,x,val);
    else update(seg,2*c+1,m+1,r,x,val);

    seg[c]=seg[2*c]+seg[2*c+1];
}

ll query(vector<ll>&seg, int c, int l, int r, int L, int R)
{
    if(l > R || r < L || r<l)return 0;

    if(l>=L && r<=R)return seg[c];
    int m = (l+r)/2;

    return query(seg,2*c,l,m,L,R) + query(seg,2*c+1,m+1,r,L,R);
}

int main()
{
    ios::sync_with_stdio(0);
    int t,n;
    cin>>t;

    while(t--)
    {
        cin>>n;
        vector<vector<int>>A(n,vector<int>(2));

        for(int i=0; i<n; i++)
            cin>>A[i][0],A[i][1]=i+1;

        sort(A.begin(),A.end());

        vector<ll>seg(4*n);
        ll inv = 0;

        for(int i=n-1; i>=0; i--)
            {
                inv+=query(seg,1,1,n,1,A[i][1]);
                update(seg,1,1,n,A[i][1],1);
            }

        cout<<inv<<"\n";
    }
}
