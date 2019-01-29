#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main()
{
    ios::sync_with_stdio(0);
    int n,m,q,st,en,cap;
    cin>>n>>m;
    vector<int>C(n);
    for(int&x:C)cin>>x;
    vector<pair<int,int>>G[1001];

    for(int i=0,v,u,w; i<m; i++)
    cin>>u>>v>>w,G[u].push_back({w,v}),G[v].push_back({w,u});

    cin>>q;
    while(q--)
    {
        cin>>cap>>st>>en;
        vector<vector<int>>SP(n,vector<int>(cap+1,666666666));
        SP[st][0]=0;
        priority_queue<vector<int>,vector<vector<int>>,greater<vector<int>>>Q;
        Q.push({0,st,0});//[w][c][fuel]

        while(!Q.empty() && Q.top()[1]!=en)
        {
            int w = Q.top()[0];
            int c = Q.top()[1];
            int fuel = Q.top()[2];
            Q.pop();

            for(auto&p:G[c])
                if(fuel >= p.first && w < SP[p.second][fuel-p.first])
            SP[p.second][fuel-p.first]=w,Q.push({w,p.second,fuel-p.first});

            for(int i=1; i+fuel<=cap; i++)
                if(w+i*C[c] < SP[c][fuel+i])
            SP[c][fuel+i]=w+i*C[c],Q.push({w+i*C[c],c,fuel+i});
        }

        if(SP[en][0]>=666666666)
            cout<<"impossible\n";
        else
            cout<<SP[en][0]<<"\n";
    }
}
