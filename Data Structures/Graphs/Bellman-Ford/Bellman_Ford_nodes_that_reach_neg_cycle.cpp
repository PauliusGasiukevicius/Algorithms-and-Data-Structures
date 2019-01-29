#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main()
{
    ios::sync_with_stdio(0);
    int t,n,m,cs=1;
    cin>>t;

    while(t--)
    {
        cin>>n>>m;
        int from[2001]={};
        int to[2001]={};
        int w[2001]={};
        vector<int>SP(n+1,666666666);
        vector<int>R[1001];

        //note: input is actually from[i], to[i], w[i], we reverse the edges, cause it does not affect the neg cycles
        //but it helps us to find the nodes that lead to neg cycles instead of nodes that are reachable from neg cycle
        for(int i=0; i<m; i++)
            cin>>to[i]>>from[i]>>w[i],R[from[i]].push_back(to[i]);

        for(int i=0; i<n; i++)
            for(int j=0; j<m; j++)
                if(SP[to[j]] > SP[from[j]]+w[j])
                    SP[to[j]]=SP[from[j]]+w[j];

        set<int>ats;
        queue<int>q;
        bitset<1001>visited(0);

        for(int j=0; j<m; j++)
                if(SP[to[j]] > SP[from[j]]+w[j])
                    q.push(from[j]),q.push(to[j]),visited[from[j]]=visited[to[j]]=1;

        while(!q.empty()) //finds all nodes that can reach any of negative cycles
        {
            int c = q.front();
            q.pop();
            ats.insert(c);

            for(int&u:R[c])
                if(!visited[u])visited[u]=1,q.push(u);
        }


        cout<<"Case "<<cs++<<":";
        if(ats.empty())
            cout<<" impossible\n";
        else
        {
            for(int x : ats)
                cout<<" "<<x;
            cout<<"\n";
        }
    }
}
