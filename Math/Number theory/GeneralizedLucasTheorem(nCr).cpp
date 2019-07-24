#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 1234567890

const int mxMod = 1000000;
vector<int> phi(mxMod+1, -1), primes;

bool arePrimesGenerated = false;
//Generate primes and also calculate phi function values
void genprime()
{
    for(int i = 2;i <=mxMod; i++)
        if(phi[i]==-1)
        {
            primes.push_back(i);
            phi[i] = i-1;
            for(int j = 2*i; j<=mxMod; j+=i)
            {
                if(phi[j]==-1)phi[j] = j;
                phi[j] = (phi[j]/i)*(i-1);
            }
        }
}

//Calculates x raised to the power of p % m
ll powm(ll a, ll n, ll m = 1LL<<62)
{
    if(n==0)return 1%m;
    if(n&1)return a*powm(a,n-1,m)%m;
    return powm((a*a)%m,n/2,m);
}

ll inverse(ll x, ll m)
{
    if(x==1)return 1;
    return powm(x, phi[m]-1, m)%m;
}

//finds (n!)_p (factorial of n without any p factors)
ll ff(ll n, ll p, ll q)
{
    ll x = 1, y = powm(p, q);
    for(int i = 2; i<=n;i++)
        if(i%p)
            x = (x*i)%y;
    return x%y;
}

//Generalized Lucas Theorem calculates nCm mod p^q
ll nCr_mod_pq(ll n, ll m, ll p, ll q){
    ll r = n-m, x = powm(p, q);
    ll e0 = 0, eq = 0;
    ll mul = (p==2&&q>=3)? 1: -1;
    ll cr = r, cm = m, carry = 0, cnt = 0;
    while(cr||cm||carry)
    {
        cnt++;
        ll rr = cr%p, rm = cm%p;
        if(rr + rm + carry >= p)
        {
            e0++;
            if(cnt>=q)eq++;
        }
        carry = (carry+rr+rm)/p;
        cr/=p;
        cm/=p;
    }
    mul = powm(p, e0)*powm(mul, eq);
    ll ret = (mul % x + x) % x;
    ll temp = 1;
    for(int i = 0;;i++)//This is THE line that calculates the formula
    {
        ret = ((ret*ff((n/temp)%x, p, q)%x)%x*(inverse(ff((m/temp)%x, p, q), x)%x*inverse(ff((r/temp)%x, p, q), x)%x)%x)%x;

        if(temp>n/p && temp>m/p && temp>r/p)
            break;
        temp = temp*p;
    }
    return (ret%x+x)%x;
}


ll gcd(ll a, ll b, ll& x, ll& y) {
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }
    ll x1, y1;
    ll d = gcd(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return d;
}

array<ll, 2> chinese_remainder_theorem( vector<ll> A, vector<ll> M ) {
    if(A.size() != M.size()) return {-1,-1}; /** Invalid input*/
    ll n = A.size();

    ll a1 = A[0];
    ll m1 = M[0];

    for ( int i = 1; i < n; i++ ) {
        ll a2 = A[i];
        ll m2 = M[i];

        ll g = __gcd(m1, m2);
        if ( a1 % g != a2 % g ) return {-1,-1}; /** No solution */

        ll p, q;
        gcd(m1/g, m2/g, p, q);

        ll mod = m1 / g * m2; /** LCM of m1 and m2*/

        ll x = ((a1*(m2/g))%mod *q %mod + (a2*(m1/g))%mod * p %mod) % mod;/** Overflow is possible*/

        a1 = x;
        if (a1 < 0) a1 += mod; /** Result is not suppose to be negative*/
        m1 = mod;
    }
    return {a1, m1};
}

ll nCr_mod_anyMod(ll n, ll r, ll m)
{
    if(!arePrimesGenerated)genprime(),arePrimesGenerated = 1;

    vector<ll>A,M; //A - results, M - modulo`s (pj^qi)
    vector<array<ll,2>>P; //stores factors in form {p,q} -> p^q

    for(ll p=2; p<=m; p++)
        if(m%p==0)
        {
            ll q = 0, pq = 1;
            while(m%p==0)m/=p,q++, pq*=p;
            P.push_back({p,q});
            M.push_back(pq);
        }

    for(auto&f:P)
    A.push_back(nCr_mod_pq(n,r,f[0],f[1]));

    return chinese_remainder_theorem(A,M)[0];
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    ll n, r, m;
    cin>>n>>r>>m;
    cout<<nCr_mod_anyMod(n,r,m)<<"\n";
}
