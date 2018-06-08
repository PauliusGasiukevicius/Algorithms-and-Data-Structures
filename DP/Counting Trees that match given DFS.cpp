#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld  double
#define oo 666666666

ll solve(vector<vector<ll>>&DP, string&s, int l, int r)
{
    if(l==r)return 1;
    if(s[l]!=s[r])return 0;
    if(DP[l][r]!=-1)return DP[l][r];
    DP[l][r]=0;

    for(int k=l+2; k<=r; k++)
        if(s[l]==s[k])//if color matches, means there is a possibility we came to same node
        DP[l][r] = (DP[l][r] + solve(DP,s,l+1,k-1)*solve(DP,s,k,r))%1000000000LL;
    return DP[l][r];
}

int main()
{
    ios::sync_with_stdio(0);
    string s;
    while(cin>>s)
    {
        vector<vector<ll>>DP(s.size(),vector<ll>(s.size(),-1));
        cout<<solve(DP,s,0,s.size()-1)<<"\n";
    }
}
