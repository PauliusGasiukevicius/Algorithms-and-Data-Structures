#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

//Finds min cost to multiply matrix chain + last[][] memo for solution construction
ll solve(vector<vector<ll>>&DP, vector<vector<ll>>&last, int l, int r, vector<int>&R,vector<int>&C)
{
    if(l>=r)return 0;
    if(l+1==r)
    {
        last[l][r]=l;
        return DP[l][r]=R[l]*C[l]*C[r];
    }
    if(DP[l][r]!=-1)return DP[l][r];

    DP[l][r]=oo;
    for(int k=l; k<r; k++) //choose last multiply operation
    {
        ll cost = solve(DP,last,l,k,R,C) + solve(DP,last,k+1,r,R,C);//recursively solve subproblems
        cost += R[l]*R[k+1]*C[r];//final multiply
        if(cost < DP[l][r])
            DP[l][r]=cost,last[l][r]=k;
        //cout<<k<<" "<<cost<<"\n";
    }
    return DP[l][r];
}

string construct(vector<vector<ll>>&last, int l, int r)
{
    if(l==r)
        return "A"+to_string(l+1);

    string s = "(";
    int k = last[l][r];
    s+=construct(last,l,k);
    s+=" x ";
    s+=construct(last,k+1,r);
    s+=")";
    return s;
}

int main()
{
    ios::sync_with_stdio(0);
    int cs=1,n;
    while(cin>>n && n)
    {
        vector<int>R(n),C(n);
        for(int i=0; i<n; i++)
            cin>>R[i]>>C[i];

        vector<vector<ll>>DP(n,vector<ll>(n,-1));
        vector<vector<ll>>last(n,vector<ll>(n,-1));
        solve(DP,last,0,n-1,R,C);
        //cout<<*/solve(DP,last,0,n-1,R,C)<<"\n";
        cout<<"Case "<<cs++<<": "<<construct(last,0,n-1)<<"\n";
    }
}
