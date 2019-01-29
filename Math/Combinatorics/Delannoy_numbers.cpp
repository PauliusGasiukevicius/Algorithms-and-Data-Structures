#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double

ll powm(ll a, ll d, ll M)
{
    if(d==0)return 1;
    if(d&1)return (a*powm(a,d-1,M))%M;
    return powm((a*a)%M,d/2,M)%M;
}

ll C(vector<ll>&F, vector<ll>&inv, int n, int k, ll& M)
{
    if(n==k || k==0)return 1;
    return F[n]*inv[k]%M*inv[n-k]%M;
}

int main()
{
    ios::sync_with_stdio(0);
    ll M = 1e9+7;
    vector<ll>F(200001),inv(200001);
    F[0]=1;
    inv[0]=powm(1,M-2,M);
    for(ll i=1; i<200001; i++)
        F[i]=(F[i-1]*i)%M, inv[i]=powm(F[i],M-2,M);

    int t;
    cin>>t;

    for(int cs=1; cs<=t; cs++)
    {
        int x1,x2,y1,y2;
        cin>>x1>>y1>>x2>>y2;
        ll ats = 0;
        for(int d=0; d<=min(x2-x1,y2-y1); d++)
        {
            int steps = x2-x1+y2-y1;
            ats = (ats + C(F,inv,x2-x1,d,M)%M * C(F,inv,steps-d,x2-x1,M)%M)%M;
            //cout<<C(F,inv,x2-x1,d,M)%M<<" "<<C(F,inv,steps-d,x2-x1,M)%M<<"\n";
        }
        cout<<"Case "<<cs<<": "<<ats<<"\n";
    }
}
