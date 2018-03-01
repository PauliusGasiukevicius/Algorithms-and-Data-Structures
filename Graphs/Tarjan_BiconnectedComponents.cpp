#include <bits/stdc++.h>
using namespace std;

int low[100001];
int disc[100001];
int P[100001];
int root = 1;
int child = 0;

void DFS(int c, vector<int>G[], vector<vector<vector<int>>>&BC, stack<vector<int>>&S)
{
    static int tm = 1;
    disc[c]=low[c]=tm++;

    for(int&u:G[c])
        if(disc[u]==0)
    {
        child++;
        P[u]=c;
        S.push({c,u});
        DFS(u,G,BC,S);
        low[c]=min(low[c],low[u]);

        if(low[u] >= disc[c] )
        {
            vector<vector<int>>B;
            vector<int>e = {c,u};
            while(S.top()!=e)
                B.push_back(S.top()),S.pop();
            B.push_back(S.top());
            S.pop();
            BC.push_back(B);
        }
        else if(c==root && child > 1)
        {
            vector<vector<int>>B;
            vector<int>e = {c,u};
            while(S.top()!=e)
                B.push_back(S.top()),S.pop();
            B.push_back(S.top());
            S.pop();
            BC.push_back(B);
        }
    }
    else if(u!=P[c] && disc[u] < low[c])
        low[c]=disc[u],S.push({c,u});
}

int main()
{
    ios::sync_with_stdio(0);
    int n,m;
    cin>>n>>m;
    vector<int>G[100001];

    for(int i=0,u,v; i<m; i++)
        cin>>u>>v,G[u].push_back(v),G[v].push_back(u);

    vector<vector<vector<int>>>BC;

    for(int i=0; i<n; i++)
        if(disc[i]==0)
    {
        root=i;
        stack<vector<int>>S;
        DFS(i,G,BC,S);
        if(!S.empty())
        {
            vector<vector<int>>B;
            while(!S.empty())
                B.push_back(S.top()),S.pop();
            BC.push_back(B);
        }
    }

    int ats[2]={};


    for(auto&b : BC)
    {
        //cout<<b.size()<<"\n";
        set<int>v;
        for(auto&e:b)
            v.insert(e[0]),v.insert(e[1]);//,cout<<e[0]<<" "<<e[1]<<"\n";
        ats[v.size()%2]++;
    }

    cout<<ats[0]<<" "<<ats[1]<<"\n";
}
