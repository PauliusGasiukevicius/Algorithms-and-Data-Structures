#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

ld solve(vector<pair<int,ld>>&A, vector<ld>&DP, ll d = 0)
{
    if(d>=DP.size())return 0;
    if(DP[d] >= 0.0)return DP[d];

    ld ats = 0;
    for(int i=0; i<A.size(); i++)
        if(A[i].first < 0)
            ats+=A[i].second*(-A[i].first+solve(A,DP,d+1));
        else ats+=A[i].first*A[i].second;
    return DP[d]=ats;
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    int t,n,cs=1;
    cin>>t;
    while(t--)
    {
        cout<<"Case "<<cs++<<": ";
        cin>>n;
        vector<pair<int,ld>>A(n);
        vector<ld>DP(501,-1.0);
        for(int i=0; i<n; i++)
        cin>>A[i].first>>A[i].second;

        sort(A.begin(),A.end());
        if(A.back().first < 0)cout<<"God! Save me\n";
        else cout<<setprecision(2)<<fixed<<solve(A,DP)<<"\n";
    }
}
