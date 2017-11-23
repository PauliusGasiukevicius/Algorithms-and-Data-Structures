/*
* Uses Both Path compression and Union by rank
* P vector should initially be initialized to -1 for all disjoint sets at the beggining
*/

int Find(vector<int>&P, int u)
{return (P[u] < 0 ? u : P[u] = Find(P,P[u]));}

void Union(vector<int>&P, int u, int v)
{
    if((u=Find(P,u)) == (v=Find(P,v)))return;

    if(P[u] > P[v])swap(u,v);

    P[u]+=P[v];
    P[v]=u;
}
