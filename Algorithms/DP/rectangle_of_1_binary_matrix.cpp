#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

int H[1005][1005];//max free cells up
int L[1005][1005];//max extension left, having height H[r][c]
int R[1005][1005];//max extension right, having height H[r][c]
char A[1005][1005];

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n,m;
    cin>>n>>m;

    for(int i=0; i<=n+1; i++)
        for(int j=0; j<=m+1; j++)
        A[i][j]='*';

    for(int i=1; i<=n; i++)
        for(int j=1; j<=m; j++)
        {
            cin>>A[i][j];
            H[i][j]=(i==1 ? (A[i][j]=='.') : (A[i][j]=='*' ? 0 : H[i-1][j]+1));
        }

    for(int i=1; i<=n; i++)
    {
        int prev=0; //previous tree
        for(int j=1; j<=m; j++)
        {
            L[i][j] = (A[i-1][j]=='*' ? j-prev : min(j-prev, L[i-1][j]));
            if(A[i][j]=='*')prev=j;
        }

        prev = m+1;
        for(int j=m; j>=1; j--)
        {
            R[i][j] = (A[i-1][j]=='*' ? prev-j : min(prev-j, R[i-1][j]));
            if(A[i][j]=='*')prev=j;
        }
    }

    int ats = 0;

    for(int i=1; i<=n; i++)
        for(int j=1; j<=m; j++)
        ats=max(ats,H[i][j]*(R[i][j]+L[i][j]-1));

    cout<<ats;
}
