#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

ll solve(vector<vector<ll>>&DP, vector<int>&O, int pos, int deg, int n)
{
    if(deg < 0)return 0;
    if(pos>2*n)return (deg ? 0 : 1);
    if(DP[pos][deg] > -1)return DP[pos][deg];
    DP[pos][deg]=0;

    if(O[pos])//forced bracket
        return DP[pos][deg] = solve(DP,O,pos+1,deg+1,n);
    else
      return DP[pos][deg] = solve(DP,O,pos+1,deg+1,n) + solve(DP,O,pos+1,deg-1,n);
}

int main()
{
    ios::sync_with_stdio(0);
    int t,n,k;
    cin>>t;

    while(t--)
    {
        cin>>n>>k;
        vector<vector<ll>>DP(2*n+1,vector<ll>(2*n+1,-1));
        vector<int>O(2*n+1); //forced '[' brackets
        for(int i=0,x; i<k; i++)
            cin>>x,O[x]=1;

        cout<< solve(DP,O,1,0,n) <<"\n";
    }
}
