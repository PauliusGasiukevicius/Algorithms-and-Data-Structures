#pragma GCC opointimize("Ofast")

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 1234567890

///NOTE: All this is made with mainly integers in mind, so if doubles are needed, some function will need to be modified:
//i.e. instead of something == 0, fabs(something) < epsilon and so on

///Points
typedef ll T;
const ld PI = acos(-1);
struct point{
    T x,y;
    point operator+(point p){return {x+p.x, y+p.y};}
    point operator-(point p){return {x-p.x, y-p.y};}
    point operator*(T d){return {x*d, y*d};}
    point operator/(T d){return {x/d, y/d};}   // only for floating-point
    bool operator<(const point& a) const {return x<a.x || (x==a.x && y < a.y);}
};

bool operator==(point a, point b) {return a.x == b.x && a.y == b.y;}
bool operator!=(point a, point b) {return !(a == b);}
ostream& operator<<(ostream& os, point p) {return os << "("<< p.x << "," << p.y << ")";}

template <typename T> int sgn(T x) {return (T(0) < x) - (x < T(0));} //wtf is this

T sq(point p) {return p.x*p.x + p.y*p.y;} //just square cause pow is doubles only + not precise
ld abs(point p) {return sqrt(sq(p));} //euclidean distance between points

point scale(point c, ld factor, point p) {return c + (p-c)*factor;} //scales point p around center c by some factor
point rot(point p, ld a) {return {p.x*cos(a) - p.y*sin(a), p.x*sin(a) + p.y*cos(a)};}
//around origin by radians, forgot if clockwise or not, just try with/without minus sign

point perp(point p) {return {-p.y, p.x};} //perpendicular to some vector

T dot(point v, point w) {return v.x*w.x + v.y*w.y;}
ld angle(point v, point w) {return acos(max((ld)-1.0, min((ld)1.0, dot(v,w) / abs(v) / abs(w))));}

T cross(point v, point w) {return v.x*w.y - v.y*w.x;}
bool isPerp(point v, point w) {return dot(v,w) == 0;}
T orient(point a, point b, point c) {return cross(b-a,c-a);}

bool inAngle(point a, point b, point c, point p){ //checks if point p is in angle between lines ab and ac
    assert(orient(a,b,c) != 0);
    if (orient(a,b,c) < 0) swap(b,c);
    return orient(a,b,p) >= 0 && orient(a,c,p) <= 0;
}

ld orientedAngle(point a, point b, point c) {//angle, going from b to c around a
    if (orient(a,b,c) >= 0)return angle(b-a, c-a);
    return 2*PI - angle(b-a, c-a);
}

///Lines
struct line{
    point v;
    T c;
    line(point v, T c) : v(v), c(c) {} // From direction vector v and offset c
    line(T a, T b, T c) : v({b,-a}), c(c) {} // From equation ax+by=c
    line(point p, point q) : v(q-p), c(cross(v,p)) {} // From points P and Q

    T side(point p) {return cross(v,p)-c;}
    ld dist(point p){return abs(side(p)) / abs(v);} //distance from point to line
    ld sqDist(point p) {return side(p)*side(p) / (ld)sq(v);} //squared distance (more precise for comparisons)
    line perpThrough(point p){return {p, p + perp(v)};} //gives line perpendicular to current one through some point
    bool cmpProj(point p, point q){return dot(v,p) < dot(v,q);} //allows to sort points along line direction
    line translate(point t) {return {v, c + cross(v,t)};} //translates a line by some vector
    line shiftLeft(ld dist) {return {v, c + dist*abs(v)};} //moves line in direction perpendicular to line

    bool intersect(line l1, line l2, point &out) //Finds intersection of 2 lines
    {
        T d = cross(l1.v, l2.v);
        if (d == 0)return false;
        out = (l2.v*l1.c - l1.v*l2.c) / d; // requires floating-point coordinates
        return true;
    }

    //The orthogonal projection of a point P on a line l is the point on l that is closest to P
    point proj(point p){return p - perp(v)*side(p)/sq(v);};
    //reflection is like mirroring point along line to other side
    point refl(point p){return p - perp(v)*2*side(p)/sq(v);}

    //bisector is such a line that has equal distance to both other lines
    line bisector(line l1, line l2, bool interior)
    {
        assert(cross(l1.v, l2.v) != 0); // l1 and l2 cannot be parallel!
        double sign = interior ? 1 : -1;
        return {l2.v/abs(l2.v) + l1.v/abs(l1.v) * sign, l2.c/abs(l2.v) + l1.c/abs(l1.v) * sign};
    }
};

///Line Segments
//checks if point p is in circle drawn on points a b with diameter (dist(a,b))
bool inDisk(point a, point b, point p) {return dot(a-p, b-p) <= 0;}
//checks if point p is on segment AB
bool onSegment(point a, point b, point p) {return orient(a,b,p) == 0 && inDisk(a,b,p);}

//if properIntersection exists (proper means not endpoint && only single point
bool properInter(point a, point b, point c, point d, point &out){
        ld oa = orient(c,d,a),
           ob = orient(c,d,b),
           oc = orient(a,b,c),
           od = orient(a,b,d);
// Proper intersection exists iff opposite signs
    if (oa*ob < 0 && oc*od < 0)
    {
        out = (a*ob - b*oa) / (ob-oa);
        return true;
    }
    return false;
}

