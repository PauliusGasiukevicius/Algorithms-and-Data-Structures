#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define oo INT_MAX/10

void update(vector<ll>&BIT,int c, int val)
{
    for(;c<BIT.size();c+=(c&-c))
            BIT[c]+=val;
}

ll query(vector<ll>&BIT,int c)
{
    ll ats = 0;
    for(;c>0;c-=(c&-c))
        ats+=BIT[c];

    return ats;
}

int main()
{
    ios::sync_with_stdio(0);
    int n;
    cin>>n;
    vector<vector<int>>A(n,vector<int>(2));
    vector<ll>L(n+1);
    vector<ll>G(n+1);
    for(int i=0; i<n; i++)
        cin>>A[i][0],A[i][1]=i+1;

    stable_sort(A.begin(),A.end());
    vector<ll>BIT1(n+1),BIT2(n+1);
    ll ats = 0;

    for(int i=n-1; i>=0; i--)
            L[i] = query(BIT1,A[i][1]),update(BIT1,A[i][1],1);

    for(int i=0; i<n; i++)
            G[i] = query(BIT2,n) - query(BIT2,A[i][1]),update(BIT2,A[i][1],1);

    for(int i=0; i<n; i++)
        ats+=L[i]*G[i];

    cout<<ats<<"\n";
}
