int dfs(vector<vector<int>>&g, vector<int>&v, vector<int>&A, int c)
{
    v[c]=1;
    int tt = 1;
    for(auto&u:g[c])
        if(!v[u])
        tt+=dfs(g,v,A,u);
    A.push_back(c);
    return tt;
}
 
int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n,m,nxt=0;
    cin>>n>>m;
    vector<vector<int>>g(n+1),rg(n+1);
    vector<int>v(n+1),A,SCC_ID(n+1),C(n+1);
    vector<ll>CC(n+1);
 
    for(int i=1; i<=n; i++)
        cin>>C[i];
 
    for(int i=1; i<=m; i++)
    {
        int u,v;
        cin>>u>>v;
        g[u].push_back(v);
        rg[v].push_back(u);
    }
 
    for(int i=1; i<=n; i++)
        if(!v[i])dfs(g,v,A,i);
 
    fill(v.begin(),v.end(),0);
 
    for(int i=A.size()-1; i>=0; i--)
        if(!v[A[i]])
        {
            vector<int>scc;
            dfs(rg,v,scc,A[i]);
            ++nxt;
            for(auto&x:scc)
                SCC_ID[x]=nxt,CC[nxt]+=C[x];
        }
 
    vector<vector<int>>G(nxt+1);
    vector<ll>IN(nxt+1),best(n+1);
    queue<int>q;
 
    for(int i=1; i<=n; i++)
        for(auto&u:g[i])
        if(SCC_ID[i] != SCC_ID[u])
            IN[SCC_ID[u]]++,G[SCC_ID[i]].push_back(SCC_ID[u]);
 
   for(int i=1; i<=nxt; i++)
    if(IN[i]==0)q.push(i);
 
   while(!q.empty())
   {
        int c = q.front();
        q.pop();
        best[c]+=CC[c];
 
        for(auto&u:G[c])
        {
            best[u]=max(best[u],best[c]);
            if(--IN[u]==0)q.push(u);
        }
   }
 
   cout<<*max_element(best.begin(),best.end());