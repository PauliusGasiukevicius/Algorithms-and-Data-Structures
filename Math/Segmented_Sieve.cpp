/*
Finds all primes on interval L....R
passed PRIME1 & PRINT on SPOJ
*/
#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main()
{
    ios::sync_with_stdio(0);
   bitset<46500>notPrime(0);
   for(int i=2; i<220; i++)
   {
       while(notPrime[i])i++;
       for(int j=2*i; j<46500; j+=i)
        notPrime[j]=1;
   }

   vector<ll>P;

   for(int i=2; i<46500; i++)
    if(!notPrime[i])P.push_back(i);

   ll t,L,R;
   cin>>t;

   while(t--)
   {
        cin>>L>>R;
        if(L==1)L++;
        bitset<1000002>notPrime(0);

        for(ll&p:P)
            {
              ll x = L + (p - (L%p==0 ? p : L%p));
              if(x==p)x+=p;
            for(x; x <=R; x+=p)
            notPrime[x-L]=1;
            }

        for(ll i=0; L+i <= R; i++)
            if(!notPrime[i])
            cout<<L+i<<"\n";
            cout<<"\n";
   }
}
