struct CentroidDecomposition
{
    int N,root,logN;
    vector<vector<int>>g; //initial tree, gotta add edges with add_edge
    vector<vector<ll>>w; //weights for edges, if unweighted pass 1 while adding edge
    vector<vector<int>>tree; //resulting centroid decomposition tree
    vector<int>dead; //marks nodes dead
    vector<int>sz; //stores subtree sizes
    vector<int>IN; //euler tour time node was first visited
    vector<int>OUT;//euler tour time node was last visited
    vector<int>P; //parent of centroid tree node
    vector<ll>depth; //depth/distance in original tree from root to other nodes
    vector<vector<int>>up; //sparse table for lca

    CentroidDecomposition(int n){
        int tmp = n+1;
        N=n+1,root=-1,logN=0;
        while(tmp > 0)logN++,tmp/=2;

        g.resize(N);
        w.resize(N);
        tree.resize(N);
        dead.resize(N);
        sz.resize(N);
        IN.resize(N);
        OUT.resize(N);
        P.resize(N);
        depth.resize(N);
        up.resize(N);
        for(int i=0; i<N; i++)
            up[i].resize(logN+1);
    }

    void add_edge(int u, int v, int weight){
        g[u].push_back(v);
        w[u].push_back(weight);
        g[v].push_back(u);
        w[v].push_back(weight);
    }

    bool isAncestor(int u, int v){return IN[u]<=IN[v] && OUT[u]>=OUT[v];}

    int LCA(int u, int v){
        if(isAncestor(u,v))return u;
        if(isAncestor(v,u))return v;

        for(int i=logN; i>=0; i--)
            if(!isAncestor(up[u][i],v))
            u=up[u][i];

        return up[u][0];
    }

    ll dist(int u, int v){return depth[u] + depth[v] - 2LL*depth[LCA(u,v)];}

    int dfs(int c, int p = 0){
        sz[c]=1;
        for(auto&u:g[c])
            if(u!=p && !dead[u])
            sz[c]+=dfs(u,c);
        return sz[c];
    }

    void dfs2(int c, int p, ll d = 0){
        static int tm = 1;
        IN[c] = ++tm;

        up[c][0]=p;
        for(int j=1; j<=logN; j++)
            up[c][j]=up[up[c][j-1]][j-1];

        depth[c]=d;
        for(int i=0; i<g[c].size(); i++)
            if(g[c][i] != p)
            dfs2(g[c][i],c,d+w[c][i]);

        OUT[c] = ++tm;
    }

    int FindCentroid(int c, int n, int p = 0){
        for(auto&u:g[c])
            if(u!=p && !dead[u] && sz[u] > n/2)
            return FindCentroid(u,n,c);
        return c;
    }

    int BuildCentroidTree(int c=1, int level = 1)
    {
        dfs(c);
        if(level==1)root = c = FindCentroid(c,sz[c]);
        else c = FindCentroid(c,sz[c]);

        dead[c]=level; //mark current node as dead
        for(auto&u:g[c])//build centroid tree for all other subtrees
        if(!dead[u])
        {
            int v = BuildCentroidTree(u,level+1);
            tree[c].push_back(v);
            tree[v].push_back(c);
            //cout<<c<<" --> "<<v<<" \n";
            P[v]=c;
        }

        if(level==1)dfs2(root,root);
        return c;
    }
};

CentroidDecomposition cd(100001);
vector<array<ll,3>>S[100001]; //{dist, color}

void Update(int c, ll dist, int color)
{
    static int updateID = 1;
    int st = c;

    while(c > 0)
    {
        ll distToC = dist - cd.dist(st, c);

        if(distToC >= 0)
        {
            while(!S[c].empty() && S[c].back()[0] <= distToC)
                S[c].pop_back();

            S[c].push_back({distToC,color,updateID++});
        }

        //cout<<c<<" "<<dist<<" "<<color<<" "<<updateID-1<<" <<<<<<<<<\n";
        c = cd.P[c];
    }
}

int Query(int c)
{
    int st = c;
    int color = 0;
    int latestUpdate = 0;

    while(c > 0)
    {
        ll distToC = cd.dist(st,c);

        if(!S[c].empty() && S[c][0][0] >= distToC) //if some coloring is saved here
        {
            int l = 0, r = S[c].size()-1;
            while(l < r)
            {
                int m = (l+r+1)/2;
                if(S[c][m][0] >= distToC)
                    l=m;
                else r = m-1;
            }

            if(S[c][r][2] > latestUpdate)
            {
                latestUpdate = S[c][r][2];
                color = S[c][r][1];
            }
        }

        c = cd.P[c];
    }
    return color;
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n,q;
    cin>>n;

    for(int i=1; i<n; i++)
    {
        int u,v,w=1;
        cin>>u>>v>>w;
        cd.add_edge(u,v,w);
    }

    cd.BuildCentroidTree();

    cin>>q;
    while(q--)
    {
        int type,c,d,col;
        cin>>type>>c;

        if(type==1)cin>>d>>col,Update(c,d,col);
        else cout<<Query(c)<<"\n";
    }
}
