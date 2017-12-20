bool DFS(vector<vector<int>>&V, bool visited[], bool explored[], int c)
{
    visited[c]=1;
    bool cycle = false;

    for(int i=0; i<V[c].size(); i++)
        if(!visited[V[c][i]])
        cycle |=DFS(V,visited,explored,V[c][i]);
        else if(!explored[V[c][i]])cycle=true;
    explored[c]=1;

    return cycle;
}
