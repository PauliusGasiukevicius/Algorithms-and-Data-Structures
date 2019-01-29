#include <bits/stdc++.h>
using namespace std;

#define ll long long
#define T vector<ll>

void build(vector<T>&seg, vector<ll>&A, int c, int l, int r)
{
    if(l==r)
    {
        seg[c]={A[r-1],r};
        return;
    }

    int m = l + (r-l)/2;
    build(seg,A,2*c,l,m);
    build(seg,A,2*c+1,m+1,r);

    if(seg[2*c][0] >= seg[2*c+1][0])
    seg[c] = seg[2*c];
    else
    seg[c] = seg[2*c+1];
}

void update(vector<T>&seg, int c, int l, int r,int pos, int x)
{
    if(l==r)
    {
        seg[c][0] = x;
        return;
    }

    int m = l + (r-l)/2;

    if(pos<=m)
    update(seg,2*c,l,m,pos,x);
    else
    update(seg,2*c+1,m+1,r,pos,x);

    if(seg[2*c][0] >= seg[2*c+1][0])
    seg[c] = seg[2*c];
    else
    seg[c] = seg[2*c+1];
}


T query(vector<T>&seg, int c, int l, int r, int L, int R)
{
    if(L > r || R < l)
        {
            T e = {-1,0};
            return e;
        }

    if(l>=L && r<=R)return seg[c];

    int m = l + (r-l)/2;
    T A = query(seg,2*c,l,m,L,R);
    T B = query(seg,2*c+1,m+1,r,L,R);
    return (A[0] >= B[0] ? A : B);
}

int main()
{
    ios::sync_with_stdio(0);
    int n,m,L,R,cs=1;
    T zero = {0,0};
    char type;
    cin>>n;
        vector<ll>A(n);
        vector<T>seg(4*n);
        for(ll&x:A)cin>>x;
        build(seg,A,1,1,n);
        cin>>m;

        while(m--)
        {
            cin>>type>>L>>R;
            if(type=='U')
                update(seg,1,1,n,L,R);
            else
                {
                    T A = query(seg,1,1,n,L,R);

                        T B1 = (A[1] > L ? query(seg,1,1,n,L,A[1]-1) : zero);
                        T B2 = (A[1] < R ? query(seg,1,1,n,A[1]+1,R) : zero);

                        T B = (B1[0] >= B2[0] ? B1 : B2);

                    cout<<A[0]+B[0]<<"\n";
                }
        }
}
