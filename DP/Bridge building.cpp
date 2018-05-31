#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

void flood(vector<string>&A, int r, int c, char color)
{
    if(r<0 || c<0 || r>=A.size() || c>=A[r].size() || A[r][c]!='#')return;
    A[r][c]=color;
    flood(A,r+1,c,color);
    flood(A,r-1,c,color);
    flood(A,r,c+1,color);
    flood(A,r,c-1,color);
}

int main()
{
    ios::sync_with_stdio(0);
    int n,m,b,s;
    while(cin>>n>>m>>b>>s)
    {
        vector<string>A(n);
        for(auto&s:A)cin>>s;
        flood(A,0,0,'1');
        flood(A,n-1,m-1,'2');
        vector<int>D(m+1);//distance between banks

        for(int j=0; j<m; j++)
        {
            int lo = 0, hi = n-1;
            for(int i=0; i<n; i++)
                if(A[i][j]=='1')lo=max(lo,i);
            else if(A[i][j]=='2')hi=min(hi,i);
            D[j+1]=hi-lo-1;//1 indexing for sanity :)
        }

        //DP[k][j] -> min amount to pay to take k items 
        // s steps apart, when last one was before j
        s++;
        vector<vector<int>>DP(b+1,vector<int>(m+1,oo));
        for(int j=1; j<=m; j++)
            DP[1][j]=min(DP[1][j-1],D[j]);

        for(int k=2; k<=b; k++)
        for(int j=s; j<=m; j++)
        DP[k][j]=min(DP[k][j-1],DP[k-1][j-s] + D[j]);

        cout<<DP[b][m]<<"\n";
    }
}
