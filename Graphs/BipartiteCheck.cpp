#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(0);
    int n,m;
    cin>>n>>m;
    vector<int>G[101];

    for(int i=0,u,v; i<m; i++)
        cin>>u>>v,G[u].push_back(v),G[v].push_back(u);

    vector<int>color(n+1,0);

    for(int i=1; i<=n; i++)
        if(color[i]==0)
    {
        color[i]=1;
        queue<int>q({i});

        while(!q.empty())
        {
            int c = q.front();
            q.pop();

            for(auto&u:G[c])
                if(color[u]==0)
            {
                color[u]= (color[c]==1 ? 2 : 1);
                q.push(u);
            }
            else if(color[u]==color[c])
                return cout<<"NO\n",0;
        }
    }

    cout<<"YES\n";
}
