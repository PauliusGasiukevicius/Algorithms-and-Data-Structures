#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

const int N = 10000001;
int root; //root to newest version of segment tree
int L[N], R[N], seg[4*N], nxt=2, V[N], nxtV=1;

void build(int c, int l, int r, vector<int>&A)
{
    if(l==r)
    {
        seg[c]=A[r];
        return;
    }
    int m =(l+r)/2;
    L[c] = nxt++;
    R[c] = nxt++;
    build(L[c],l,m,A);
    build(R[c],m+1,r,A);
    seg[c] = seg[L[c]] + seg[R[c]];

    //cout<<c<<" "<<l<<" "<<r<<" "<<seg[c]<<" <--build\n";
}

int update(int c, int l, int r, int pos, int val)
{
    //cout<<c<<" "<<l<<" "<<r<<" "<<seg[c]<<" <--\n";
    int nc = nxt++; //index of new version of seg tree
    if(l==r)
    {
        seg[nc]=seg[c]+val;
        return nc;
    }
    int m = (l+r)/2;
    L[nc]=L[c];
    R[nc]=R[c]; //sets links to old version

    if(pos <= m)
        L[nc] = update(L[c],l,m,pos,val);
    else
        R[nc] = update(R[c],m+1,r,pos,val);

        seg[nc] = seg[L[nc]] + seg[R[nc]];

    return nc;
}

int query(int c, int l, int r, int LL, int RR)
{
    if(l>r || l>RR || r<LL)return 0;
    if(l>=LL && r<=RR)return seg[c];
    int m = (l+r)/2;
    return query(L[c],l,m,LL,RR) + query(R[c],m+1,r,LL,RR);
}

int main()
{
    ios::sync_with_stdio(0);
    int n,q,type;
    V[0]=1;//V is version roots array
    cin>>n;
    vector<int>A(n+1);
    for(int i=1; i<=n; i++)
        cin>>A[i];

    build(1,1,n,A);

    cin>>q;
    while(q--)
    {
        cin>>type;
        if(type&1)
        {
            int v,pos,val;
            cin>>v>>pos>>val;
            V[nxtV++] = update(V[v],1,n,pos,val);
            //saves root of a new version in version array, and constructs new version based on version v
        }
        else
        {
            int v,l,r;
            cin>>v>>l>>r;
            cout<<query(V[v],1,n,l,r)<<"\n";
        }
    }
}
