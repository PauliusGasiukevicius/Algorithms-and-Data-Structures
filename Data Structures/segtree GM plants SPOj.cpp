#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld double
#define oo 666666666

void lazy(vector<array<int,2>>&seg, int c, int l, int r)
{
    if(!seg[c][0])return;
    seg[c][1] = (r-l+1) - seg[c][1];
    if(l!=r)seg[2*c][0]^=1,seg[2*c+1][0]^=1;
    seg[c][0]^=1;
}

void update(vector<array<int,2>>&seg, int c, int l, int r, int L, int R)
{
    lazy(seg,c,l,r);
    if(l>r || l>R || r<L)return;
    if(l>=L && r<=R)
    {
        seg[c][0]^=1;
        lazy(seg,c,l,r);
        return;
    }
    int m = (l+r)/2;
    update(seg,2*c,l,m,L,R);
    update(seg,2*c+1,m+1,r,L,R);
    seg[c][1] = seg[2*c][1] + seg[2*c+1][1];
}

ll query(vector<array<int,2>>&seg, int c, int l, int r, int L, int R)
{
    lazy(seg,c,l,r);
    if(l>r || l>R || r<L)return 0;
    if(l>=L && r<=R)return seg[c][1];
    int m = (l+r)/2;
    return query(seg,2*c,l,m,L,R) + query(seg,2*c+1,m+1,r,L,R);
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    int t,nx,ny,nz,q,tp,l,r;
    cin>>t;

    while(t--)
    {
        cin>>nx>>ny>>nz>>q;
        vector<array<int,2>>segX(4*nx+1),segY(4*ny+1),segZ(4*nz+1);
        while(q--)
        {
            cin>>tp;
            if(tp==0)
            {
                cin>>l>>r;
                update(segX,1,1,nx,l+1,r+1);
            }
            else if(tp==1)
            {
                cin>>l>>r;
                update(segY,1,1,ny,l+1,r+1);
            }
            else if(tp==2)
            {
                cin>>l>>r;
                update(segZ,1,1,nz,l+1,r+1);
            }
            else
            {
                ll x1,y1,z1,x2,y2,z2;
                cin>>x1>>y1>>z1>>x2>>y2>>z2;
                ll rx = query(segX,1,1,nx,x1+1,x2+1);
                ll ry = query(segY,1,1,ny,y1+1,y2+1);
                ll rz = query(segZ,1,1,nz,z1+1,z2+1);
                ll gx = (x2-x1+1)-rx;
                ll gy = (y2-y1+1)-ry;
                ll gz = (z2-z1+1)-rz;
                //cout<<rx<<" "<<ry<<" "<<rz<<"\n";
                ll ats = (rx*gy*gz) + (gx*ry*gz) + (gx*gy*rz) + (rx*ry*rz);

                cout<<ats<<"\n";
            }
        }
    }
}
