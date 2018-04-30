#include <bits/stdc++.h>
using namespace std;
#define ld long double
#define ll long long
#define oo 666666666666666

ld pw2(ld x)
{
    return x*x;
}

ld euclid(ld x1, ld y1, ld x2, ld y2)
{
    return sqrt(pw2(x1-x2)+pw2(y1-y2));
}

int main()
{
    ios::sync_with_stdio(0);
    ld X,Y,n;
    while(cin>>X>>Y>>n)
    {
        ld best = oo;
        ld x = 0;
        ld y = 0;

        ld x1,y1,x2,y2;
        cin>>x2>>y2;

        for(int i=0; i<n; i++)
        {
            x1=x2,y1=y2;
            cin>>x2>>y2;

            ld dist = euclid(X,Y,x1,y1);
                if(dist < best)
                    best=dist,x=x1,y=y1;

                dist = euclid(X,Y,x2,y2);
                if(dist < best)
                    best=dist,x=x2,y=y2;

            //finding line
            ld a = (y1-y2)/(x1-x2);
            ld c = y1 - x1*a;

            ld mnX=min(x1,x2);
            ld mnY=min(y1,y2);
            ld mxX=max(x1,x2);
            ld mxY=max(y1,y2);

            //special case: horizontal line
            if(a<1e-7)
            {
                if(X>=mnX && X<=mxX)
                {
                    ld dist = euclid(X,Y,X,c);
                if(dist < best)
                    best=dist,x=X,y=c;
                }
                continue;
            }

            //finding perpendicular line
            ld a2 = -1.0/a;
            ld c2 = Y - X*a2;

            // y1 = y2
            // a*x+c = a2*x+c2
            // a*x - a2*x = c2-c
            // x = (c2-c)/(a-a2)
            //finding intersection
            ld xh = (c2-c)/(a-a2);
            ld yh = a*xh+c;

            if(xh>=mnX && xh<=mxX && yh>=mnY && yh<=mxY)
            {
                ld dist = euclid(X,Y,xh,yh);
                if(dist < best)
                    best=dist,x=xh,y=yh;
            }
        }

        cout<<setprecision(4)<<fixed<<x<<"\n"<<y<<"\n";
    }
}
