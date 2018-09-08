// SPOJ HIST2
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 1000000000

int A[16];
int DP[16][1<<16];
int cnt[16][1<<16];
int n;

int solve(int c, int mask)
{
    if(DP[c][mask]!=-1)return DP[c][mask];
    int res = 0;
    int ways = 1;

    for(int i=0; i<n; i++)
        if((mask & (1<<i))==0)
    {
        int nmask = mask | (1<<i);

        if(nmask==(1<<n)-1) //last one
        {
            int val = abs(A[i]-A[c]) + 2 + A[i];
            if(val > res)res=val,ways=1;
            else if(val==res)ways++;
        }
        else
        {
            int val = abs(A[i]-A[c]) + 2 + solve(i,nmask);
            if(val > res)res=val,ways=cnt[i][nmask];
            else if(val==res)ways+=cnt[i][nmask];
        }
    }

    cnt[c][mask]=ways;
    return DP[c][mask]=res;
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    while(cin>>n && n>0)
    {
        for(int i=0; i<n; i++)
            cin>>A[i];

        for(int i=0; i<n; i++)
            for(int j=0; j<(1<<n); j++)
            DP[i][j]=-1;

        int res = 0, ways = 0;
        for(int i=0; i<n; i++)
        {
            int val = solve(i,(1<<i)) + A[i] + 2;
            if(val > res)res=val,ways=cnt[i][(1<<i)];
            else if(val==res)ways+=cnt[i][(1<<i)];
        }

        cout<<res<<" "<<ways<<"\n";
    }
}
