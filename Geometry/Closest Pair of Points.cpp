#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

ld dist(ld x1, ld y1, ld x2, ld y2)
{
    return sqrt(pow(x1-x2,2) + pow(y1-y2,2));
}

//Finds closest pair of points in O(n log^2(n))
ld solve(vector<array<ld,2>>&A, int l, int r)
{
    if(r-l+1 == 1)return oo;
    if(r-l+1 == 2)return dist(A[l][0],A[l][1],A[r][0],A[r][1]);

    int m = (l+r)/2;
    ld le = solve(A,l,m);
    ld ri = solve(A,m+1,r);

    ld ats = min(le,ri);

    vector<array<ld,2>>strip;

    for(int i=m; i>=l; i--)
    {
        ld d = fabs(A[i][0]-A[m][0]);
        if(d > ats)break;
        strip.push_back(A[i]);
    }

    for(int i=m+1; i<=r; i++)
    {
        ld d = fabs(A[i][0]-A[m][0]);
        if(d > ats)break;
        strip.push_back(A[i]);
    }

    stable_sort(strip.begin(),strip.end(),[](array<ld,2>a, array<ld,2>b)
                {
                    return a[1] < b[1];
                });

    for(int i=0; i<strip.size(); i++)
        for(int j=i+1; j<strip.size() && fabs(strip[i][1]-strip[j][1]) < ats; j++)
        ats=min(ats,dist(strip[i][0],strip[i][1],strip[j][0],strip[j][1]));

    return ats;
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    int n;
    while(cin>>n && n)
    {
        vector<array<ld,2>>A(n);
        for(auto&p:A)
            cin>>p[0]>>p[1];

        sort(A.begin(),A.end());
        ld ats = solve(A,0,n-1);
        if(ats >= 10000)cout<<"INFINITY\n";
        else cout<<setprecision(4)<<fixed<<ats<<"\n";
    }
}
