/* 
* Here`s V - adj list represented graph, all other arrays are initially all 0 | empty
* if graph is not connected you need to call this for each connected subgraph separately
* All Bridges of current Subgraph are in bridges array after execution
* IF there`s a bridge between nodes u and v it`s stored as minIndex(u,v) and maxIndex(u,v) pair
*/

void DFS(vector<int>V[],vector<int>&parent, int low[],int disc[],bool visited[],vector<pair<int,int>>&bridges,int c)
{
    static int time = 0;
    low[c]=disc[c]=time++;
    visited[c]=1;

    for(int i=0; i<V[c].size(); i++)
        if(!visited[V[c][i]])
        {
            parent[V[c][i]]=c;
            DFS(V,parent,low,disc,visited,bridges,V[c][i]);

            if(disc[c] < low[V[c][i]])
                bridges.push_back(make_pair(min(c,V[c][i]),max(c,V[c][i])));
            else
                low[c]=min(low[c],low[V[c][i]]);
        }
        else if(parent[c]!=V[c][i])
            low[c]=min(low[c],disc[V[c][i]]);
}
