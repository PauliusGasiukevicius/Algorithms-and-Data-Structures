#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 1234567890

const int N = 3001; //nodes in flow network
vector<int>from(N),edge(N),sp(N),inQueue(N); //helper arrays for Edmond-Karp, cause memory allocations are expensive

//graph contains {to, flow, capacity, reverseEdgeId, costPerFlowUnit}
void add_edge(vector<vector<array<int,5>>>&g, int u, int v, int cap, int cost)
{
    int ru = g[u].size();
    int rv = g[v].size();

    g[u].push_back({v,0,cap,rv,cost});
    g[v].push_back({u,0,0,ru,-cost});
}

//Finds max flow with minimum cost, uses SPF modification, worst case O(n^2 * m^2)
array<ll,2> min_cost_max_flow(vector<vector<array<int,5>>>&g, int source, int sink)
{
    ll mf  = 0; //max_flow
    ll mfc = 0; //max_flow_cost

    while(1)
    {
        fill(from.begin(),from.end(),-1);
        fill(edge.begin(),edge.end(),-1);
        fill(sp.begin(),sp.end(),oo);
        fill(inQueue.begin(),inQueue.end(),0);
        queue<int>q;

        /*Shortest-Path-Faster*/
        sp[source]=0;
        inQueue[source]=1;
        q.push(source);

        while(!q.empty())
        {
            int c = q.front();
            q.pop();
            inQueue[c]=0;

            for(int j=0; j<g[c].size(); j++)
            {
                auto&e = g[c][j];
                if(sp[e[0]] > sp[c] + e[4] && e[1] < e[2])
                {
                    sp[e[0]]=sp[c]+e[4];
                    from[e[0]]=c;
                    edge[e[0]]=j;

                    if(!inQueue[e[0]])
                        {
                            q.push(e[0]);
                            inQueue[e[0]]=1;
                        }
                }
            }
        }

        if(sp[sink]>=oo)break; //no way to reach sink anymore

        vector<int>path;
        vector<int>E;
        int c = sink;

        while(c!=-1)path.push_back(c),E.push_back(edge[c]),c=from[c];

        reverse(path.begin(),path.end());
        reverse(E.begin(),E.end());

        int flow = oo;

        for(int i=1; i<path.size(); i++)
            flow=min(flow,g[path[i-1]][E[i]][2] - g[path[i-1]][E[i]][1]);

        for(int i=1; i<path.size(); i++)
            {
                auto&e = g[path[i-1]][E[i]];
                mfc+=e[4]*flow;
                e[1]+=flow;
                g[e[0]][e[3]][1]-=flow;
            }

        mf+=flow;
    }

    return {mf, mfc};
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    vector<vector<array<int,5>>>g(N);
    int source = 0, sink = 1, nxt = 2;

    int n;
    string t;
    cin>>t>>n;

    vector<int>cnt(256);
    for(auto&ch:t)cnt[ch]++;

    for(int i='a'; i<='z'; i++)
        add_edge(g,source,nxt++,cnt[i],0);

    vector<string>words(n);
    vector<int>limits(n);

    for(int i=0; i<n; i++)
        {
            cin>>words[i]>>limits[i];
            fill(cnt.begin(),cnt.end(),0);
            for(auto&ch:words[i])cnt[ch]++;

            int idOfWordNode = nxt++;

            add_edge(g,idOfWordNode, sink, limits[i], i+1);

            for(int i='a'; i<='z'; i++)
            if(cnt[i])
            {
                add_edge(g,i-'a'+2,nxt++,cnt[i],0);
                add_edge(g,nxt-1,idOfWordNode,cnt[i],0);
            }
        }

    array<ll,2>mcf = min_cost_max_flow(g, source, sink);
    if(mcf[0] < t.size())cout<<"-1\n";
    else cout<<mcf[1];
}
