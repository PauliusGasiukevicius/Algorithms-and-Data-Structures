#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 1234567890

void Add(vector<ll>&BIT, int c, ll val)
{
    for(;c<BIT.size();c+=c&-c)
        BIT[c]+=val;
}

ll Get(vector<ll>&BIT, int c, ll s = 0)
{
    for(;c;c-=c&-c)
        s+=BIT[c];
    return s;
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    ll n,k, mod = 1e9;
    cin>>n>>k;
    vector<ll>A(n);
    for(auto&x:A)cin>>x;
    auto cp = A;
    sort(cp.begin(),cp.end());
    cp.erase(unique(cp.begin(),cp.end()),cp.end());

    vector<vector<ll>>BITS(k,vector<ll>(n+1));

    //Main idea: in BIT[x][pos] we store inversions of size x+1 that end in pos
    //inversions of larger size can only be made by taking some sequence of length x+1
    //and adding some smaller element to the end
    for(int i=0; i<A.size(); i++)
    {
        int id = lower_bound(cp.begin(),cp.end(),A[i]) - cp.begin() + 1;
        Add(BITS[0],id,1);
        for(int j=0; j+1<k; j++)
            Add(BITS[j+1], id, Get(BITS[j],n) - Get(BITS[j],id));
    }

    cout<<Get(BITS[k-1],n)%mod;
}
