#include <bits/stdc++.h>
using namespace std;
#define ll long long
 
int main()
{
    ios::sync_with_stdio(0);
    int n,m,st,en;
    while(cin>>n>>m && n!=0)
    {
        cin>>st>>en;
        #define T vector<int>
        vector<T>G[505];
        int from[10001];
        for(int i=0,u,v,c; i<m; i++)
        cin>>u>>v>>c,G[u].push_back({c,v,i}),from[i]=u;
 
        T SP(505,666666666);
        SP[st]=0;
        set<int>E[505];
        priority_queue<T, vector<T>, greater<T>>q;
       bitset<505>visited(0);
        q.push({0,st,-1});
 
        while(!q.empty())
        {
            int c = q.top()[1];
            int w = q.top()[0];
            int edge = q.top()[2];
            q.pop();
 
            for(auto&v : G[c])
                if(w + v[0] < SP[v[1]])
            {
                SP[v[1]]=w+v[0];
                E[v[1]].clear();
                E[v[1]].insert(v[2]);
                q.push({SP[v[1]],v[1],v[2]});
            }
            else if(w + v[0] == SP[v[1]])
                E[v[1]].insert(v[2]);
        }
 
        unordered_set<int>e;
        queue<int>Q;
        Q.push(en);
        visited[en]=1;
 
        while(!Q.empty())
        {
            int c = Q.front();
            Q.pop();
            for(int edge : E[c])
            {
                e.insert(edge);
                if(!visited[from[edge]])
                    visited[from[edge]]=1,Q.push(from[edge]);
            }
        }
 
        vector<int>sp(n,666666666);
        sp[st]=0;
        q.push({0,st,-1});
 
        while(!q.empty())
        {
            int c = q.top()[1];
            int w = q.top()[0];
            int edge = q.top()[2];
            q.pop();
 
            for(auto&v : G[c])
                if(!e.count(v[2]) && w + v[0] < sp[v[1]])
            {
                sp[v[1]]=w+v[0];
                q.push({sp[v[1]],v[1],v[2]});
            }
        }
 
        cout<<(sp[en]>=666666666 ? -1 : sp[en])<<"\n";
    }
}
