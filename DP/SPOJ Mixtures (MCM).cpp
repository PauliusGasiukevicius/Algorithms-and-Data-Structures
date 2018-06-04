#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

int solve(vector<vector<int>>&DP, vector<vector<int>>&col, vector<int>&A, int l, int r)
{
    if(l>r)return 0;
    if(l==r)
    {
        col[l][r]=A[r];
        return 0;
    }
    if(l+1==r)
    {
        col[l][r] = (A[l]+A[r])%100;
        return A[l]*A[r];
    }
    if(DP[l][r]!=oo)return DP[l][r];

    for(int i=l+1; i<=r; i++)
    {
        int L = solve(DP,col,A,l,i-1);
        int R = solve(DP,col,A,i,r);
        if(L+R+col[l][i-1]*col[i][r] < DP[l][r])
        {
        DP[l][r]=L+R+col[l][i-1]*col[i][r];
        col[l][r]=(col[l][i-1] + col[i][r])%100;
        }
    }
    return DP[l][r];
}

int main()
{
    ios::sync_with_stdio(0);
    int n;
    while(cin>>n)
    {
        vector<int>A(n);
        for(int&x:A)cin>>x;
        vector<vector<int>>DP(n,vector<int>(n,oo));
        vector<vector<int>>col(n,vector<int>(n,oo));
        cout<<solve(DP,col,A,0,n-1)<<"\n";
    }
}
