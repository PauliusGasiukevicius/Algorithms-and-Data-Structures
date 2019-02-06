#include <bits/stdc++.h>
using namespace std;
#define oo 666666666
#define ll long long
#define ld long double

int N,S;
ld EX[1001][1001];
int solved[1001][1001];

ld solve(int n, int s)
{
    if(n==N && s==S)return 0;
    if(solved[n][s])return EX[n][s];

    ld ats = 1.0;

    if(n < N && s < S)ats+=1.0*(N-n)/N * 1.0*(S-s)/S * solve(n+1,s+1); //new bug in new component
    if(n < N)ats+=1.0*(N-n)/N * 1.0*(s)/S * solve(n+1,s); //new bug in old component
    if(s < S)ats+=1.0*(n)/N * 1.0*(S-s)/S * solve(n,s+1); //old bug in new component

    /*
        let p1 - probability of new bug in new component
        let p2 - probability of new bug in old component
        let p3 - probability of old bug in new component
        let p4 - probability of old bug in old component
        so then
        EX[n][s] = p1*EX[n+1][s+1] + p2*EX[n+1][s] + p3*EX[n][s+1] + p4*EX[n][s]
        EX[n][s] - p4*EX[n][s] = p1*EX[n+1][s+1] + p2*EX[n+1][s] + p3*EX[n][s+1]
        (1-p4)*EX[n][s] = p1*EX[n+1][s+1] + p2*EX[n+1][s] + p3*EX[n][s+1]
        EX[n][s] = (p1*EX[n+1][s+1] + p2*EX[n+1][s] + p3*EX[n][s+1]) / (1-p4)
    */

    ld p4 = 1.0*n*s/N/S;
    ats/=(1.0-p4);
    solved[n][s]=1;
    return EX[n][s]=ats;
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin>>N>>S;
    cout<<setprecision(4)<<fixed<<solve(0,0);
}
