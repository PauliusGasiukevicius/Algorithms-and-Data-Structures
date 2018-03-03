#include <bits/stdc++.h>
using namespace std;
#define ll long long

void solve(vector<int>&S, int n, int last,vector<vector<int>>&ats)
{
    if(n==1)
    {
        if(S.size() > 1)
        ats.push_back(S);
        return;
    }

    for(int i=last; i*i <=n; i++)
        if(n%i==0)
    {
        S.push_back(i);
        solve(S,n/i,i,ats);
        S.pop_back();
    }

    S.push_back(n);
    solve(S,1,n,ats);
    S.pop_back();
}

int main()
{
    ios::sync_with_stdio(0);
    int n;

    while(cin>>n && n)
    {
        vector<int>S;
        vector<vector<int>>ats;
        solve(S,n,2,ats);

        cout<<ats.size()<<"\n";
        for(auto&v:ats)
            for(int i=0; i<v.size(); i++)
            cout<<v[i]<<(i+1==v.size()?"\n":" ");
    }
}
