#include <bits/stdc++.h>
using namespace std;
 
int main()
{
    ios::sync_with_stdio(0);
    int n;
    while(cin>>n && n!=0)
    {
        vector<pair<int,string>>G[1001];
        string s;
        int x;
        bool PARADOX = 0;
 
        for(int i=1; i<=n; i++)
        {
            cin>>x>>s;
            for(auto&ch:s)ch|=' ';
            G[i].push_back({x,s});
            G[x].push_back({i,s});
            if(x==i && s=="false")PARADOX=1;
        }
 
        vector<int>visited(n+1,0);
        vector<int>True(n+1,0);
 
        for(int i=1; i<=n; i++)
            if(!visited[i])
        {
            bool T = 1, F = 1;
            visited[i] = 1;
            True[i] = 1;
            vector<int>nodes;
 
            queue<pair<int,string>>q;
            q.push({i,"true"});
 
            while(!q.empty())
            {
                int c = q.front().first;
                s = q.front().second;
                q.pop();
                nodes.push_back(c);
 
                for(auto&p : G[c])
                    if(!visited[p.first])
                {
                    visited[p.first] = 1;
                    if(s=="true")
                    True[p.first] = (p.second=="true" ? 1 : 0);
                    else
                    True[p.first] = (p.second=="true" ? 0 : 1);
 
                    q.push({p.first,(True[p.first] ? "true" : "false")});
                }else
                {
                    if(s=="true" && p.second=="true" && !True[p.first])T=0;
                    if(s=="true" && p.second=="false" && True[p.first])T=0;
                    if(s=="false" && p.second=="false" && !True[p.first])T=0;
                    if(s=="false" && p.second=="true" && True[p.first])T=0;
                }
            }
 
            if(T)continue;
 
            q.push({i,"false"});
            for(auto&u:nodes)
                visited[u]=0,True[u]=0;
 
            visited[i] = 1;
 
            while(!q.empty())
            {
                int c = q.front().first;
                s = q.front().second;
                q.pop();
 
                for(auto&p : G[c])
                    if(!visited[p.first])
                {
                    visited[p.first] = 1;
                    if(s=="true")
                    True[p.first] = (p.second=="true" ? 1 : 0);
                    else
                    True[p.first] = (p.second=="true" ? 0 : 1);
 
                    q.push({p.first,(True[p.first] ? "true" : "false")});
                }else
                {
                    if(s=="true" && p.second=="true" && !True[p.first])F=0;
                    if(s=="true" && p.second=="false" && True[p.first])F=0;
                    if(s=="false" && p.second=="false" && !True[p.first])F=0;
                    if(s=="false" && p.second=="true" && True[p.first])F=0;
                }
            }
 
            if(!F)
            PARADOX = true;
        }
 
        cout<<(PARADOX ? "PARADOX\n" : "NOT PARADOX\n");
    }
}