//return set of 0..2 points, if 0 - dont intersect, 1 - 1 intersection point, 2 - interval of all points in given range
set<point> intersection(point a, point b, point c, point d){
    point out;
    if (properInter(a,b,c,d,out))return {out};
    set<point> s;
    if (onSegment(c,d,a))s.insert(a);
    if (onSegment(c,d,b))s.insert(b);
    if (onSegment(a,b,c))s.insert(c);
    if (onSegment(a,b,d))s.insert(d);
    return s;
}

//Finds closest distance from point p to segment AB
ld segPoint(point a, point b, point p){
    if (a != b)
    {
        line l(a,b);
        if (l.cmpProj(a,p) && l.cmpProj(p,b)) // if closest to projection
            return l.dist(p); // output distance to line
    }
    return min(abs(p-a), abs(p-b)); // otherwise distance to A or B
}

//returns min distance between 2 segments
ld segSeg(point a, point b, point c, point d){
    point dummy;
    if (properInter(a,b,c,d,dummy))return 0;
    return min({segPoint(a,b,c), segPoint(a,b,d),segPoint(c,d,a), segPoint(c,d,b)});
}


///Polygons

bool cw(point a, point b, point c) {return orient(a,b,c) < 0;}
bool ccw(point a, point b, point c) {return orient(a,b,c) > 0;}

vector<point> convex_hull(vector<point> a) {
    //Finds 2D convex hull in O(nlogn), gives points in counterclockwise order,
    //ignores points on border
    if (a.size() == 1)return a;
    sort(a.begin(), a.end());
    point p1 = a[0], p2 = a.back();
    vector<point> up, down;
    up.push_back(p1);
    down.push_back(p1);

    for (int i = 1; i < (int)a.size(); i++)
    {
        if (i == a.size() - 1 || cw(p1, a[i], p2))
        {
            while (up.size() >= 2 && !cw(up[up.size()-2], up[up.size()-1], a[i]))
                up.pop_back();
            up.push_back(a[i]);
        }

        if (i == a.size() - 1 || ccw(p1, a[i], p2))
        {
            while(down.size() >= 2 && !ccw(down[down.size()-2], down[down.size()-1], a[i]))
                down.pop_back();
            down.push_back(a[i]);
        }
    }

    a.clear();
    for (int i = 0; i < (int)down.size(); i++)
        a.push_back(down[i]);
    for (int i = up.size() - 2; i > 0; i--)
        a.push_back(up[i]);

    if(a.size() == 2 && a[0]==a[1])a.pop_back(); //degenerate case

    return a;
}

ld areaTriangle(point a, point b, point c) {return abs(cross(b-a, c-a)) / 2.0;}

ld areaPolygon(vector<point>& p){
    ld area = 0.0;
    for (int i = 0, n = p.size(); i < n; i++)
        area += cross(p[i], p[(i+1)%n]); // wrap back to 0 if i == n-1

    return abs(area) / 2.0;
}

// true if P at least as high as A (blue part)
bool above(point a, point p)
{return p.y >= a.y;}

// check if [PQ] crosses ray from A
bool crossesRay(point a, point p, point q)
{return (above(a,q) - above(a,p)) * orient(a,p,q) > 0;}

// if strict, returns false when A is on the boundary
bool inPolygon(vector<point>& p, point a, bool strict = true){
    int numCrossings = 0;
    for (int i = 0, n = p.size(); i < n; i++)
    {
        if (onSegment(p[i], p[(i+1)%n], a))
            return !strict;
        numCrossings += crossesRay(a, p[i], p[(i+1)%n]);
    }
    return numCrossings & 1; // inside if odd number of crossings
}

// amplitude travelled around point A, from P to Q
ld angleTravelled(point a, point p, point q){
    ld ampli = angle(p-a, q-a);
    if (orient(a,p,q) > 0)
        return ampli;
    else
        return -ampli;
}

//if windingNumber is non zero, point is in polygon, works even for non convex ones
int windingNumber(vector<point>& p, point a){
    ld ampli = 0;
    for (int i = 0, n = p.size(); i < n; i++)
        ampli += angleTravelled(a, p[i], p[(i+1)%n]);
    return round(ampli / (2*PI));
}

///Circles
point circumCenter(point a, point b, point c) { //Finds center of circle given 3 points
    b = b-a, c = c-a; // consider coordinates relative to A
    assert(cross(b,c) != 0); // no circumcircle if A,B,C aligned
    return a + perp(b*sq(c) - c*sq(b))/cross(b,c)/2;
}

int circleLine(point o, ld r, line l, pair<point,point> &out){ //Intersects circle with line
    ld h2 = r*r - l.sqDist(o);
    if (h2 >= 0)   // the line touches the circle
    {
        point p = l.proj(o); // point P
        point h = l.v*sqrt(h2)/abs(l.v); // vector parallel to l, off length h
        out = {p-h, p+h};
    }
    return 1 + sgn(h2); //sgn function is written for ints though... might write another one for doubles
}

