#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

int A[2001][2001]; //[node][v] - id of edge that connects node with other node with color v
int color[2001][2001];
int edge[2001][2001];
vector<array<int,3>>E;

void dfs(int u, int v, int c1, int c2)
{
    if(!A[u][c1] && !A[v][c1])//we can color current edge by c1
    {
        //cout<<"No more conflicts found, terminating at "<<u<<" "<<v<<"\n";
        int col = color[u][v];
        int ee = edge[u][v];
        if(A[v][col]==ee)A[v][col]=0;
        if(A[u][col]==ee)A[u][col]=0;

        A[u][c1]=A[v][c1]=ee;
        E[ee][2]=c1;
        color[u][v]=color[v][u]=c1;
        return;
    }

    int conflictingEdge = A[v][c1];
    int other = E[conflictingEdge][0]^v^E[conflictingEdge][1];
    int col = color[u][v];
    int ee = edge[u][v];
    if(A[v][col]==ee)A[v][col]=0;//erase current color
    if(A[u][col]==ee)A[u][col]=0;
    A[u][c1]=A[v][c1]=ee; //color as needed
    E[ee][2]=c1;
    color[u][v]=color[v][u]=c1;

    //cout<<"Edge "<<u<<" "<<v<<" still bad\n";
    dfs(v,other,c2,c1); //we keep alternating colors and because graph is bipartite, it can only have
    // even degree cycles - which can be bi-colored, hence in the worst case we will just 'rotate' whole cycle
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    int a,b,m;
    cin>>a>>b>>m;
    E.push_back({0,0,0});
    int mx = 0;
    while(m--)
    {
        int u,v;
        cin>>u>>v;
        v+=a;
        E.push_back({u,v,0});
        edge[u][v]=edge[v][u]=E.size()-1;
    }

    for(int i=1; i<E.size(); i++)
    {
        int c1 = 1, c2 = 1;
        int u = E[i][0], v = E[i][1];
        while(A[u][c1])c1++;
        while(A[v][c2])c2++;
        mx=max({mx,c1,c2});

        if(c1==c2)
        {
            E[i][2]=c1;
            A[u][c1]=i;
            A[v][c1]=i;
            color[u][v]=color[v][u]=c1;
        }
        else
            dfs(u,v,c1,c2);
    }

    cout<<mx<<"\n";
    for(int i=1; i<E.size(); i++)
        cout<<E[i][2]<<" ";
}
