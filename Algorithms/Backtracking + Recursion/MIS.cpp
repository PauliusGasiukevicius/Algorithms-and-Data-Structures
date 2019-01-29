#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

ll mx,total;

void solve(ll c, ll visited, vector<ll>&M, ll cnt)
{
    if(visited == (1LL<<M.size())-1)
    {
        total++;
        mx=(cnt>mx ? cnt : mx);
        return;
    }
    for(int i=c; i<M.size(); i++)
        if(!(1LL<<i & visited))
        solve(i+1,visited | M[i] | (1LL<<i),M,cnt+1);
}

int main()
{
    ios::sync_with_stdio(0);
    ll t,n,m;
    cin>>t;
    while(t--)
    {
        mx=total=0;
        cin>>n>>m;
        vector<ll>M(n);
        for(int i=0,u,v; i<m; i++)
        {
            cin>>u>>v;
            M[u]|=(1LL<<v);
            M[v]|=(1LL<<u);
        }
        solve(0,0,M,0);
        cout<<total<<"\n"<<mx<<"\n";
    }
}
