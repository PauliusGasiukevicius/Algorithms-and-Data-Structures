#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define oo INT_MAX/10

int phi(int n)
{
    int res = n;
    for(int i=2; i*i<=n; i++)
        if(n%i==0)
    {
        while(n%i==0)
        n/=i;

        res-=res/i;
    }

    res-=(n>1 ? res/n : 0);
    return res;
}

int main()
{
    ios::sync_with_stdio(0);
    int t,n;
    cin>>t;

    while(t--)
    {
        cin>>n;
        cout<<phi(n)<<"\n";
    }
}
