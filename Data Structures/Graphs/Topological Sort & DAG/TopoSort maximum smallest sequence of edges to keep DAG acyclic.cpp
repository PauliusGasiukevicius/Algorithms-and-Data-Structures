#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo INT_MAX/2

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    int n;
    cin>>n;
    vector<string>A(n);
    vector<int>in(n+1);
    for(auto&s:A)cin>>s;
    vector<vector<int>>G(n+1);
    vector<set<int>>adj(n+1);

    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
        if(A[i][j]=='1')
        G[j+1].push_back(i+1),in[i+1]++,adj[i+1].insert(j+1);

    priority_queue<int>q;
    for(int i=1; i<=n; i++)
        if(in[i]==0)
        q.push(i);

    vector<int>Topo;

    while(!q.empty())
    {
        int c = q.top();
        q.pop();
        Topo.push_back(c);

        for(auto&u:G[c])
            if(--in[u]==0)
            q.push(u);
    }
    reverse(Topo.begin(),Topo.end());

    vector<pair<int,int>>ats;

    for(int i=0; i<Topo.size(); i++)
        for(int j=i+1; j<Topo.size(); j++)
            if(!adj[Topo[i]].count(Topo[j]))
        ats.push_back({Topo[i],Topo[j]});

    sort(ats.begin(),ats.end());
    cout<<ats.size()<<"\n";
    for(auto&p:ats)
        cout<<p.first<<" "<<p.second<<"\n";
}
