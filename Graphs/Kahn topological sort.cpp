vector<int>V[101];
int out[101]={0}; //vertex out degree ( this sorts putting late tasks
first, use in degree for opposite effect )
for(int i=0; i<m; i++)
{
int a,b;
cin>>a>>b;
V[b].push_back(a); //note cause we use out degree we need to
reverse all edges!!!
out[a]++; // update out degress cause of edge a->b
}
stack<int>s; // you can use priority queues if you need
lexixographically smallest/largest sorting
//for labeling use greedy (i.e. for smallest labelling
mark latest tasks with largest label)
for(int i=1; i<=n; i++)
if(out[i]==0) // put all nodes with out degree of 0 into our
container
s.push(i);
while(!s.empty())
{
int cur = s.top();
s.pop();
for(int i=0; i<V[cur].size();i++) //reduce all out degrees of
all nodes coming into this one
if(--out[V[cur][i]]==0) //and if it hits zero we can add
it into our container
s.push(V[cur][i]);
} // we can store/print/use/etc our topological ordering
