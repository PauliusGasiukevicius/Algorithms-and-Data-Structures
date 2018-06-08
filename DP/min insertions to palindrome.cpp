#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld  double
#define oo 666666666

int solve(map<pair<int,pair<int,int>>,int>&DP, vector<int>&A, int l, int r, int k)
{
    if(l>=r)return 0;
    if(DP.count(make_pair(l,make_pair(r,k))))return DP[make_pair(l,make_pair(r,k))];
    if(k<0)return oo;

    int ats = oo;
    if(A[l]==A[r])ats=solve(DP,A,l+1,r-1,k);
    else ats=min(solve(DP,A,l+1,r,k-1),solve(DP,A,l,r-1,k-1))+1;
    return DP[make_pair(l,make_pair(r,k))]=ats;
}

int main()
{
    ios::sync_with_stdio(0);
    int t,n,k,cs=1;
    cin>>t;
    while(t--)
    {
        cin>>n>>k;
        vector<int>A(n);
        for(int&x:A)cin>>x;
        map<pair<int,pair<int,int>>,int>mp;
        int ats = solve(mp,A,0,n-1,k);

        if(ats>0 && ats <= oo)
        cout<<"Case "<<cs++<<": "<<solve(mp,A,0,n-1,k)<<"\n";
        else if(ats==0)
            cout<<"Case "<<cs++<<": Too easy\n";
        else
            cout<<"Case "<<cs++<<": Too difficult\n";
    }
}
