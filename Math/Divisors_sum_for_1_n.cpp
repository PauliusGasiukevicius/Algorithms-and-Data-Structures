#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

ll powm(ll a, ll n, ll M)
{
    if(n==0)return 1%M;
    if(n&1)return a*powm(a,n-1,M)%M;
    return powm(a*a%M,n/2,M);
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    ll n;
    cin>>n;
    //let sum_div(x) - sum of divisors of x
    //we need sum (1...n) of sum_div(i)
    //brute-force: for(1..n) ats+= i*n/i;
    //thats too slow, but notice that n/i only has O(sqrt(n)) distinct values
    //for every suck value we can find lower_bound, upper_bound
    //and add (lower, lower + 1, ..., upper)*k to answer

    ll M = 1e9+7;
    ll ats = 0;
    ll inv2 = powm(2,M-2,M);
    vector<ll>D;
    for(ll i=1; i*i<=n; i++)
    D.push_back(i),D.push_back(n/i);

    sort(D.begin(),D.end());
    D.erase(unique(D.begin(),D.end()),D.end());
    reverse(D.begin(),D.end());
    ll lo=1;
    for(ll&k : D)
    {
        ll hi = n/k; //n/x = k, kx=n
        //cout<<lo<<" "<<hi<<" "<<k<<"\n";

        ll sum = (((((((1+hi)%M) * (hi%M))%M)*inv2)%M - ((((lo-1)%M)*(lo%M))%M)*inv2%M)%M+M)%M;
        ats= (ats + (k%M)*sum)%M;
        lo=hi+1;
    }
    cout<<ats;
}
