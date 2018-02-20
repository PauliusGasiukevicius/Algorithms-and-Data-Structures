#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main()
{
    ios::sync_with_stdio(0);
    bitset<50001>notPrime(0);

    for(int i=2; i<225; i++)
    {
        while(notPrime[i])i++;
        for(int j=2*i; j<50001; j+=i)
            notPrime[j]=1;
    }
    vector<ll>P;

    for(int i=2; i<50001; i++)
        if(!notPrime[i])P.push_back(i);

    ll L,U;

    while(cin>>L>>U)
    {
        if(L<2)L=2;
        ll mn = LLONG_MAX;
        ll mx = LLONG_MIN;
        bitset<1000001>notPrime(0);

        for(ll&p:P)
        {
            ll x = L;
            if(L%p!=0)x+=(p - L%p);
            if(x==p)x*=2;

            for(x; x<=U; x+=p)
                notPrime[x-L]=1;
        }
        vector<ll>Primes;
        for(ll x=L; x<=U; x++)
            if(!notPrime[x-L])Primes.push_back(x);

            for(int i=1; i<Primes.size(); i++)
                mx=max(mx,Primes[i]-Primes[i-1]),mn=min(mn,Primes[i]-Primes[i-1]);

        if(Primes.size()<=1)cout<<"There are no adjacent primes.\n";

        for(int i=1; i<Primes.size(); i++)
            if(Primes[i]-Primes[i-1]==mn)
        {
            cout<<Primes[i-1]<<","<<Primes[i]<<" are closest, ";
            break;
        }

        for(int i=1; i<Primes.size(); i++)
            if(Primes[i]-Primes[i-1]==mx)
        {
            cout<<Primes[i-1]<<","<<Primes[i]<<" are most distant.\n";
            break;
        }
    }
}
