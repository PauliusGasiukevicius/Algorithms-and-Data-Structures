#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo INT_MAX/2

int k,n,m;
int DP[1011][1011];
int len[1011][1011];
string a,b;

int main()
{
    ios::sync_with_stdio(0);
    while(cin>>k && k)
    {
        cin>>a>>b;
        a="?"+a;
        b="?"+b;
        if(a>b)swap(a,b);
        n=a.size();
        m=b.size();

        for(int i=0; i<=n; i++)
            for(int j=0; j<=n; j++)
            DP[i][j]=len[i][j]=0;

        //Finding LCS of 2 strings where all matched substrings are at least of length k

        for(int i=1; i<n; i++)
            for(int j=1; j<m; j++)
        {
            DP[i][j]=max(DP[i-1][j],DP[i][j-1]);

            if(a[i]==b[j])len[i][j]=len[i-1][j-1]+1;
            else len[i][j]=0;

            for(int z=k; z<=len[i][j]; z++)
                DP[i][j]=max(DP[i][j],DP[i-z][j-z] + z);
        }

        cout<<DP[n-1][m-1]<<"\n";
    }
}