int circleCircle(point o1, ld r1, point o2, ld r2, pair<point,point> &out){ //Intersects circle with circle
    point d=o2-o1;
    double d2=sq(d);
    if (d2 == 0)
    {
        assert(r1 != r2);    // concentric circles
        return 0;
    }
    double pd = (d2 + r1*r1 - r2*r2)/2; // = |O_1P| * d
    double h2 = r1*r1 - pd*pd/d2; // = h€2
    if (h2 >= 0)
    {
        point p = o1 + d*pd/d2, h = perp(d)*sqrt(h2/d2);
        out = {p-h, p+h};
    }
    return 1 + sgn(h2);
}

int tangents(point o1, ld r1, point o2, ld r2, bool inner, vector<pair<point,point>> &out){
    if (inner)
        r2 = -r2;
    point d = o2-o1;
    double dr = r1-r2, d2 = sq(d), h2 = d2-dr*dr;
    if (d2 == 0 || h2 < 0)
    {
        assert(h2 != 0);
        return 0;
    }
    for (double sign :{-1,1})
    {
        point v = (d*dr + perp(d)*sqrt(h2)*sign)/d2;
        out.push_back({o1 + v*r1, o2 + v*r2});
    }
    return 1 + (h2 > 0);
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n;
    cin>>n;
    vector<point>a(n);

    for(auto&p:a)
        cin>>p.x>>p.y;

    sort(a.begin(),a.end());

    point p1 = a[0], p2 = a.back();

    vector<point> up, down;
    up.push_back(p1);
    down.push_back(p1);

    for (int i = 1; i < (int)a.size(); i++)
    {
        if (i == a.size() - 1 || cw(p1, a[i], p2))
        {
            while (up.size() >= 2 && !cw(up[up.size()-2], up[up.size()-1], a[i]))
                up.pop_back();
            up.push_back(a[i]);
        }

        if (i == a.size() - 1 || ccw(p1, a[i], p2))
        {
            while(down.size() >= 2 && !ccw(down[down.size()-2], down[down.size()-1], a[i]))
                down.pop_back();
            down.push_back(a[i]);
        }
    }

    auto hull = convex_hull(a);
    ll top = hull.size()*(n-hull.size()), bot = n;

    //special cases - points we use to make line that divides up and down hull parts
    a.pop_back();
    top+=convex_hull(a).size();
    a.push_back(p2);

    swap(a[0],a.back());
    a.pop_back();
    top+=convex_hull(a).size();
    a.push_back(p1);
    swap(a[0],a.back());

    /*
    cout<<"UP: ";
    for(auto&p:up)cout<<p<<" ";
    cout<<"\n";
    cout<<"DOWN: ";
    for(auto&p:down)cout<<p<<" ";
    cout<<"\n";*/

    //up part (only considering points that have 2 neighbors)
    for(int i=1; i+1<up.size(); i++)
    {
        int from = lower_bound(a.begin(),a.end(),up[i-1]) - a.begin();
        int to = lower_bound(a.begin(),a.end(),up[i+1]) - a.begin();

        vector<point>up2 = {p1};
        if(from==0)from++;

        for(int j=from; j<=to; j++)
            if(a[j]==up[i])continue;
        else
        {
            if(j==n-1 || cw(p1, a[j], p2))
            {
                while (up2.size() >= 2 && !cw(up2[up2.size()-2], up2[up2.size()-1], a[j]))
                    up2.pop_back();
                up2.push_back(a[j]);
                if(a[j]==up[i-1])top--;
            }
        }

        /*
        cout<<up[i]<<" "<<(int)up2.size()-(i>=2 ? 3 : 2)<<" <<<\n";
        cout<<"["<<from<<", "<<to<<"]\n";
        for(auto&p:up2)cout<<p<<" ";cout<<" <<<<\n\n";
        */

        top+=hull.size()+up2.size();
        top-=3;
    }


    for(int i=1; i+1<down.size(); i++)
    {
        int from = lower_bound(a.begin(),a.end(),down[i-1]) - a.begin();
        int to = lower_bound(a.begin(),a.end(),down[i+1]) - a.begin();

        vector<point>down2 = {p1};
        if(from==0)from++;

        for(int j=from; j<=to; j++)
            if(a[j]==down[i])continue;
        else
        {
            if (j==n-1 || ccw(p1, a[j], p2))
            {
                while(down2.size() >= 2 && !ccw(down2[down2.size()-2], down2[down2.size()-1], a[j]))
                    down2.pop_back();
                down2.push_back(a[j]);
                if(a[j]==down[i-1])top--;
            }
        }

        /*
        cout<<down[i]<<" "<<(int)down2.size()-(i>=2 ? 3 : 2)<<" <<<\n";
        cout<<"["<<from<<", "<<to<<"]\n";
        for(auto&p:down2)cout<<p<<" ";cout<<" <<<<\n\n";
        */

        top+=hull.size()+down2.size();
        top-=3;
    }

    ll gcd = __gcd(top,bot);
    cout<<top/gcd<<"/"<<bot/gcd<<"\n";
}
