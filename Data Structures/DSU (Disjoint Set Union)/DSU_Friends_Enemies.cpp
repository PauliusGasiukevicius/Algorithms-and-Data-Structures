#include <bits/stdc++.h>
using namespace std;
#define ll long long

int P[10001];
int E[10001];

int Find(int x)
{
    return (P[x]<0 ? x : P[x]=Find(P[x]));
}

int Union(int u, int v) //now return the new root
{
    if((u=Find(u))==(v=Find(v)))return u;
    if(P[u] > P[v])swap(u,v);
    P[u]+=P[v];
    P[v]=u;
    return u;
}


int main()
{
    ios::sync_with_stdio(0);
    int n,o,x,y;
    cin>>n;
    for(int i=0; i<=n; i++)P[i]=E[i]= -1;

    while(cin>>o>>x>>y && o!=0)
    {
        x=Find(x);
        y=Find(y);

        if(o==1)
        {
            if(E[x]==y)
                cout<<"-1\n";
            else if(E[x]==-1 && E[y]==-1)
                Union(x,y);
            else if(E[x]==-1)
                E[x]=E[y],Union(x,y);
            else if(E[y]==-1)
                E[y]=E[x],Union(x,y);
            else
                E[Union(E[x],E[y])]=Union(x,y),E[Find(x)]=Find(E[x]);
        }
        else if(o==2)
        {
            if(x==y)cout<<"-1\n";
            else if(E[x]==-1 && E[y]==-1)
                E[x]=y,E[y]=x;
            else if(E[x]==-1)
                Union(x,E[y]),x=Find(x),E[x]=y,E[y]=x;
            else if(E[y]==-1)
                Union(y,E[x]),y=Find(y),E[x]=y,E[y]=x;
            else
                Union(x,E[y]),Union(y,E[x]),x=Find(x),y=Find(y),E[x]=y,E[y]=x;
        }
        else if(o==3)
            cout<<(x==y ? "1\n" : "0\n");
        else
            cout<<(E[x]==y ? "1\n" : "0\n");
    }
}
