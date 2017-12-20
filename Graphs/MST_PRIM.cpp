int total = 0;
vector<vector<pair<int,int>>>V(n,vector<pair<int,int>>());
//all edges are {cost,toVertex}
for(int i=0; i<m; i++)
{
int a,b,c;
cin>>a>>b>>c;
total+=c;
V[a].push_back({c,b});
V[b].push_back({c,a});
}
priority_queue<pair<int,int>, vector<pair<int,int>>,
greater<pair<int,int>>>q;
//min heap that stores [cost,node]
q.push({0,0});
// if graph is not connected, we need to use cycle and try building
MST after every unvisited node insertion
bool visited[200001]={0};
while(!q.empty() && n>0)
{
//we choose to connect with edge that costs the least
int cost = q.top().first;
int c = q.top().second;
q.pop();
if(visited[c])continue;
visited[c]=1;
n--;
total-=cost;
//we also add all neighbouring nodes with costs into our heap
for(int i=0; i<V[c].size(); i++)
if(!visited[V[c][i].second])
q.push(V[c][i]);
}
