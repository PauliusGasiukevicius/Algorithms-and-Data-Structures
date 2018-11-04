#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

/*
Consider an n×n grid whose top-left square is (1,1) and bottom-right square is (n,n).
Your task is to move from the top-left square to the bottom-right square.
On each step you may move one square right or down.
In addition, there are m traps in the grid. You cannot move to a square which has a trap.
What is the total number of possible paths?
n < 1e6, m < 1e3
*/

ll F[2000001];
ll invF[2000001];
ll M = 1e9+7;

ll powm(ll a, ll n, ll M)
{
    if(n==0)return 1;
    if(n&1)return a*powm(a,n-1,M)%M;
    return powm(a*a%M,n/2,M);
}

ll inv(ll x)
{
    if(invF[x]!=0)return invF[x];
    return invF[x]=powm(F[x],M-2,M);
}

ll C(int n, int k)
{
    if(k>n)return 0;
    return ((F[n]*inv(k)%M)*inv(n-k))%M;
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    F[0]=invF[0]=1;
    for(int i=1; i<=2000000; i++)
        F[i]=(F[i-1]*i)%M;//,invF[i]=powm(F[i],M-2,M);

    int n,m;
    cin>>n>>m;
    vector<array<int,2>>A(m);
    for(auto&a:A)
        cin>>a[0]>>a[1];

    sort(A.begin(),A.end());
    ll ats = C(2*n-2,n-1);
    vector<ll>ways(m); //ways to reach blocked cell [i][j],
    //without visiting any blocked cell [i][j] thats before this one

    for(int i=0; i<m; i++)
    {
        ll x = A[i][0];
        ll y = A[i][1];

        ways[i] = C(x+y-2,x-1);
        for(int j=0; j<i; j++)
        {
            ll x2 = A[j][0];
            ll y2 = A[j][1];
            if(y2 > y)continue;
            ways[i] -= ways[j]*C((x-x2)+(y-y2),(x-x2));//number of paths that are already counted
            ways[i]%=M;
            if(ways[i] < 0)ways[i]+=M;
        }
        ats = (ats - ways[i]*C(n-x+n-y,n-x))%M;
        if(ats<0)ats+=M;
    }

    cout<<ats;
}
