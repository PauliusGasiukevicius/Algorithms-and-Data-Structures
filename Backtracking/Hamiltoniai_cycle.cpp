#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define oo LLONG_MAX/2
int n;
void solve(vector<int>G[], int c, vector<int>&visited, vector<int>path, vector<int>&ats)
{
    if(!ats.empty())return;
    if(path.size()==n)
    {
        for(auto&u : G[c])
            if(u==path[0])
        {
            ats=path;
            return;
        }
        return;
    }

    for(auto&u : G[c])
    if(!visited[u])
    {
        visited[u]=1;
        path.push_back(u);
        solve(G,u,visited,path,ats);
        path.pop_back();
        visited[u]=0;
    }
}

int main()
{
    ios::sync_with_stdio(0);

    while(cin>>n)
    {
        cin.ignore();
        string s;
        vector<int>G[257];
        while(getline(cin,s) && s[0]!='%')
        {
            stringstream ss(s);
            int u,v;
            ss>>u>>v;
            G[u].push_back(v);
            G[v].push_back(u);
        }
        vector<int>visited(n+1),ats,path;
        path.push_back(1);
        visited[1]=1;
        solve(G,1,visited,path,ats);

        if(ats.empty())cout<<"N\n";
        else
        {
            ats.push_back(ats[0]);
            for(int i=0; i<ats.size(); i++)
                cout<<ats[i]<<(i+1==ats.size()?"\n":" ");
        }
    }
}
