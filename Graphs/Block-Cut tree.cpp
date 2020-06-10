#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 0x3f3f3f3f

vector<vector<int>> biconnected_components(vector<vector<int>> &adj, vector<int>&art)
{
    int n = adj.size();

    vector<int> num(n), low(n), stk;
    vector<vector<int>> comps;

    function<void(int, int, int&)> dfs = [&](int u, int p, int &t)
    {
        num[u] = low[u] = ++t;
        stk.push_back(u);

        for (int v : adj[u]) if (v != p)
        {
            if (!num[v])
            {
                dfs(v, u, t);
                low[u] = min(low[u], low[v]);

                if (low[v] >= num[u])
                {
                    art[u] = (num[u] > 1 || num[v] > 2);

                    comps.push_back({u});
                    while (comps.back().back() != v)
                        comps.back().push_back(stk.back()), stk.pop_back();
                }
            }
            else low[u] = min(low[u], num[v]);
        }
    };

    for (int u = 0, t; u < n; ++u)
        if (!num[u]) dfs(u, -1, t = 0);

    return comps;
}

void dfs2(int c, int p, vector<vector<int>>&g, vector<int>&in, vector<int>&out,
               vector<int>&depth, vector<vector<int>>&up)
{
    static int tm = 1;
    in[c]=tm++;
    depth[c] = (p==-1 ? 0 : depth[p] + 1);

    up[0][c] = p < 0 ? c : p;
    for(int j=1; j<up.size(); j++)
        up[j][c] = up[j-1][up[j-1][c]];

    for(auto&u:g[c])
        if(u!=p)
        dfs2(u,c,g,in,out,depth,up);
    out[c]=tm;
}

bool isAncestor(int u, int v, vector<int>&in, vector<int>&out)
{
    return in[u]<=in[v] && out[u]>=out[v];
}

int LCA(int u, int v, vector<int>&in, vector<int>&out, vector<vector<int>>&up)
{
    if(isAncestor(u,v,in,out))return u;
    if(isAncestor(v,u,in,out))return v;

    for(int j=up.size()-1; j>=0; j--)
        if(!isAncestor(up[j][u],v,in,out))
            u = up[j][u];

    return up[0][u];
}

int can(int a, int b, int c, vector<int>&bccId, vector<int>&depth, vector<int>&isAP,
        vector<int>&in, vector<int>&out,vector<vector<int>>&up)
{
    if(!isAP[c] && a!=c && b!=c)return 1;
    if(c == a || c == b)return 0;

    a = bccId[a];
    b = bccId[b];
    c = bccId[c];

    if(a==b )return 1;

    int lcaAB = LCA(a,b,in,out,up);
    int lcaAC = LCA(a,c,in,out,up);
    int lcaBC = LCA(b,c,in,out,up);

    int pathAB = depth[a] + depth[b] - 2*depth[lcaAB];
    int pathAC = depth[a] + depth[c] - 2*depth[lcaAC];
    int pathBC = depth[b] + depth[c] - 2*depth[lcaBC];

    if(pathAB != pathAC + pathBC)return 1;
    return 0;
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n,m,q;
    cin>>n>>m>>q;
    vector<vector<int>>g(n+1),bcc;
    vector<int>isAP(n+1);
    for(int i=0; i<m; i++)
    {
        int u,v;
        cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    bcc = biconnected_components(g,isAP);

    vector<vector<int>>blockCutTree(bcc.size()+1);
    vector<int>bccId(n+1);
    int nxtId = bcc.size()+1;
    for(int i=1; i<=n; i++)
        if(isAP[i])
        {
            blockCutTree.push_back({});
            bccId[i]=nxtId++;
        }

    for(int i=0; i<bcc.size(); i++)
        for(auto& u : bcc[i])
        if(isAP[u])
        {
            blockCutTree[bccId[u]].push_back(i+1);
            blockCutTree[i+1].push_back(bccId[u]);
        }else bccId[u]=i+1;

    int N = blockCutTree.size();

    vector<int>in(N),out(N),depth(N);
    const int lgN = log2(N)+1;
    vector<vector<int>>up(lgN,vector<int>(N));
    dfs2(1,-1,blockCutTree,in,out,depth, up);

    while(q--)
    {
        int a,b,c;
        cin>>a>>b>>c;

        if(can(a,b,c,bccId,depth,isAP,in,out,up))cout<<"YES\n";
        else cout<<"NO\n";
    }
}
