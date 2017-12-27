#include <bits/stdc++.h>
using namespace std;
#define ll long long

struct Node
{
    //variables: (stuff needed to solve problem, like lazy field, sum field, etc)
    ll prefix, suffix, best, sum;
    //Merge procedure to merge 2 nodes
    void Merge(Node& L, Node& R)
    {
        sum = L.sum + R.sum;
        prefix = max(L.prefix, L.sum + R.prefix);
        suffix = max(R.suffix, R.sum + L.suffix);
        best = max({L.best,R.best,L.suffix+R.prefix});
    }

    //procedure for initial node initialization, can have parameters (i.e. input array element....)
    void Init(int x)
    {
        prefix = suffix = best = sum = x;
    }
};

void build(vector<Node>&seg, vector<int>&A, int l, int r, int c)
{
    if(l==r)
    {
        seg[c].Init(A[r]);
        return;
    }

    int m = l + (r-l)/2;
    build(seg,A,l,m,2*c);
    build(seg,A,m+1,r,2*c+1);
    seg[c].Merge(seg[2*c],seg[2*c+1]);
}


Node query(vector<Node>&seg, int l, int r, int c, int L, int R)
{
    if(l>=L && r<=R)
        return seg[c];

    int m = l + (r-l)/2;

    if(L > m)return query(seg,m+1,r,2*c+1,L,R);
    else if(R <= m)return query(seg,l,m,2*c,L,R);

    Node left = query(seg,l,m,2*c,L,R);
    Node right = query(seg,m+1,r,2*c+1,L,R);
    Node ats;
    ats.Merge(left,right);
    return ats;
}

void PointUpdate(vector<Node>&seg, int l ,int r, int c, int x, int y)
{
    if(l==r)
    {
        seg[c].Init(y);
        return;
    }

     int m = l + (r-l)/2;

     if(x<=m)
        PointUpdate(seg,l,m,2*c,x,y);
     else
        PointUpdate(seg,m+1,r,2*c+1,x,y);

    seg[c].Merge(seg[2*c],seg[2*c+1]);
}

int main()
{
    ios::sync_with_stdio(0);
    int n,m,l,r,type,x,y;
    cin>>n;
    vector<int>A(n);
    for(auto&x:A)cin>>x;

    vector<Node>seg(4*n);
    build(seg,A,0,n-1,1);

    cin>>m;
    while(m--)
    {
        cin>>type>>x>>y;
        if(type==1)
        cout<<query(seg,0,n-1,1,x-1,y-1).best<<"\n";
        else
            PointUpdate(seg,0,n-1,1,x-1,y);
    }
}
