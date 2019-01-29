#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666
ll k,x0,x1;
ll a[11],c[11],m[11],l[11],r[11];

ll f(ll x) //recursive function where x(i) is defined using x(i-1) in which we need to find cycle
{
    for(int i=0; i<k; i++)
        if(x>=l[i] && x<=r[i])
        return(a[i]*x+c[i])%m[i];
    return x;
}

int main()
{
    ios::sync_with_stdio(0);
    cin>>k>>x0;
    for(int i=0; i<k; i++)
        cin>>a[i]>>c[i]>>m[i]>>l[i]>>r[i];

    ll tortoise = f(x0);
    ll hare = f(f(x0));

    while(tortoise!=hare)
    {
        tortoise = f(tortoise);
        hare = f(f(hare));
    }

    ll mu = 0;//first point of cycle
    tortoise = x0;
    while (tortoise != hare)
        tortoise = f(tortoise),hare = f(hare),mu++;

    ll lam = 1; //size of cycle
    hare = f(tortoise);
    while (tortoise != hare)
        hare = f(hare),lam++;

    cout<<lam+mu<<" "<<mu<<"\n";
}
