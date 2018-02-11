#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main()
{
    ios::sync_with_stdio(0);
    int t,n,m,k,cs=1,Q;
    cin>>t;

    while(t--)
    {
        cin>>n>>m>>k;
        bitset<2048>A(0);
        for(int x,i=0; i<k; i++)
            cin>>x,A[x]=1;

        vector<pair<int,int>>G[5018];

        for(int i=1; i<=n; i++)
        G[i].push_back({!A[i],i+n}),G[i+n].push_back({!A[i],i});

        for(int i=0,u,v; i<m; i++)
        {
            cin>>u>>v;
            G[u+n].push_back({0,v});
            G[v+n].push_back({0,u});
        }

        cin>>Q;
        cout<<"Case "<<cs++<<":\n";
        while(Q--)
        {
            int x,y;
            cin>>x>>y;
            
            vector<int>SP(2*n+1,666666666);
            SP[x]=0;
            
            if(x==y)SP[y+n]=0;
            
            priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>q;
            q.push({0,x});

            while(!q.empty() && q.top().second!=y+n)
            {
                int w = q.top().first;
                int c = q.top().second;
                q.pop();

                for(auto&p : G[c])
                    if(w + p.first < SP[p.second])
                    SP[p.second]=w+p.first,q.push({SP[p.second],p.second});
            }
            cout<<(SP[y+n]>=666666666 ? -1 : SP[y+n])<<"\n";
        }
        cout<<"\n";
    }
}
