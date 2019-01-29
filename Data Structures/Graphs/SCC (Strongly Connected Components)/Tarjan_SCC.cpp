/* 
* Here`s V - adj list represented graph, all other arrays are initially all 0 | empty
* if graph is not connected you need to call this for each connected subgraph separately
* All strongly Connected Components of current Subgraph are in SCC array after execution 
*/

void DFS(vector<int>V[], int low[], int disc[], bool inStack[], stack<int>&s, int c, vector<vector<int>>&SCC)
{
    static int time = 1;
    disc[c]=low[c]=time++;
    inStack[c]=1;
    s.push(c);

    for(int i=0; i<V[c].size(); i++)
        if(disc[V[c][i]]==0)
    {
        DFS(V,low,disc,inStack,s,V[c][i],SCC);
        low[c]=min(low[c],low[V[c][i]]);
    }
    else if(inStack[V[c][i]])
    low[c]=min(low[c],disc[V[c][i]]);

    if(disc[c]==low[c])
    {
        vector<int>comp;
        while(1)
        {
            int cur = s.top();
            s.pop();
            inStack[cur]=0;
            comp.push_back(cur);
            if(cur==c)break;
        }
        SCC.push_back(comp);
    }
} 
