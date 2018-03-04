#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define oo LONG_MAX/2

void update(vector<ll>&BIT, int c, ll val)
{
    for(;c<BIT.size();c+=(c&-c))
        BIT[c]+=val;
}

ll query(vector<ll>&BIT, int c)
{
    ll sum=0;
    for(;c>0;c-=(c&-c))
        sum+=BIT[c];
    return sum;
}

ll solve(vector<vector<ll>>&DP, vector<ll>&A,vector<ll>&BIT, int L, int R)
{
    if(L>R)return 0;
    if(DP[L][R]!=-oo)return DP[L][R];
    if(L==R)return DP[L][R]=A[R];

    for(int i=L; i<=R; i++)
    {
        ll pf = query(BIT,i) - query(BIT,L-1);
        DP[L][R]=max(DP[L][R],pf - solve(DP,A,BIT,i+1,R));
    }

    for(int i=R; i>=L; i--)
    {
        ll sf = query(BIT,R) - query(BIT,i-1);
        DP[L][R]=max(DP[L][R],sf - solve(DP,A,BIT,L,i-1));
    }
    return DP[L][R];
}

int main()
{
    ios::sync_with_stdio(0);
    int n;
    while(cin>>n && n)
    {
        vector<ll>A(n+1);
        vector<ll>BIT(n+1);
        for(int i=1; i<=n; i++)cin>>A[i],update(BIT,i,A[i]);
        vector<vector<ll>>DP(n+1,vector<ll>(n+1,-oo));
        cout<<solve(DP,A,BIT,1,n)<<"\n";
    }
}
