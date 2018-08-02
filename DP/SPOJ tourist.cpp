#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld double

char A[102][102];
int DP[102][102][102];
int n,m;

int solve(int r, int c, int rr)
{
    if(DP[r][c][rr]!=-1)return DP[r][c][rr];
    int cc = r+c-rr;
    if(r==n && c==m)return A[n][m]=='*';
    int v = 0;
    v+=A[r][c]=='*';
    v+=A[rr][cc]=='*';
    if(r==rr && c==cc)
    v-=A[r][c]=='*';

    int ats = v;

    if(r+1<=n && rr+1<=n && A[r+1][c]!='#' && A[rr+1][cc]!='#')ats=max(ats,v+solve(r+1,c,rr+1));
    if(c+1<=m && rr+1<=n && A[r][c+1]!='#' && A[rr+1][cc]!='#')ats=max(ats,v+solve(r,c+1,rr+1));
    if(r+1<=n && cc+1<=m && A[r+1][c]!='#' && A[rr][cc+1]!='#')ats=max(ats,v+solve(r+1,c,rr));
    if(c+1<=m && cc+1<=m && A[r][c+1]!='#' && A[rr][cc+1]!='#')ats=max(ats,v+solve(r,c+1,rr));
    return DP[r][c][rr] = ats;
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    int t;
    cin>>t;
    while(t--)
    {
        cin>>m>>n;
        for(int i=1; i<=n; i++)
            for(int j=1; j<=m; j++)
            cin>>A[i][j];

        for(int i=1; i<=n; i++)
            for(int j=1; j<=m; j++)
                for(int ii=1; ii<=n; ii++)
                    DP[i][j][ii]=-1;

        cout<<solve(1,1,1)<<"\n";
    }
}
