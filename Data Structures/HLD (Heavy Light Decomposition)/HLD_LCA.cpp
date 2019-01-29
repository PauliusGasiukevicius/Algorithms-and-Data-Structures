#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

const int N = 100001;
int chain[N],head[N],P[N],D[N],sz[N],nxtChain=1;
ll dist[N]; //distance from root to node
vector<pair<int,ll>>G[N];

int dfs(int c)//sets node parents, depths, subtree sizes
{
    sz[c]=1;
    for(auto& u : G[c])
        if(u.first!=P[c])
        {
            P[u.first]=c;  //parent of node
            D[u.first]=D[c]+1; //depth of node
            dist[u.first]+=u.second+dist[c]; //sum of path from root to node
            sz[c]+=dfs(u.first); //subtree size of node
        }

    return sz[c];
}

void HLD(int c, int id)//Heavy-Light Decomposition, set id to -1 to start a new chain
{
    if(id<0)
    {
        id=nxtChain++;
        chain[c]=id;
        head[id]=c;
    }
    chain[c]=id;

    if(G[c].empty() || (G[c].size()==1 && G[c][0].first==P[c]))return; //leaf, so we`re done

    int mx = (P[c]==G[c][0].first ? G[c][1].first : G[c][0].first);//index in adj list for heaviest child

    for(auto& u : G[c])
        if(u.first!=P[c] && sz[u.first] > sz[mx])
        mx=u.first;

    HLD(mx,id);//Finish current chain

    for(auto& u : G[c])
        if(u.first!=P[c] && u.first!=mx)//for all other children, start next chains
        HLD(u.first,-1);
}

int LCA(int u, int v)//Find LCA of 2 nodes in a tree, uses HLD
{
    while(chain[u] != chain[v])//if nodes are not in same chains we gotta climb up to same chain
        if(D[head[chain[u]]] < D[head[chain[v]]])//we always move nodes with higher depth up
            v = P[head[chain[v]]];
        else
            u = P[head[chain[u]]];

    return D[u] < D[v] ? u : v;//nodes in same chain, so the one with lowest depth is LCA
}

int distance(int u, int v) //calculates distance between 2 nodes (unweighted tree)
{
    int lca = LCA(u,v);
    return D[u] + D[v] - 2*D[lca];
}

ll distanceW(int u, int v)//calculates distance between 2 nodes (weighted tree)
{
    int lca = LCA(u,v);
    return dist[u] + dist[v] - 2*dist[lca];
}

int main()
{
    ios::sync_with_stdio(0);
    int n,m;
    while(cin>>n && n)
    {
        nxtChain = 1;
        for(int i=1; i<=n; i++)
            G[i].clear(),dist[i]=0;

        for(int i=2,u,w; i<=n; i++)
        {
            cin>>u>>w;
            G[u+1].push_back({i,w});
            G[i].push_back({u+1,w});
        }

        dfs(1);
        HLD(1,-1);

        cin>>m;

        while(m--)
        {
            int u,v;
            cin>>u>>v;
            //cout<<u+1<<" "<<v+1<<" "<<LCA(u+1,v+1)<<"\n";
            cout<<distanceW(u+1,v+1)<<(m==0 ? "\n" : " ");
        }
    }
}
