#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define oo LONG_MAX/2

ll solve(vector<vector<ll>>&DP, vector<ll>&A, int L, int R)
{
    if(L>R)return 0;
    if(DP[L][R]!=-oo)return DP[L][R];
    if(L==R)return DP[L][R]=A[R];

    for(int i=L; i<=R; i++)
    {
        ll pf = 0;
        for(int k=L; k<=i; k++)pf+=A[k];

        DP[L][R]=max(DP[L][R],pf - solve(DP,A,i+1,R));
    }

    for(int i=R; i>=L; i--)
    {
        ll sf = 0;
        for(int k=i; k<=R; k++)sf+=A[k];

        DP[L][R]=max(DP[L][R],sf - solve(DP,A,L,i-1));
    }
    return DP[L][R];
}

int main()
{
    ios::sync_with_stdio(0);
    int n;
    while(cin>>n && n)
    {
        vector<ll>A(n);
        for(ll&x:A)cin>>x;
        vector<vector<ll>>DP(n,vector<ll>(n,-oo));
        cout<<solve(DP,A,0,n-1)<<"\n";
    }
}
