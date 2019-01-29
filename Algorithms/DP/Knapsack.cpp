#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main()
{
    ios::sync_with_stdio(0);
    int W,n;

    while(cin>>W>>n && n)
    {
        int w[505],c[505];
        for(int i=1; i<=n; i++)
            cin>>w[i]>>c[i];

        int DP[505][505]={};

        for(int i=1; i<=n; i++)
            for(int j=0; j<=W; j++)
                if(j < w[i])DP[i][j]=DP[i-1][j];
                else DP[i][j]=max(DP[i-1][j],c[i]+DP[i-1][j-w[i]]);

        int optC = 0, optW=0;

        for(int j=0;j<=W; j++)
        if(DP[n][j] > optC)optC=DP[n][j],optW=j;

        cout<<optW<<" "<<optC<<"\n";
    }
}
