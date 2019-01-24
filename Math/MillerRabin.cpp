#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

ll mulmod(ll a, ll b, ll mod)
{
    ll x = 0,y=a%mod;

    while(b > 0)
    {
        if(b&1)x = (x+y)%mod;
        y = (y*2)%mod;
        b /= 2;
    }
    return x%mod;
}

ll powm(ll a, ll n, ll mod)
{
    if(n==0)return 1%mod;
    if(n&1)return mulmod(a,powm(a,n-1,mod),mod);
    return powm(mulmod(a,a,mod),n/2,mod);
}

bool millerTest(ll n, ll d)
{
     mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
     ll a = uniform_int_distribution<ll>(2LL,n-2LL)(rnd);
     ll x = powm(a,d,n);
     if(x==1 || x==n-1)return 1;

     while(d!= n-1)
     {
         x=powm(x,2,n);
         d*=2;

         if(x==1)return 0;
         if(x==n-1)return 1;
     }
     return 0;
}

bool isPrimeMillerRabin(ll n, int iterations)
{
    if(n==2 || n==3)return 1;
    if(n<4 || n%2==0)return 0;

    ll d = n-1;
    while(d%2==0)d/=2;

    while(iterations--)
    {
        if(!millerTest(n,d))
            return 0;
    }
    return 1;
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int t;
    ll n;
    cin>>t;
    while(t--)
    {
        cin>>n;
        cout<<(isPrimeMillerRabin(n,1000) ? "YES\n" : "NO\n");
    }
}
