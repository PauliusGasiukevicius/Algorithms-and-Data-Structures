#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 1234567890
#define MOD 1000000007

//to fill dp we consider upper and lower part of tour and try extending them to rightmost point
ld dp[1001][1001];
int can[1001][1001];
ld d[1001][1001]; //euclidean distance

ld solve(int p1, int p2, int n)
{
    int p = max(p1,p2) + 1; //next point to consider adding to some path
    if(p==n-1)return d[p1][p] + d[p2][p]; //final point so connect to both paths
    if(can[p1][p2])return dp[p1][p2];
    can[p1][p2]=1;
    return dp[p1][p2] = min(d[p1][p] + solve(p,p2,n), d[p2][p] + solve(p1,p,n));
}

ld bitonicTSP(vector<array<ld,2>>&p)
{
    memset(can,0,sizeof can);
    sort(p.begin(),p.end());

    for(int i=0; i<p.size(); i++)
    for(int j=i; j<p.size(); j++)
    d[i][j]=d[j][i]=sqrt(pow(p[i][0]-p[j][0],2) + pow(p[i][1]-p[j][1],2));

    return solve(0,0,p.size());
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n;
    while(cin>>n)
    {
        vector<array<ld,2>>P(n);
        for(auto&p:P)
            cin>>p[0]>>p[1];

        cout<<setprecision(2)<<fixed<<bitonicTSP(P)<<"\n";
    }
}
