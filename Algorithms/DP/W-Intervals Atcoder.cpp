#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

vector<array<ll,2>>A[200005];
ll seg[800005][2];

void lazy(int c, int l, int r)
{
    seg[c][0]+=seg[c][1];
    if(l!=r)
    {
        seg[2*c][1]+=seg[c][1];
        seg[2*c+1][1]+=seg[c][1];
    }
    seg[c][1]=0;
}

void update(int c, int l, int r, int L, int R, ll val)
{
    lazy(c,l,r);
    if(l>r || r < L || l > R)return;
    if(l>=L && r<=R)
    {
        seg[c][1]+=val;
        lazy(c,l,r);
        return;
    }
    int m = (l+r)/2;
    update(2*c,l,m,L,R,val);
    update(2*c+1,m+1,r,L,R,val);
    seg[c][0]=max(seg[2*c][0],seg[2*c+1][0]);
}

ll get(int c, int l, int r, int L, int R)
{
    lazy(c,l,r);
    if(l>r || r < L || l > R)return -1e18;
    if(l>=L && r<=R)return seg[c][0];

    int m = (l+r)/2;
    ll ats = max(get(2*c,l,m,L,R), get(2*c+1,m+1,r,L,R));
    seg[c][0]=max(seg[2*c][0],seg[2*c+1][0]);
    return ats;
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n,m;
    cin>>n>>m;

    while(m--)
    {
        ll L,R,val;
        cin>>L>>R>>val;
        A[L].push_back({val,L});
        A[R+1].push_back({-val,L});
    }

    ll ats = 0;

    for(int i=1; i<=n; i++) //lets choose which position in string should be '1'
    {
        for(auto&x : A[i])update(1,0,n,0,x[1]-1,x[0]);
        //^if some interval starts here we increase all previous positions [0,L-1] by its value
        //because i is in the interval
        //if some interval ends when we decrease all previous positions [0,L-1] by its value
        //because i is not in interval anymore
        ll cur = get(1,0,n,0,i-1); //we get maximum value of prefix [0,i-1] -
        //^its the best we can get with prefix[1...i] bits done
        ats=max(ats,cur);
        update(1,0,n,i,i,cur);//finally we add our current best for prefix[0,i] to the tree
        //now other queries can try extending this answer

        //its like brute-force where we would choose some j in range [0,i-1]
        //(0 meaning no bits on yet) to extend answer
        //yet segment tree saves us from N^2, and we can do this in N log N
    }

    cout<<ats;
}
