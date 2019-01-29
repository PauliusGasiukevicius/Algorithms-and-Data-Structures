#include <bits/stdc++.h>
using namespace std;
#define ll long long
/*LCA with root queries trick

Let LCA(u, v, w) be the LCA of v and w with respect to root u. To compute LCA(u, v, w), we can compute, for any fixed r,

LCA(r, u, v)
LCA(r, u, w)
LCA(r, v, w)

and take the "odd man out", i.e., if two are equal and the third is different, then take the third, else they're all equal, so take that node.

*/
void dfs(int c,int p, vector<int>&euler,vector<int>&first, vector<int>T[])
{
    euler.push_back(c);
    first[c]=euler.size();

    for(int&u : T[c])
        if(u!=p)
        {
            dfs(u,c,euler,first,T);
            euler.push_back(c);//cause we will reach this node after climbing the tree
        }
}
//*********************************************************************************
//This part below is wrong, instead of using node id for comparision, i should be using node depth from root!!!!!
//*********************************************************************************

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
    seg[c]=min(seg[2*c],seg[2*c+1]);
}

int query(int seg[],int c, int l, int r, int L, int R)
{
    if(r<l || l>R || r<L)return INT_MAX;

    if(l>=L && r<=R)return seg[c];
    int m = (l+r)/2;
    return min(query(seg,2*c,l,m,L,R),query(seg,2*c+1,m+1,r,L,R));
}

int main()
{
    ios::sync_with_stdio(0);
    int t,n,q,sz,x,u,v,cs=1;
    cin>>t;

    while(t--)
    {
        cin>>n;
        vector<int>first(n+1);
        vector<int>euler;
        vector<int>T[n+1];

        for(int i=1; i<=n; i++)
        {
            cin>>sz;
            while(sz--)
                cin>>x,T[i].push_back(x),T[x].push_back(i);
        }

        dfs(1,-1,euler,first,T);
        int seg[8001]={};
        build(seg,1,1,euler.size(),euler);

        cin>>q;
        cout<<"Case "<<cs++<<":\n";
        while(q--)
        {
            cin>>u>>v;
            cout<<query(seg,1,1,euler.size(),min(first[u],first[v]),max(first[u],first[v]))<<"\n";
        }
    }
}
