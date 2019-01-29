#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

const int N = 100001;
int chain[N],head[N],P[N],D[N],sz[N],segID[N],nxtChain=1,nxt=1,n;
int E[N][3];//edges
int seg[4*N];
vector<int>G[N];

int dfs(int c)//sets node parents, depths, subtree sizes
{
    sz[c]=1;
    for(auto& u : G[c])
        if(u!=P[c])
        {
            P[u]=c;  //parent of node
            D[u]=D[c]+1; //depth of node
            sz[c]+=dfs(u); //subtree size of node
        }

    return sz[c];
}

void HLD(int c, int id)//Heavy-Light Decomposition, set id to -1 to start a new chain
{
    segID[c]=nxt++;
    if(id<0)
    {
        id=nxtChain++;
        chain[c]=id;
        head[id]=c;
    }
    chain[c]=id;

    if(G[c].empty() || (G[c].size()==1 && G[c][0]==P[c]))return; //leaf, so we`re done

    int mx = (P[c]==G[c][0] ? G[c][1] : G[c][0]);//index in adj list for heaviest child

    for(auto& u : G[c])
        if(u!=P[c] && sz[u] > sz[mx])
        mx=u;

    HLD(mx,id);//Finish current chain

    for(auto& u : G[c])
        if(u!=P[c] && u!=mx)//for all other children, start next chains
        HLD(u,-1);
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

void update(int c, int l, int r, int pos, ll val)//updates segment tree
{
    if(l==r)
    {
        seg[c]=val;
        return;
    }
    int m = (l+r)/2;
    if(pos<=m)
        update(2*c,l,m,pos,val);
    else update(2*c+1,m+1,r,pos,val);

    seg[c]=(seg[2*c] >= seg[2*c+1] ? seg[2*c] : seg[2*c+1]);
}

int RMaxQ(int c, int l, int r, int L, int R)
{
    if(l>r || l>R || r<L)return -oo;
    if(l>=L && r<=R)
        return seg[c];

    int m = (l+r)/2;
    return max(RMaxQ(2*c,l,m,L,R), RMaxQ(2*c+1,m+1,r,L,R));
}

int up(int u, int v)//v should be ancestor of u
{
    int ats = -oo;
    while(chain[u]!=chain[v])
    {
        int c = RMaxQ(1,1,n,segID[head[chain[u]]],segID[u]);
        ats=max(c,ats);
        u=P[head[chain[u]]];
    }
    int c = RMaxQ(1,1,n,segID[v]+1,segID[u]);
    ats=max(ats,c);
        //cout<<v<<" "<<u<<" "<<segID[v]<<" "<<segID[u]<<" "<<ats<<"\n";
    return ats;
}

int Query(int u, int v)
{
    /*Path from u-->v can be decomposed to paths:
    u-->lca(u,v)-->v
    while moving to lca we can update answer with each chain piece*/
    int lca = LCA(u,v);
    return max(up(u,lca),up(v,lca));
}

int main()
{
    //ios::sync_with_stdio(0);
    int t;
    scanf("%d",&t);

    while(t--)
    {
        nxtChain=1;
        nxt=1;
        scanf("%d",&n);

        //fill(seg, seg+4*n, LLONG_MIN);//cleans segment tree
        for(int i=1; i<=n; i++)
            G[i].clear();

        for(int i=0; i+1<n; i++)
        {
            int u,v,w;
            scanf("%d %d %d",&u,&v,&w);
            G[u].push_back(v);
            G[v].push_back(u);
            E[i][0]=u,E[i][1]=v,E[i][2]=w;
        }
        dfs(1);
        HLD(1,-1);
        /*
        Nodes are easier to work with, so we can change all edges to nodes
        Edge (u,v) is node u (if D[u] > D[v]) else v
        */

        for(int i=0; i+1<n; i++)
        {
            int u = E[i][0];
            int v = E[i][1];
            if(D[u] < D[v])swap(u,v);
            update(1,1,n,segID[u],E[i][2]);
        }

        char s[20];
        while(1)
        {
            scanf("%s",s);
            if(s[0]=='D')break;

            if(s[0]=='Q')
        {
            int u,v;
            scanf("%d %d",&u,&v);
            //cout<<Query(u,v)<<"\n";
            printf("%d\n",Query(u,v));
        }
        else
        {
            int i,cost;
            scanf("%d %d",&i,&cost);
            int u = E[i-1][0];
            int v = E[i-1][1];
            if(D[u] < D[v])swap(u,v);
            update(1,1,n,segID[u],cost);
        }
        }
    }
}
