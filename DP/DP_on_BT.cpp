#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double

int read(vector<int>&A, int c, int lim)
{
    cin>>A[c];
    if(2*c < lim)read(A,2*c,lim);
    if(2*c+1 < lim)read(A,2*c+1,lim);
}

int solve(vector<int>&A, vector<vector<int>>&DP, int c, int lim, int k)
{
    if(k<1)return 0;
    if(2*c >= lim)return A[c];
    if(DP[c][k]!=-666666666)return DP[c][k];

    DP[c][k] = A[c];

    for(int j=1; j<k; j++)
    DP[c][k]=max(DP[c][k],solve(A,DP,2*c,lim,j)+solve(A,DP,2*c+1,lim,k-j));

    return DP[c][k];
}

int main()
{
    ios::sync_with_stdio(0);
    int n,k;
    while(cin>>n && n!=-1)
    {
        n++;
        cin>>k;
        vector<int>A((1<<n));
        vector<vector<int>>DP((1<<n),vector<int>(21,-666666666));
        read(A,1,(1<<n));
        cout<<solve(A,DP,1,(1<<n),k)<<"\n";
    }
}
