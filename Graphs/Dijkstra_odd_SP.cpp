#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main()
{
    ios::sync_with_stdio(0);
    int n,m,cs=1;
    while(cin>>n>>m)
    {
        vector<pair<int,int>>G[501];
        for(int i=0,u,v,w; i<m; i++)
        cin>>u>>v>>w,G[u].push_back({w,v}),G[v].push_back({w,u});
        vector<vector<int>>SP(n,vector<int>(2,666666666));
        SP[0][0]=0;
        priority_queue<vector<int>,vector<vector<int>>,greater<vector<int>>>q;
        q.push({0,0,0});//[w][c][0-walk, 1 -bike]

        while(!q.empty())
        {
            int w = q.top()[0];
            int c = q.top()[1];
            int mode = q.top()[2];
            q.pop();

            for(auto&p:G[c])
                if(w+p.first < SP[p.second][!mode])
            SP[p.second][!mode]=w+p.first,q.push({SP[p.second][!mode],p.second,!mode});
        }

        cout<<"SET #"<<cs++<<"\n";
        if(SP[n-1][0] >= 666666666)
            cout<<"?\n";
        else
            cout<<SP[n-1][0]<<"\n";
    }
}
