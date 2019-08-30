#include <bits/stdc++.h>
using namespace std;
#define ll long long

int n;
int A[505][505];
int seg[2018][2018][2]; // [0] for RMQ, and [1] for RMaxQ
#define oo 666666666

void buildy(int x, int xl, int xr, int y, int yl, int yr)
{
    if(yl==yr)
        {
            /*if we hit a leaf in inner segment tree, if it`s also a leaf
             *in main tree, we update it to array value, else it`s equal
             *to (function) of main tree children inner trees at same position*/
            seg[x][y][0]= ( xl==xr ? A[xr][yr] : min(seg[2*x][y][0],seg[2*x+1][y][0]));
            seg[x][y][1]= ( xl==xr ? A[xr][yr] : max(seg[2*x][y][1],seg[2*x+1][y][1]));
        }
    else
    {
        int ym = (yl+yr)/2;
        buildy(x,xl,xr,2*y,yl,ym);
        buildy(x,xl,xr,2*y+1,ym+1,yr);
        seg[x][y][0]=min(seg[x][2*y][0],seg[x][2*y+1][0]);
        seg[x][y][1]=max(seg[x][2*y][1],seg[x][2*y+1][1]);
    }
}

void build(int x, int xl, int xr)
{
    if(xl==xr)
        buildy(x,xl,xr,1,1,n);
    else
    {
        int xm = (xl + xr)/2;
        build(2*x,xl,xm);
        build(2*x+1,xm+1,xr);
        buildy(x,xl,xr,1,1,n);
    }
}


void updatey(int x, int xl, int xr, int y, int yl, int yr, int Y, int val)
{
    if(yl==yr)
    {
        seg[x][y][0]= ( xl==xr ? val : min(seg[2*x][y][0],seg[2*x+1][y][0]));
        seg[x][y][1]= ( xl==xr ? val : max(seg[2*x][y][1],seg[2*x+1][y][1]));
    }
    else
    {
        int ym = (yl+yr)/2;
        if(Y<=ym)
        updatey(x,xl,xr,2*y,yl,ym,Y,val);
        else
        updatey(x,xl,xr,2*y+1,ym+1,yr,Y,val);

        seg[x][y][0]= min(seg[x][2*y][0],seg[x][2*y+1][0]);
        seg[x][y][1]= max(seg[x][2*y][1],seg[x][2*y+1][1]);
    }
}

void update(int x, int xl, int xr, int X, int Y, int val)
{
    if(xl==xr)
        updatey(x,xl,xr,1,1,n,Y,val);
    else
    {
        int xm = (xl+xr)/2;
        if(X<=xm)
        update(2*x,xl,xm,X,Y,val);
        else
        update(2*x+1,xm+1,xr,X,Y,val);

        updatey(x,xl,xr,1,1,n,Y,val);
    }
}


int queryy(int x, int xl, int xr, int y, int yl, int yr, int YL, int YR, int type)
{
    if(yl > YR || yr < YL || yr < yl)return (type==0 ? oo : -oo);

    if(yl >= YL && yr <= YR)
    return seg[x][y][type];

    int ym = (yl+yr)/2;
    if(type==0)
        return min(queryy(x,xl,xr,2*y,yl,ym,YL,YR,type),queryy(x,xl,xr,2*y+1,ym+1,yr,YL,YR,type));
    else
        return max(queryy(x,xl,xr,2*y,yl,ym,YL,YR,type),queryy(x,xl,xr,2*y+1,ym+1,yr,YL,YR,type));
}

int query(int x, int xl, int xr, int XL, int XR, int YL, int YR, int type)
{
    if(xl > XR || xr < XL || xr < xl)return (type==0 ? oo : -oo);

    if(xl >= XL && xr <= XR)
        return queryy(x,xl,xr,1,1,n,YL,YR,type);

    int xm = (xl+xr)/2;
    if(type==0)
        return min(query(2*x,xl,xm,XL,XR,YL,YR,type),query(2*x+1,xm+1,xr,XL,XR,YL,YR,type));
    else
        return max(query(2*x,xl,xm,XL,XR,YL,YR,type),query(2*x+1,xm+1,xr,XL,XR,YL,YR,type));
}

int main()
{
    ios::sync_with_stdio(0);
    int q,x,y,x1,y1,v;
    char ch;
    cin>>n;
    for(int i=1; i<=n; i++)
        for(int j=1; j<=n; j++)
        cin>>A[i][j];

    cin>>q;
    build(1,1,n);

    while(q--)
    {
        cin>>ch;
        if(ch=='q')
        {
            cin>>x>>y>>x1>>y1;
            cout<<query(1,1,n,x,x1,y,y1,1)<<" "<<query(1,1,n,x,x1,y,y1,0)<<"\n";
        }
        else
        {
            cin>>x>>y>>v;
            update(1,1,n,x,y,v);
        }
    }
}
