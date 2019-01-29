#include <bits/stdc++.h>
using namespace std;
#define oo 666666666

pair<int,int> R(pair<int,int>O, pair<int,int>P, int deg)
{
    P.first-=O.first;
    P.second-=O.second;
    //int x = round(P.first*cos(D)-sin(D)*P.second);
    //int y = round(P.first*sin(D)+cos(D)*P.second);

    while(deg!=0)
    {
        int x = -P.second;
        int y = P.first;
        P.first=x;
        P.second=y;
        deg+=90;
    }

    P.first+=O.first;
    P.second+=O.second;
    return P;
}

int distSquared(pair<int,int>p1, pair<int,int>p2)
{
    return (p1.first-p2.first)*(p1.first-p2.first) + (p1.second-p2.second)*(p1.second-p2.second);
}

bool isSquare(pair<int,int>p1, pair<int,int>p2,pair<int,int>p3,pair<int,int>p4)
{
    if(p1==p2 || p1==p3 || p1==p4 || p2==p3 || p2==p4 || p3==p4)return 0;
    int d1 = distSquared(p1,p2);
    int d2 = distSquared(p1,p3);
    int d3 = distSquared(p1,p4);
if(d1==d2 && d1*2==d3 && distSquared(p2,p4)==d1 && distSquared(p3,p4)==d1)return 1;
if(d1==d3 && d1*2==d2 && distSquared(p3,p4)==d1 && distSquared(p3,p2)==d1)return 1;
if(d2==d3 && d2*2==d1 && distSquared(p2,p4)==d2 && distSquared(p2,p3)==d2)return 1;
    return 0;
}

int main()
{
    ios::sync_with_stdio(0);
    int n;
    cin>>n;

    while(n--)
    {
        vector<vector<int>>A(4,vector<int>(4));
        for(int i=0; i<4; i++)
            for(int j=0; j<4; j++)
            cin>>A[i][j];

        int ats = 666;

        for(int r1=0; r1<4; r1++)
        for(int r2=0; r2<4; r2++)
        for(int r3=0; r3<4; r3++)
        for(int r4=0; r4<4; r4++)
        {
            auto p1 = R({A[0][2],A[0][3]},{A[0][0],A[0][1]},-90*r1);
            auto p2 = R({A[1][2],A[1][3]},{A[1][0],A[1][1]},-90*r2);
            auto p3 = R({A[2][2],A[2][3]},{A[2][0],A[2][1]},-90*r3);
            auto p4 =R({A[3][2],A[3][3]},{A[3][0],A[3][1]},-90*r4);

            if(isSquare(p1,p2,p3,p4))
                ats=min(ats,r1+r2+r3+r4);
        }

        if(ats==666)ats=-1;
        cout<<ats<<"\n";
    }
}
