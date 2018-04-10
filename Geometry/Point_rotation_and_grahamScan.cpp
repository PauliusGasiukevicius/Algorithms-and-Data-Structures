#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

ld cross(ld x1, ld y1, ld x2, ld y2)
{return x1*y2-x2*y1;}

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

pair<ld,ld> CircleCenterFrom3Points(ld x1, ld y1, ld x2, ld y2, ld x3, ld y3)
{
   ld d = 2*(x1*(y2-y3) + x2*(y3-y1) + x3*(y1-y2));
   ld xc = ((x1 * x1 + y1 * y1) * (y2 - y3) + (x2 * x2 + y2 * y2) *
            (y3 - y1) + (x3 * x3 + y3 * y3) * (y1 - y2)) / d;
   ld yc = ((x1 * x1 + y1 * y1) * (x3 - x2) + (x2 * x2 + y2 * y2) *
            (x1 - x3) + (x3 * x3 + y3 * y3) * (x2 - x1)) / d;
   return {xc,yc};
}

void R(ld& x, ld& y, ld A)
{
    ld pi = atan(1)*4;
    ld xi = cos(A*pi/180)*x - sin(A*pi/180)*y;
    ld yi = sin(A*pi/180)*x + cos(A*pi/180)*y;
    x = xi;
    y = yi;
}

void R(pair<ld,ld>&p, ld Ox, ld Oy, ld A)
{
    ld x = p.first;
    ld y = p.second;
    ld pi = atan(1)*4;
    ld xi = x - Ox;
    ld yi = y - Oy;
    x = cos(A*pi/180)*xi - sin(A*pi/180)*yi;
    y = sin(A*pi/180)*xi + cos(A*pi/180)*yi;
    x += Ox;
    y += Oy;
    p={x,y};
}

int CCW(ld x1, ld y1, ld x2, ld y2, ld x3, ld y3)
{
    ld a = cross(x2-x1,y2-y1,x3-x2,y3-y2);
    if(a>0)return -1;
    if(a<0)return 1;
    return 0;
}

vector<pair<ld,ld>> hull(vector<pair<ld,ld>>&P)
{
    for(int i=1; i<P.size(); i++)
        if(P[i].second < P[0].second || (P[i].second == P[0].second && P[i].first < P[0].first))
         swap(P[i],P[0]);

    sort(P.begin()+1,P.end(),[&P](pair<ld,ld>&a, pair<ld,ld>&b)
    {
    int o = CCW(P[0].first,P[0].second,a.first,a.second,b.first,b.second);
    if(o==0)return dist(P[0].first,P[0].second,a.first,a.second) < dist(P[0].first,P[0].second,b.first,b.second);
    return o<0;
    });

    vector<pair<ld,ld>>CH;
    CH.push_back(P[0]);
    CH.push_back(P[1]);
    CH.push_back(P[2]);

    for(int i=3; i<P.size(); i++)
    {
       while(CCW(CH[CH.size()-2].first,CH[CH.size()-2].second,CH.back().first,CH.back().second,P[i].first,P[i].second)>=0)
       CH.pop_back();
       CH.push_back(P[i]);
    }
    return CH;
}

int main()
{
    ios::sync_with_stdio(0);
    int t,n;
    cin>>t;

    while(t--)
    {
        cin>>n;
        vector<pair<ld,ld>>P;
        ld area = 0.0;

        for(int i=0; i<n; i++)
        {
            ld x,y,w,h,a;
            cin>>x>>y>>w>>h>>a;
            area+=w*h;
            P.push_back({x-w/2,y-h/2});
            R(P.back(),x,y,-a);
            P.push_back({x-w/2,y+h/2});
            R(P.back(),x,y,-a);
            P.push_back({x+w/2,y-h/2});
            R(P.back(),x,y,-a);
            P.push_back({x+w/2,y+h/2});
            R(P.back(),x,y,-a);
        }

        auto CH = hull(P);

        ld hullArea = 0.0;
        for(int i=1; i+1<CH.size(); i++)
            hullArea+=cross(CH[i].first-CH[0].first,CH[i].second-CH[0].second,CH[i+1].first-CH[0].first,CH[i+1].second-CH[0].second);
        hullArea=fabs(hullArea)/2;

        //cout<<fixed<<setprecision(2)<<area<<" "<<hullArea<<"\n";
        cout<<fixed<<setprecision(1)<<100*area/hullArea<<" %\n";
    }
}
