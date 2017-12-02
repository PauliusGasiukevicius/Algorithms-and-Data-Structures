#include <bits/stdc++.h>
using namespace std;
 
int main()
{
    ios::sync_with_stdio(0);
    int n,m;
    cin>>n>>m;
    int DP[101][101]={}; //row prefixes
 
    for(int i=1; i<=n; i++)
    for(int j=1; j<=m; j++)
    {
        cin>>DP[i][j];
        DP[i][j] += DP[i][j-1];
    }
 
    int ats = -100;
 
    //Kadane`s algorithm to get O(n^3)
    for(int j=1; j<=m; j++)
        for(int j2=j; j2<=m; j2++)
            {
                int sum = 0;
                for(int i=1; i<=n; i++)
                {
                    sum+=DP[i][j2] - DP[i][j-1];
                    ats = max(ats,sum);
                    if(sum < 0)
                    sum=0;
                }
            }
 
    cout<<ats<<"\n";
}
