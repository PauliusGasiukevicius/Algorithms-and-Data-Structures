#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo INT_MAX/2

int Find(vector<ll>&P, int u)
{
    return P[u] < 0 ? u : P[u] = Find(P,P[u]);
}

void Union(vector<ll>&P, int u, int v)
{
    u=Find(P,u);
    v=Find(P,v);
    if(u==v)return;
    P[u]+=P[v];
    P[v]=u;
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    ll n;
    cin>>n;
    vector<vector<ll>>E(n-1,vector<ll>(3));
    vector<ll>P(n+1,-1);
    ll sum = 0;
    for(auto&e:E)
    {
        cin>>e[1]>>e[2]>>e[0];
        sum+=e[0];
    }

    sort(E.begin(),E.end());
    ld ats = n*(n-1)/2;
    ats*=sum;

    for(auto&e:E)
    {
        int u = Find(P,e[1]);
        int v = Find(P,e[2]);
        ats-= P[u]*P[v]*e[0];
        Union(P,u,v);
    }

    cout<<setprecision(13)<<fixed<<(1.0*ats)/(n*(n-1)/2)<<"\n";
}

