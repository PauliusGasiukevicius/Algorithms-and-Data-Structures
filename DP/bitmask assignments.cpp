#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

/*
our task will be to calculate number of different assignments of n different topics
to n students such that everybody gets exactly one topic he likes.
*/

int A[21][21]; //like matrix
ll DP[21][(1<<20)];
int n;

ll solve(int i, ll mask)
{
    if(i>=n)return 1;
    if(DP[i][mask] != -1)return DP[i][mask];

    DP[i][mask]=0;
    for(int j=0; j<n; j++)
        if(A[i][j] && (mask & (1<<j))==0) //if topic is not assigned and student likes it
            DP[i][mask]+=solve(i+1,mask|(1<<j));

    return DP[i][mask];
}

int main()
{
    ios::sync_with_stdio(0);
    int t;
    cin>>t;
    while(t--)
    {
        cin>>n;

        for(int i=0; i<n; i++)
            for(int j=0; j<n; j++)
            cin>>A[i][j];

        for(int i=0; i<n; i++)
            for(int j=0; j<(1<<n); j++)
            DP[i][j]=-1;

        cout<<solve(0,0LL)<<"\n";
    }
}
