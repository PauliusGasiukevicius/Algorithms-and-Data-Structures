//binary sequences with exacly n1 ones and n2 zeroes, with no more than k1 succesive ones and k2 zeroes
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define oo INT_MAX/10

int DP[201][201][11][11];
int M = 1e8;

int solve(int n1, int n2, int k1, int k2, int& limit1, int& limit2)
{
    if(DP[n1][n2][k1][k2]!=-1)return DP[n1][n2][k1][k2];
    if(n1==0 && n2==0)return 1;

    int ats = 0;
    if(n1 > 0 && k1+1<=limit1)ats = (ats + solve(n1-1,n2,k1+1,0,limit1,limit2))%M;
    if(n2 > 0 && k2+1<=limit2)ats = (ats + solve(n1,n2-1,0,k2+1,limit1,limit2))%M;
    return DP[n1][n2][k1][k2]=ats%M;
}

int main()
{
    ios::sync_with_stdio(0);
    int n1,n2,k1,k2;
    cin>>n1>>n2>>k1>>k2;

    for(int i=0; i<=n1; i++)
        for(int j=0; j<=n2; j++)
            for(int k=0; k<=k1; k++)
                for(int y=0; y<=k2; y++)
                DP[i][j][k][y]=-1;

    cout<<solve(n1,n2,0,0,k1,k2)<<"\n";
}
