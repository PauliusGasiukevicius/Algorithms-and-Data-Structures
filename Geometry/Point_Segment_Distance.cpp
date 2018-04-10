#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

ld cross(ld x1, ld y1, ld x2, ld y2)
{return x2*y1-x1*y2;}

ld dot(ld x1, ld y1, ld x2, ld y2)
{return x1*x2+y1*y2;}

ld pw(ld x)
{return x*x;}

ld dist(ld x1, ld y1, ld x2, ld y2)
{return sqrt(pw(x1-x2)+pw(y1-y2));}

//Finds shortest distance between (x1,y1) and segment((x2,y2),(x3,y3))
ld PointToSegment(ld x1, ld y1, ld x2, ld y2, ld x3, ld y3)
{
    if(dot(x2-x3,y2-y3,x3-x1,y3-y1) > 0)return dist(x1,y1,x3,y3);
    if(dot(x3-x2,y3-y2,x2-x1,y2-y1) > 0)return dist(x1,y1,x2,y2);

    return fabs(cross(x1-x2,y1-y2,x1-x3,y1-y3))/dist(x2,y2,x3,y3);
}

int main()
{
    ios::sync_with_stdio(0);
    int t,n,m;
    cin>>t;
    while(t--)
    {
        cin>>n;
        vector<ld>x(n),y(n);
        for(int i=0; i<n; i++)
            cin>>x[i]>>y[i];

        cin>>m;
        vector<ld>X(m),Y(m);
        for(int i=0; i<m; i++)
            cin>>X[i]>>Y[i];

        X.push_back(X[0]);
        Y.push_back(Y[0]);

        ld ats=oo;

        for(int i=0; i<n; i++)
            for(int j=0; j+1<X.size(); j++)
                ats=min(ats,PointToSegment(x[i],y[i],X[j],Y[j],X[j+1],Y[j+1]));

        cout<<setprecision(13)<<fixed<<ats/2<<"\n";
    }
}
