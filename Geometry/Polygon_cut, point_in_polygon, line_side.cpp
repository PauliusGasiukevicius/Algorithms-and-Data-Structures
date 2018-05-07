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

void printPolygon(vector<pair<ld,ld>>&A)
{
    for(auto&p:A)
        cout<<"("<<p.first<<", "<<p.second<<"), ";
    cout<<"\n";
}

ld polygonArea(vector<pair<ld,ld>>&A)
{
    ld ats = 0.0;
    for(int i=2; i<A.size(); i++)
        ats+=cross(A[i].first-A[0].first,A[i].second-A[0].second,A[i-1].first-A[0].first,A[i-1].second-A[0].second);
    return fabs(ats/2);
}

bool inPolygon(vector<pair<ld,ld>>&A, ld x, ld y)
{
  int i, j, nvert = A.size();
  bool c = false;

  for(i = 0, j = nvert - 1; i < nvert; j = i++) {
    if( ( (A[i].second >= y ) != (A[j].second >= y) ) &&
        (x <= (A[j].first - A[i].first) * (y - A[i].second) / (A[j].second - A[i].second) + A[i].first)
      )
      c = !c;
  }

  return c;
}

// 0 - on line, -1 - one side, 1 - other side
ld lineSide(ld x, ld y, ld x1, ld y1, ld x2, ld y2)
{return (x-x1)*(y2-y1) - (y-y1)*(x2-x1);}

//only for convex polygon, only full cuts, cut with vertical line not implemented yet
void cut(vector<pair<ld,ld>>&A, ld x, ld y, ld x1, ld y1, ld x2, ld y2)
{
    set<pair<ld,ld>>H; // stores hit points

    if(x1!=x2)//if not vertical line
    {
    //get cutting line
    ld a1 = (y1-y2)/(x1-x2);
    ld b1 = y1 - a1*x1;
    A.push_back(A[0]); // reinsert point to examine segment A[0]--A[N]
    for(int i=1; i<A.size(); i++)
        if(A[i].first!=A[i-1].first)//if not vertical segment
    {
        ld a2 = (A[i].second-A[i-1].second)/(A[i].first-A[i-1].first);
        ld b2 = A[i].second - a2*A[i].first;

        ld xh = (b2-b1)/(a1-a2);
        ld yh = a2*xh+b2;
        if(xh>=min(A[i].first,A[i-1].first) && xh<=max(A[i].first,A[i-1].first)
           && yh>=min(A[i].second,A[i-1].second) && yh<=max(A[i].second,A[i-1].second))
        H.insert({xh,yh});
    }else //we have vertical segment
    {
        ld yh = a1*A[i].first+b1;
        if(yh>=min(A[i].second,A[i-1].second) && yh<=max(A[i].second,A[i-1].second))
        H.insert({A[i].first,yh});
    }
    A.pop_back();//remove extra A[0]
    }

    //cout<<"Hit points: ";
    //for(auto p:H)cout<<p.first<<" "<<p.second<<"  <-hit\n";

    if(H.size() < 2)return; // line only touches 1 point or misses so no point in continuing

    set<pair<ld,ld>>L,R;
    for(auto&p:A)
    {
        if(lineSide(p.first,p.second,x1,y1,x2,y2)<=0)L.insert(p);
        if(lineSide(p.first,p.second,x1,y1,x2,y2)>=0)R.insert(p);
    }

    L.insert(*H.begin());
    L.insert(*H.rbegin());
    R.insert(*H.begin());
    R.insert(*H.rbegin());

    vector<pair<ld,ld>>side1,side2;
    for(auto p : L)side1.push_back(p);
    for(auto p : R)side2.push_back(p);

    //convex hull is purely to order points...
    side1 = hull(side1);
    side2 = hull(side2);

    if(inPolygon(side1,x,y))A=side1;
    else A=side2;
    return;
}

int main()
{
    ios::sync_with_stdio(0);
    ll n,w,h,cs=1;
    ld x,y,x1,y1,x2,y2;
    while(cin>>n>>w>>h>>x>>y)
    {
        vector<pair<ld,ld>>A = {{0,0},{w,0},{w,h},{0,h}};

        while(n--)
        {
            cin>>x1>>y1>>x2>>y2;
            cut(A,x,y,x1,y1,x2,y2);
            //cout<<"After cutting: \n";
            //printPolygon(A);
           // cout<<"Area = "<<setprecision(3)<<fixed<<polygonArea(A)<<"\n";
        }

        cout<<"Case #"<<cs++<<": "<<setprecision(3)<<fixed<<polygonArea(A)<<"\n";
    }
}
