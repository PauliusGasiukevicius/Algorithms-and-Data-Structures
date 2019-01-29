#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

vector<vector<ll>> Mul(vector<vector<ll>>A, vector<vector<ll>>B, ll m)
{
    int n = A.size();
    vector<vector<ll>>R(n,vector<ll>(n));

    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            for(int k=0; k<n; k++)
            R[i][j]= (R[i][j]%m + A[i][k]*B[k][j]%m)%m;

    return R;
}

vector<vector<ll>> MPow(vector<vector<ll>>M, ll n, ll m)
{
    if(n==1)return M;
    if(n&1)return Mul(M,MPow(M,n-1,m),m);
    return MPow(Mul(M,M,m),n/2,m);
}


int main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    //freopen("lacking.in","r",stdin);
    //freopen("lacking.out","w",stdout);
    ll n,m;
    cin>>n>>m;
    ll ats = 0;

    for(unsigned ll len = 1, pw = 1; len<=19; len++, pw*=10)
    {
        if(pw > n)break;
        ll L = pw, R = min(pw*10-1,(unsigned ll)n);
       // cout<<L<<" "<<R<<endl;
        vector<vector<ll>> M = {
            {10*pw%m, 1, 0},
            {    0, 1, 1},
            {    0, 0, 1}
        };
        //A = {ats, L, 1};
        if(R!=L)
        M = MPow(M,R-L+1,m);
        ats = ((M[0][0]*ats)%m + (M[0][1]*(L%m))%m + M[0][2])%m;
        //cout<<len<<" "<<ats<<"\n";
    }
    cout<<ats<<"\n";
}
