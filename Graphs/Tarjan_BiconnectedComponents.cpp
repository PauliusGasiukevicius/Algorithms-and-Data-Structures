int low[100001];
int disc[100001];
int P[100001];

void DFS(int c, vector<int>G[], vector<vector<vector<int>>>&BC, stack<vector<int>>&S)
{
    static int tm = 1;
    disc[c]=low[c]=tm++;

    for(int&u:G[c])
        if(u!=P[c])
    {
        S.push({c,u});

    if(disc[u]==0)
    {
        P[u]=c;
        DFS(u,G,BC,S);
        low[c]=min(low[c],low[u]);
    }
    else if(u!=P[c])
        low[c]=min(disc[u],low[c]);

        if(low[u] >= disc[c])
        {
            vector<vector<int>>B;
            vector<int>e = {c,u};
            vector<int>e2 = {u,c};
            while(S.top()!=e && S.top()!=e2)
                B.push_back(S.top()),S.pop();
            B.push_back(S.top());
            S.pop();
            BC.push_back(B);
        }
    }
}