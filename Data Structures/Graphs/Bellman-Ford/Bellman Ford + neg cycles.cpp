#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo INT_MAX/2

ll u[5005],v[5005],w[5005],D[5005],P[5005];
vector<array<ll,2>>G[5005];

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    ll n,m;
    cin>>n>>m;

    for(int i=0; i<m; i++)
    {
        cin>>u[i]>>v[i]>>w[i];
        G[v[i]].push_back({w[i],u[i]});
    }

    for(int i=1; i<=n; i++)
        D[i]=1e13;

    for(int i=1; i<n; i++)
        for(int j=0; j<m; j++)
        if(D[u[j]] + w[j] < D[v[j]])
            {
                D[v[j]] = w[j] + D[u[j]];
                P[v[j]] = u[j];
            }

        for(int j=0; j<m; j++)
        if(D[u[j]] + w[j] < D[v[j]])
            {
                P[v[j]] = u[j];
                int c = u[j];
                for(int i=0; i<n; i++) //keep going back so we are sure we are in some neg cycle
                    c=P[c];
                int cc = c;
                vector<int>cycle;

                while(1)
                {
                    cycle.push_back(c);
                    c=P[c];
                    if(c==cc)break;
                }

                cycle.push_back(c);
                cout<<"YES\n";
                reverse(cycle.begin(),cycle.end());
                for(int&x : cycle)
                    cout<<x<<" ";
                return 0;
            }

    cout<<"NO\n";
}
