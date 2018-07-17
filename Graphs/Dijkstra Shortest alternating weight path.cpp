#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo INT_MAX/2

int main()
{
    //ios::sync_with_stdio(0);cin.tie(0);
    int t,n,m,st,en;
    //cin>>t;
    scanf("%d",&t);

    while(t--)
    {
        //cin>>n>>m;
        scanf("%d%d",&n, &m);
        vector<vector<pair<ll,ll>>>inc(n+1);
        vector<vector<pair<ll,ll>>>dec(n+1);
        for(int i=0; i<m; i++)
        {
            int u,v,w;
           // cin>>u>>v>>w;
           scanf("%d%d%d",&u, &v, &w);
            inc[u].push_back({w,v});
            inc[v].push_back({w,u});
            dec[u].push_back({w,v});
            dec[v].push_back({w,u});
        }

        for(int i=1; i<=n; i++)
            sort(inc[i].begin(),inc[i].end()),sort(dec[i].rbegin(),dec[i].rend());

        //cin>>st>>en;
        scanf("%d%d",&st, &en);
        #define T array<ll,4>
        priority_queue<T, vector<T>, greater<T>>q;
        //steps,node,lastE,less ? 0 : 1
        map<T,ll>mp;
        for(auto& u : inc[st])
            q.push({u.first,u.second,u.first,0}),mp[{u.second,u.first,0}]=u.first;

        vector<int>incPos(n+1),decPos(n+1);

        ll ats = LLONG_MAX;

        while(!q.empty())
        {
            ll w = q.top()[0];
            ll c = q.top()[1];
            ll lastE = q.top()[2];
            ll ls = q.top()[3];
            q.pop();

            if(c==en)
            {
                ats=w;
                break;
            }

            if(mp[{c,lastE,ls}] < w)continue;

            if(ls==0)
            {
                for(incPos[c]; incPos[c] < inc[c].size(); incPos[c]++)
                    {
                        auto u = inc[c][incPos[c]];
                        if(u.first < lastE)
                {
                    if(!mp.count({u.second,u.first,!ls}) || mp[{u.second,u.first,!ls}] > w+u.first)
                    mp[{u.second,u.first,!ls}]=w+u.first,q.push({w+u.first,u.second,u.first,!ls});
                }else break;
                    }
            }
            else
            {
                for(decPos[c]; decPos[c] < dec[c].size(); decPos[c]++)
                    {
                        auto u = dec[c][decPos[c]];
                        if(u.first > lastE)
                {
                    if(!mp.count({u.second,u.first,!ls}) || mp[{u.second,u.first,!ls}] > w+u.first)
                    mp[{u.second,u.first,!ls}]=w+u.first,q.push({w+u.first,u.second,u.first,!ls});
                }else break;
                    }
            }
        }

        if(ats>=LLONG_MAX)printf("No Solution\n");//cout<<"No Solution\n";
        else printf("%lld\n",ats);//cout<<ats<<"\n";
    }
}
