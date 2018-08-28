#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666
int DP[12][12][12][32];

int solve(int l1, int l2, int l3, int d)
{
    if(DP[l1][l2][l3][d]!=-1)return DP[l1][l2][l3][d];
    if(l1+l2+l3 < d)return 0;
    if(l1==0 && l2==0 && l3==0)return d==0;
    int ats = 0;

    for(int i1=0; i1<=l1; i1++)
    for(int i2=0; i2<=l2; i2++)
    for(int i3=0; i3<=l3; i3++)
        if(i1+i2+i3)
    {
        //so we split a problem into subproblems, like split in 2 parts: p1|p2
        //or remove some bracket and solve for other part
        for(int d1 = 1; d1<d; d1++)//depth of left part
            if(i1+i2+i3>=d1)
        {
            //left part has depth < d so right one must have depth of d
            if(i1)ats+=solve(i1-1,i2,i3,d1-1)*solve(l1-i1,l2-i2,l3-i3,d);
            else if(i2)ats+=solve(i1,i2-1,i3,d1-1)*solve(l1-i1,l2-i2,l3-i3,d);
            else ats+=solve(i1,i2,i3-1,d1-1)*solve(l1-i1,l2-i2,l3-i3,d);
            ats%=11380;
        }

        for(int d1 = 0; d1<=d; d1++)//depth of right part
            if(i1+i2+i3>=d1)
        {
            //left part has depth == d so right one can have any depth
            if(i1)ats+=solve(i1-1,i2,i3,d-1)*solve(l1-i1,l2-i2,l3-i3,d1);
            else if(i2)ats+=solve(i1,i2-1,i3,d-1)*solve(l1-i1,l2-i2,l3-i3,d1);
            else ats+=solve(i1,i2,i3-1,d-1)*solve(l1-i1,l2-i2,l3-i3,d1);
            ats%=11380;
        }
    }
    return DP[l1][l2][l3][d]=ats%11380;
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    int tc = 10;
    int l1,l2,l3,d;
    while( tc-- > 0 && cin>>l1>>l2>>l3>>d)
    {
        memset(DP, -1, sizeof DP);
        cout<<solve(l1,l2,l3,d)<<"\n";
    }
}
