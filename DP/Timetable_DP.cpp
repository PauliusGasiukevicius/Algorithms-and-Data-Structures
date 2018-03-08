#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define oo INT_MAX/10

int main()
{
    ios::sync_with_stdio(0);
    int n,m,k;
    cin>>n>>m>>k;
    vector<vector<int>>MN(n+1,vector<int>(501,oo)); // min amount of hours to spend in univ skipping j lessons on day i
    vector<vector<int>>DP(n+1,vector<int>(501,oo));
    MN[0][0]=DP[0][0]=0;

    for(int i=1; i<=n; i++)
    {
        vector<char>D(m+1);
        for(int j=1; j<=m; j++)
            cin>>D[j];

        vector<int>P(m+1,0);    // prefix on day i
        for(int j=1; j<=m; j++)
            P[j]=P[j-1]+(D[j]=='1');

        for(int from = 1; from<=m; from++)
            for(int to=from; to<=m; to++)   //select interval of hours [from,to] to attend
        {
            int skip = P[from-1] + P[m] - P[to]; // amount of lessons that needs to be skipped
            MN[i][skip]=min(MN[i][skip],to-from+1);
        }

        MN[i][P[m]]=0;

            for(int j = 0; j<=k; j++) //total lessons skipped
                for(int last = 0; last<=j; last++) // lessons skipped on day i-1
                DP[i][j]=min(DP[i][j],DP[i-1][last] + MN[i][j-last]);
    }

    int ats = oo;

    for(int j=0; j<=k; j++)
        ats=min(ats,DP[n][j]);

    cout<<ats<<"\n";
}
