#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main()
{
    ios::sync_with_stdio(0);
    int t,n,m;
    string a,b;
    cin>>t;
    while(t--)
    {
        cin>>a>>b;
        n=a.size();
        m=b.size();
        vector<vector<int>>DP(n+1,vector<int>(m+1,666666666));

        for(int i=0; i<=n; i++)
            DP[i][0]=i;
        for(int j=0; j<=m; j++)
            DP[0][j]=j;

        for(int i=1; i<=n; i++)
            for(int j=1; j<=m; j++)
            if(a[i-1]==b[j-1])DP[i][j]=DP[i-1][j-1];
            else DP[i][j]=min({DP[i-1][j-1]+1, DP[i-1][j]+1, DP[i][j-1]+1});

        cout<<DP[n][m]<<"\n";
    }
}
