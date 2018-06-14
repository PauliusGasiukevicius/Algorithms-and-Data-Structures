#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

int josephus(int n, int k)
{
    int ats = 0;
    for(int i=1; i<=n; i++)
        ats=(ats+k)%i;
    return ats+1;
}

int main()
{
    ios::sync_with_stdio(0);
    int t,n,k;
    cin>>t;
    for(int cs=1; cs<=t; cs++)
    {
        cin>>n>>k;
        cout<<"Case "<<cs<<": "<<josephus(n,k)<<"\n";
    }
}
