#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
const int RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
struct chash {
    int operator()(int x) const { return hash<int>{}(x ^ RANDOM); }
};

/*
Finding number of intervals such that sum of all integers in interval minus smallest integer is divisible by k
*/

ll solve(vector<int>&A, int l, int r, int k)
{
    if(l>=r)return 0;
    int m = (r+l)/2;

    for(int i=m-1; i>=l; i--)
        if(A[i] < A[m])m=i;

    for(int i=m+1; i<=r; i++)
        if(A[i] < A[m])m=i;

    gp_hash_table<int, int, chash> mp;
    ll ats = 0,s = 0;
    for(int i=m-1; i>=l; i--)
        {
            s=(A[i]+s)%k;
            if(s==0)ats++;
            mp[s]++;
        }
    s=0;
    for(int i=m+1; i<=r; i++)
    {
        s=(s+A[i])%k;
        if(s==0)ats++;
        ats+=mp[(k-s)%k];
    }

    return ats + solve(A,l,m-1,k) + solve(A,m+1,r,k);
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    int n,k;
    cin>>n>>k;
    vector<int>A(n+1);
    for(int i=1; i<=n; i++)
        cin>>A[i];

    cout<<solve(A,1,n,k)<<"\n";
}
