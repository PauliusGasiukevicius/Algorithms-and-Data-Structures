#pragma GCC opointimize("Ofast")

#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 1234567890

vector<int>spf(100000001);

void precalc()
{
    for(int i=0; i<spf.size(); i++)spf[i]=i;
    for(int i=2; i*i<spf.size(); i++)
    if(spf[i]==i)
    for(int j=2*i; j<spf.size(); j+=i)
    if(spf[j]==j)spf[j]=i;
}

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

ll pollard_rho(ll n, ll c)
{ //finds some factor of n in O(n^1/4), sometimes fails and gives n itself so call with various c
    ll x = 2, y = 2;
    while(1)
    {
        //x = (x*x+c)%n;
        x = (mulmod(x, x, n)+c)%n;
        //y = (y*y+c)%n, y = (y*y+c)%n;
        y = (mulmod(y, y, n)+c)%n;
        y = (mulmod(y, y, n)+c)%n;
        ll d = __gcd(x-y, n);
        if(d > 1)return d;
    }
}

void factor(vector<ll>&factors, ll n)
{
    if(n == 1)return;

    if(n < spf.size())
    {
        ll f = spf[n];
        factors.push_back(f);
        factor(factors, n/f);
        return;
    }

    if(isPrimeMillerRabin(n,10))
    {
        factors.push_back(n);
        return;
    }

    ll c = 2;
    ll f = pollard_rho(n,2);
    while(f==n)f=pollard_rho(n,++c);

    factor(factors, n/f);
    factor(factors, f);
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    ll t,n;
    precalc();
    cin>>t;
    while(t--)
    {
        cin>>n;
        vector<ll>factors;
        cout<<n<<" = ";

        factor(factors,n);

        map<ll,ll>mp;
        for(auto&x:factors)
            mp[x]++;

        for(auto&p:mp)
        {
            ll f = p.first;
            ll d = p.second;

            if(p != *mp.begin())cout<<" * ";
            cout<<f;
            if(d > 1)cout<<"^"<<d;
        }
        cout<<"\n";
    }
}
