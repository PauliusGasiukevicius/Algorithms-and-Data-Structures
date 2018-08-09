#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo INT_MAX/2

vector<int>FindCenter(vector<vector<int>>&G)
{
    int c = 1;
    vector<int>P;
    queue<int>q;
    for(int j=0; j<2; j++)
    {
    P.assign(G.size(),-1);
    P[c]=c;
    q.push(c);
    while(!q.empty())
    {
        c = q.front();
        q.pop();
        for(auto& u : G[c])
            if(P[u] == -1)
                q.push(u),P[u]=c;
    }
    }
    vector<int>diameter = {c};
    while(P[c]!=c)
        c=P[c],diameter.push_back(c);

    if(diameter.size()%2==1)return {diameter[diameter.size()/2]};
    return {diameter[diameter.size()/2-1], diameter[diameter.size()/2]};
}

void dfs(int c, int d, vector<int>&P, vector<vector<int>>&D, vector<vector<int>>&G)
{
    D[d].push_back(c);
    for(auto&u : G[c])
        if(u!=P[c])
        P[u]=c,dfs(u,d+1,P,D,G);
}

bool rooted_isomorphic(vector<vector<int>>&T1, vector<vector<int>>&T2, int r1, int r2)
{
    vector<int>P1(T1.size(),-1),P2(T2.size(),-1);
    vector<vector<int>>D1(T1.size()+1),D2(T2.size()+1);
    vector<int>ID1(T1.size()),ID2(T2.size());
    dfs(r1,0,P1,D1,T1);
    dfs(r2,0,P2,D2,T2);

    for(int d=T1.size(); d>=0; d--)
    {
        if(D1[d].size()!=D2[d].size())return 0;
        if(D1[d].empty())continue;

        vector<pair<vector<int>,int>>L1,L2;
        for(int i=0; i<D1[d].size(); i++)
        {
            auto&c = D1[d][i];
            vector<int>CC;
            for(auto&u : T1[c])
                if(u!=P1[c])
                CC.push_back(ID1[u]);
            sort(CC.begin(),CC.end());
            L1.push_back({CC,i});
        }

        for(int i=0; i<D2[d].size(); i++)
        {
            auto&c = D2[d][i];
            vector<int>CC;
            for(auto&u : T2[c])
                if(u!=P2[c])
                CC.push_back(ID2[u]);
            sort(CC.begin(),CC.end());
            L2.push_back({CC,i});
        }

        sort(L1.begin(),L1.end());
        sort(L2.begin(),L2.end());


      /*  cout<<"L1:\n";
        for(auto&p:L1)
        {
            cout<<p.second<<": ";
            for(auto&v:p.first)
                cout<<v<<",";
            cout<<"\n";
        }cout<<"\n";

        cout<<"L2:\n";
        for(auto&p:L2)
        {
            cout<<p.second<<": ";
            for(auto&v:p.first)
                cout<<v<<",";
            cout<<"\n";
        }cout<<"\n";*/

        for(int i=0; i<L1.size(); i++)
            if(L1[i].first!=L2[i].first)return 0;
        map<vector<int>,int>mp;
        int nxt = 0;

        for(int i=0; i<L1.size(); i++)
            if(!mp.count(L1[i].first))
                mp[L1[i].first]=++nxt;

        for(int i=0; i<L1.size(); i++)
            ID1[D1[d][L1[i].second]]=mp[L1[i].first];

        for(int i=0; i<L2.size(); i++)
            ID2[D2[d][L2[i].second]]=mp[L2[i].first];
    }
    return 1;
}

bool isomorphic(vector<vector<int>>&T1, vector<vector<int>>&T2)
{
    if(T1.size()!=T2.size())return 0;
    vector<int>center1 = FindCenter(T1);
    vector<int>center2 = FindCenter(T2);
    //cout<<center1[0]<<" "<<center2[0]<<" <-centers\n";
    if(center1.size() != center2.size())return 0;
    if(center1.size()==1)return rooted_isomorphic(T1,T2,center1[0],center2[0]);
    return rooted_isomorphic(T1,T2,center1[0],center2[0]) || rooted_isomorphic(T1,T2,center1[0],center2[1]);
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    int t,n,u,v;
    cin>>t;
    while(t--)
    {
        cin>>n;
        vector<vector<int>>T1(n+1),T2(n+1);
        for(int i=1; i<n; i++)
        {
            cin>>u>>v;
            T1[u].push_back(v);
            T1[v].push_back(u);
        }

        for(int i=1; i<n; i++)
        {
            cin>>u>>v;
            T2[u].push_back(v);
            T2[v].push_back(u);
        }

        cout<<(isomorphic(T1,T2) ? "YES\n" : "NO\n");
    }
}
