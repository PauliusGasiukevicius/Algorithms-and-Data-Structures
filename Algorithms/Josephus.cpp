#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

int josephus(int n, int k) //standart problem when we always remove every k-th person
{
    int ats = 0;
    for(int i=1; i<=n; i++)
        ats=(ats+k)%i;
    return ats+1;
}

int josephus2(int n)
{
    return 2*(n-pow(2,floor(log2(n))))+1;
}

int josephusW(int n, vector<int>&K)//modified, now we will remove K[0]-thperson first, then K[1]-th...
{
    int ats = 0;
    for(int i=1; i<=n; i++)
        ats = (ats + K[n-i])%i;
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
