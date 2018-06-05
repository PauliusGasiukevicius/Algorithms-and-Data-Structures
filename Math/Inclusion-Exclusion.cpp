#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

int main()
{
    ios::sync_with_stdio(0);
    ll n,m;
    /*
    Here we are finding how many numbers in set [1,2,...,n]
    are not divisible by any of A[0],A[1],...,A[m-1]
    */
    while(cin>>n>>m)
    {
        ll ats = n;
        vector<ll>A(m);
        for(ll&x:A)cin>>x;

        for(int i=1; i<(1<<m); i++)
        {
            bitset<16>b(i);
            ll p = 1;
            for(int j=0; j<m && p<=n; j++)
                if(b[j])p=p*A[j]/__gcd(p,A[j]);//LCM magic

            ats += (b.count()&1 ? -n/p : n/p);
        }
        cout<<ats<<"\n";
    }
}
