#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

int main()
{
    ios::sync_with_stdio(0);
    int t,n,k;
    cin>>t;

    while(t--)
    {
        //Number of permutations of 1...N numbers having exacly k inversions
        cin>>n>>k;
        int DP[13][303]={};
        DP[1][0]=1;

        for(int i=2; i<=n; i++)
        for(int k=0; k<156; k++)
        for(int j=0; j<i; j++)
            DP[i][j+k]+=DP[i-1][k];

        cout<<DP[n][k] << "\n";
    }
}
