#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

#define N 100001
#define LOGN 20
int root; //this will become first centroid of the tree after decomposing input tree
vector<int>G[N]; //input tree
vector<int>T[N]; //centroid tree
int centroid[N]; //marks used nodes
int P[LOGN][N]; //parent, has LOGN dimension for all centroid levels
int closestRed[N]; //distance to closest red node in centroid tree
int sz[LOGN][N]; //subtree size, has LOGN dimension for all centroid levels
int parent[N]; // parents for centroid tree
int parentInput[N];
int depth[N]; // depths of original tree rooted at first centroid
int centroidTreeDepth[N]; // depths of centroid tree rooted at first centroid
//all this stuff uses like 60*N memory :/
int seg[8*N];
vector<int>first(N);
vector<int>euler;

void dfs(int c,int p, vector<int>&euler,vector<int>&first, vector<int>G[])
{
    euler.push_back(c);
    first[c]=euler.size();

    for(int&u : G[c])
        if(u!=p)
        {
            dfs(u,c,euler,first,G);
            euler.push_back(c);//cause we will reach this node after climbing the tree
        }
}

void build(int seg[], int c, int l, int r, vector<int>&euler)
{
    if(l==r)
    {
        seg[c]=euler[r-1];
        return;
    }

    int m = (l+r)/2;
    build(seg,2*c,l,m,euler);
    build(seg,2*c+1,m+1,r,euler);
    seg[c]=depth[seg[2*c]] < depth[seg[2*c+1]] ? seg[2*c] : seg[2*c+1];
}

int query(int seg[],int c, int l, int r, int L, int R)
{
    if(r<l || l>R || r<L)return INT_MAX;

    if(l>=L && r<=R)return seg[c];
    int m = (l+r)/2;
    int q1 = query(seg,2*c,l,m,L,R);
    int q2 = query(seg,2*c+1,m+1,r,L,R);
    if(max(q1,q2)==INT_MAX)return min(q1,q2);
    return (depth[q1] < depth[q2] ? q1 : q2);
}

void bfs(int c) //fills in depth[].
{//depth[i] - distance from root(first c) to node i on original tree
    vector<int>visited(N,0);
    visited[c]=1;
    depth[c]=0;
    queue<int>q;
    q.push(c);

    while(!q.empty())
    {
        int u = q.front();
        q.pop();

        for(auto&v:G[u])
            if(!visited[v])
            q.push(v),depth[v]=depth[u]+1,visited[v]=1,parentInput[v]=u;
    }
}

void bfs2(int c) //fills in centroidTreeDepth[].
{//centroidTreeDepth[i] - distance from root(first c) to node i on centroid tree
    vector<int>visited(N,0);
    visited[c]=1;
    centroidTreeDepth[c]=0;
    queue<int>q;
    q.push(c);

    while(!q.empty())
    {
        int u = q.front();
        q.pop();

        for(auto&v:T[u])
            if(!visited[v])
            q.push(v),centroidTreeDepth[v]=centroidTreeDepth[u]+1,visited[v]=1;
    }
}

void dfs(int c, int L) //gets subtree sizes calculated for tree (without centroids)
{//L - level of centroid tree
    sz[L][c]=1;
    for(auto&u:G[c])
        if(u!=P[L][c] && !centroid[u])
        P[L][u]=c,dfs(u,L),sz[L][c]+=sz[L][u];
}

void decompose(int c, int nodes, int p, int L) //decomposes current tree into centroid tree
{
    dfs(c,L);
    while(1)
    {
    int cand = c;
    int mx = 1;

    for(auto&u:G[c])
        if(!centroid[u])
    {
        if(P[L][c]!=u && sz[L][u] >= mx)mx=sz[L][u],cand=u;
        else if(nodes-sz[L][c] >= mx)mx=nodes-sz[L][c],cand=u;
    }

    if(mx*2 <= nodes || nodes<=1) //if we found a centroid
    {
        centroid[c]=1;
        if(p)//if this node is not root, update centroid tree
            T[p].push_back(c),T[c].push_back(p),parent[c]=p;
        else root=c;
        break;
    }
    else c=cand; // go to the subtree that has centroid
    }

    if(nodes<=1)return;

    for(auto&u:G[c])
        if(!centroid[u] && u!=P[L][c])decompose(u,sz[L][u],c,L+1);
        else if(!centroid[u])decompose(u,nodes-sz[L][c],c,L+1);
}

int LCA_T(int u, int v) //finds LCA in centroid tree of centroids u and v
{//because of nature of centroid tree, takes O(log n) time
    while(u!=v)
    {
        if(centroidTreeDepth[u] > centroidTreeDepth[v])u=parent[u];
        else if(centroidTreeDepth[v] > centroidTreeDepth[u])v=parent[v];
        else u=parent[u],v=parent[v];
    }
    return u;
}

int LCA(int u, int v)
{//TODO find LCA of 2 nodes in original tree, rooted at first centroid
    return query(seg,1,1,euler.size(),min(first[u],first[v]), max(first[u],first[v]));
}

int Distance(int u, int v)
{//calculates distance between 2 nodes in O(log n) (uses LCA)
    return depth[u] + depth[v] - 2*depth[LCA(u,v)];
}

int CentroidDist(int u, int v)
{//because all paths from u to v will go through LCA_T(u,v), decomposes paths and gets Distance
    int lca = LCA_T(u,v);
    return Distance(u,lca) + Distance(v,lca);
}

void colorRed(int c)
{
    closestRed[c]=0;
    int u = c;
    while(parent[u])
    {
        u=parent[u]; // go up
        closestRed[u] = min(closestRed[u], CentroidDist(c,u));
    }
}

int query(int c)
{
    int ats = closestRed[c];
    int u = c;
    while(parent[u])
    {
        u=parent[u]; // go up
        ats = min(ats, CentroidDist(c,u) + closestRed[u]);
    }
    return ats;
}

int main()
{
    ios::sync_with_stdio(0);
    int n,m,type,v;
    cin>>n>>m;

    for(int i=1,u,v; i<n; i++)
        {
            cin>>u>>v;
            G[u].push_back(v),G[v].push_back(u);
        }
    decompose(1,n,0,0); //build centroid tree T, from input tree G
    bfs(root); //calculates depth for all nodes from root (Original tree)
    bfs2(root);//calculates depth for all nodes from root (Centroid tree)
    fill(closestRed, closestRed + N, oo); //sets initial distances to oo
    dfs(root,-1,euler,first,G);//gets euler tour of original tree from root
    build(seg,1,1,euler.size(),euler); //builds segment tree on euler tour, uses RMQ comparing depth
    colorRed(1);

    while(m--)
    {
        cin>>type>>v;
        if(type&1)colorRed(v);
        else cout<<query(v)<<"\n";
    }
}
