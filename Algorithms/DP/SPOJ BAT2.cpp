#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double

int solve(vector<int>&A,vector<vector<int>>&DP, int c, int inc, int dec)
{
    if(c>=A.size())return 0;
    if(DP[inc][dec])return DP[inc][dec];
    int mx = solve(A,DP,c+1,inc,dec);
    if(inc==0 || A[inc] < A[c])mx = max(mx,1+solve(A,DP,c+1,c,dec));
    if(dec==0 || A[dec] > A[c])mx = max(mx,1+solve(A,DP,c+1,inc,c));
    return DP[inc][dec]=mx;
}

int main()
{
    ios::sync_with_stdio(0);
    int t,n;
    cin>>t;
    while(t--)
    {
        cin>>n;
        vector<int>A(n+1);
        vector<vector<int>>DP(n+1,vector<int>(n+1,0));
        for(int i=1; i<=n; i++)cin>>A[i];
        cout<<solve(A,DP,1,0,0)<<"\n";
    }
}
