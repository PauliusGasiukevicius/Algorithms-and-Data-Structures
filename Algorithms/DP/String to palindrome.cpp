#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

int solve(vector<vector<int>>&DP, string&s, int l, int r)
{
    if(r-l+1 < 2)return 0;
    if(DP[l][r]>-1)return DP[l][r];
    DP[l][r]=oo;

    if(s[l]==s[r])return DP[l][r] = solve(DP,s,l+1,r-1);
    return DP[l][r] = 1 + min({solve(DP,s,l+1,r), solve(DP,s,l,r-1), solve(DP,s,l+1,r-1)});
}

int main()
{
    ios::sync_with_stdio(0);
    int t,cs=1;
    string s;
    cin>>t;

    while(t--)
    {
        cin>>s;
        vector<vector<int>>DP(s.size(),vector<int>(s.size(),-1));

        int ats = solve(DP,s,0,s.size()-1);
        cout<<"Case "<<cs++<<": "<<ats<<"\n";
    }
}
