#include <bits/stdc++.h>
using namespace std;
#define oo 666666666
#define ll long long
#define ld long double

ld cross(ld x1, ld y1, ld x2, ld y2)
{return x1*y2-x2*y1;}

ld polygonArea(vector<pair<ll,ll>>&A)
{
    ld ats = 0.0;
    for(int i=2; i<A.size(); i++)
        ats+=cross(A[i].first-A[0].first,A[i].second-A[0].second,A[i-1].first-A[0].first,A[i-1].second-A[0].second);
    return fabs(ats/2);
}

ll boundary(vector<pair<ll,ll>>&A)
{
    ll ats = A.size();
    for(int i=0; i<A.size(); i++)
    {
        ll dx = (A[i].first - A[(i+1)%A.size()].first);
        ll dy = (A[i].second - A[(i+1)%A.size()].second);
        ats+=abs(__gcd(dx,dy)) - 1;
    }
    return ats;
}

ll Pick(vector<pair<ll,ll>>&A)
{
    //S - area, B - boundary  integer points, I - points inside
    //Theorem: S = B/2 + I - 1
    //I = S+1-B/2;
    ll S = polygonArea(A);
    ll B = boundary(A);
    ll I = S+1-B/2;
    return I + B;
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    ll n;
    cin>>n;

    vector<pair<ll,ll>>A11,A12,A21,A22;
    for(int i=0; i<n; i++)
    {
        ll x,y;
        cin>>x>>y;
        A11.push_back({x,y});
        A12.push_back({x,y*2});
        A21.push_back({x*2,y});
        A22.push_back({x*2,y*2});
    }
    ll ats = Pick(A22) - Pick(A12) - Pick(A21) + Pick(A11);

    cout<<ats;
}
