/* 
* Here`s V - adj list represented graph, all other arrays are initially all 0 | empty
* if graph is not connected you need to call this for each connected subgraph separately
* All articulation points of current Subgraph are in AP array after execution
*/

void DFS(vector<int>V[],vector<int>&parent,int disc[], int low[],vector<int>&AP, int c)
{
    static int time = 1;
    int childs = 0;
    disc[c]=low[c]=time++;
    bool isAP = false;

    for(int j=0; j<V[c].size(); j++)
    {
        if(V[c][j]==parent[c])continue;
        if(disc[V[c][j]]==0)
        {
            parent[V[c][j]]=c;
            childs++;
            DFS(V,parent,disc,low,AP,V[c][j]);

            if(disc[c] <= low[V[c][j]]) // change <= to < for bridges
                isAP=true;
            else
                low[c]=min(low[c],low[V[c][j]]);
        }
        else low[c]=min(low[c],disc[V[c][j]]);
    }

    if((parent[c]!=-1 && isAP) || (parent[c]==-1 && childs > 1))
        AP.push_back(c);
}
