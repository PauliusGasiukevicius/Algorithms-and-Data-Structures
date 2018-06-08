#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld  double
#define oo 666666666

/*
How many ways can one score out a few symbols
(maybe 0) that the rest of sequence become a palidrome.
Varints that are only different by an order of
scoring out should be considered the same
*/

ll solve(vector<vector<ll>>&DP, string&s, int l, int r)
{
    if(l==r)return 1;
    if(l>r)return 0;
    if(DP[l][r]!=-1)return DP[l][r];

    if(s[l]==s[r])
    DP[l][r]= solve(DP,s,l,r-1) + solve(DP,s,l+1,r) + 1;
    else DP[l][r] = solve(DP,s,l,r-1) + solve(DP,s,l+1,r) - solve(DP,s,l+1,r-1);

    return DP[l][r];
}

int main()
{
    ios::sync_with_stdio(0);
    int t;
    string s,r;
    cin>>t;

    while(t--)
    {
        cin>>s;
        vector<vector<ll>>DP(s.size(),vector<ll>(s.size(),-1));
        cout<<solve(DP,s,0,s.size()-1)<<"\n";
    }
}
