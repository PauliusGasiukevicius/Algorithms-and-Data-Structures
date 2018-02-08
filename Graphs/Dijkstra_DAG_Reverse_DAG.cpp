#include <bits/stdc++.h>
using namespace std;
#define ll long long
 
int main()
{
    ios::sync_with_stdio(0);
    int t,n,m,k,st,en;
    cin>>t;
    while(t--)
    {
        cin>>n>>m>>k>>st>>en;
        vector<pair<int,int>>G[10001], R[10001];
 
        for(int i=0,u,v,c; i<m; i++)
        cin>>u>>v>>c,G[u].push_back({c,v}),R[v].push_back({c,u});
 
        vector<int>SPs(10001,666666666), SPt(10001,666666666);
        SPs[st]=SPt[en]=0;
 
        priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>>q;
        bitset<10001>visiteds(0), visitedt(0);
        q.push({0,st});
 
        while(!q.empty())
        {
            int c = q.top().second;
            int w = q.top().first;
            q.pop();
            visiteds[c]=1;
 
            for(auto&p : G[c])
                if(!visiteds[p.second] && w + p.first < SPs[p.second])
            SPs[p.second] = w + p.first, q.push({SPs[p.second],p.second});
        }
 
        q.push({0,en});
 
        while(!q.empty())
        {
            int c = q.top().second;
            int w = q.top().first;
            q.pop();
            visitedt[c]=1;
 
            for(auto&p : R[c])
                if(!visitedt[p.second] && w + p.first < SPt[p.second])
            SPt[p.second] = w + p.first, q.push({SPt[p.second],p.second});
        }
 
        int ats = SPs[en];
 
        for(int i=0,u,v,c; i<k; i++)
            cin>>u>>v>>c, ats = min({ats, c + SPs[u] + SPt[v], c + SPt[u] + SPs[v]});
 
        cout<<(ats >= 666666666  ? -1 : ats)<<"\n";
    }
}
