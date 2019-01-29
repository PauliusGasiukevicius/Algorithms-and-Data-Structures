#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

int Find(vector<int>&P, int u)
{
    return P[u] < 0 ? u : P[u] = Find(P,P[u]);
}

void Union(vector<int>&P, int u, int v)
{
    u = Find(P,u);
    v = Find(P,v);
    if(u!=v)P[v]=u;
}

//Directed Minimum Spanning Tree
//weight returned is ok, set of edges nope :/
int DMST(vector<array<int,3>>E, int n, int root, vector<int>&edgeUsed)
{
 vector<int>cost(n),P(n,-1),prev(n),v(n),changed(n),prevEdges;
  int ret = 0;

  while(1)
    {
   fill(cost.begin(),cost.begin()+n,oo);
   fill(changed.begin(),changed.begin()+n,-1);
   prevEdges = edgeUsed; //copy previously used edges

    for(int i=0; i<E.size(); i++)
    {
      auto&e = E[i];
      int u = Find(P,e[0]);
      int v = Find(P,e[1]);
      if (v!=root && u!=v && e[2] < cost[v])
      {
          if(changed[v]!=-1)
          edgeUsed[changed[v]]=prevEdges[changed[v]];

          changed[v]=e[1];
          cost[v] = e[2], prev[v] = u, edgeUsed[e[1]]=i+1;
      }
    }

    cost[Find(P,root)] = 0;
    for(int i=0; i<n; i++)
        if(P[i] < 0)
    {
        if(cost[i]>=oo)return -1;
        ret+=cost[i];
    }
    //cout<<ret<<" <-\n";
    fill(v.begin(),v.begin()+n,-1);

    //re-weight edges
    for (auto &e : E)
    {
      int u = Find(P,e[0]);
      int v = Find(P,e[1]);
      if (u != v) e[2] -= cost[v];
    }

    bool cycle = 0;

    for(int i=0; i<n; i++)
        if(P[i] < 0)
    {
      int x = i;
      for (; x != root && v[x] == -1; x = prev[x])//goes up the from pointers
        v[x] = i;

      if (x != root && v[x] == i) //if it`s not at root and not already visited we found new cycle
        {
            int y = prev[x];
            for (y; y!=x; y = prev[y])//because it`s cycle we can keep following pointers
            Union(P,x,y),cycle=1;
        }
    }

    if(!cycle)break;
    root=Find(P,root);
  }
    return ret;
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    int t,n,m,cs=1;
    cin>>t;
    while(t--)
    {
        cin>>n>>m;
        vector<array<int,3>>E(m);
        vector<int>used(n);

        for(auto&e:E)
            cin>>e[0]>>e[1]>>e[2];

        int ans = DMST(E,n,0,used);

        //cout<<"Edges of DMST: \n";
        int sum = 0;
        for(int i=0; i<n; i++)
            if(used[i])
        {
            auto&e = E[used[i]-1];
            //cout<<used[i]<<" "<<e[0]<<" "<<e[1]<<" "<<e[2]<<"\n";
            sum+=e[2];
        }

        if(ans<0)cout<<"Case #"<<cs++<<": Possums!\n";
        else cout<<"Case #"<<cs++<<": "<<ans<<"\n";
    }
}
