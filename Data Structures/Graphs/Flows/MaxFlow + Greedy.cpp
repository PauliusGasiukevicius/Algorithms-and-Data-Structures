#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

int Edmond(vector<vector<int>>&M, vector<int>G[], int st, int en)
{
    int mf = 0;

    while(1)
    {
        vector<int>P(en+1,-1),visited(en+1);
        visited[st]=1;
        queue<int>q;
        q.push(st);

        while(!q.empty() && q.front()!=en)
        {
            int c = q.front();
            q.pop();

            for(auto&u:G[c])
                if(!visited[u] && M[c][u] > 0)
                visited[u]=1,q.push(u),P[u]=c;
        }
        if(q.empty())return mf;
        int f = oo;
        int c = en;
        vector<int>path;
        while(c!=-1)
            path.push_back(c),c=P[c];
        reverse(path.begin(),path.end());

        for(int i=1; i<path.size(); i++)
            f=min(f,M[path[i-1]][path[i]]);

        for(int i=1; i<path.size(); i++)
            M[path[i-1]][path[i]]-=f,M[path[i]][path[i-1]]+=f;
        mf+=f;
    }
}

int main()
{
    ios::sync_with_stdio(0);
    int t,n,m,d;
    cin>>t;

    for(int cs=1; cs<=t; cs++)
    {
        cin>>n>>d>>m;
        vector<int>G[333];
        int en = 332, total = 0;

        vector<vector<int>>E(m,vector<int>(5));//cost,from,to,cap,day
        vector<vector<int>>M(333,vector<int>(333));
        for(int i=0; i<m; i++)
            cin>>E[i][1]>>E[i][2]>>E[i][3]>>E[i][0]>>E[i][4];
        sort(E.begin(),E.end());

        for(int i=1; i<=n; i++)
        {
            int w;
            cin>>w;
            total+=w;
            G[0].push_back(i);
            G[i].push_back(0);
            M[0][i]=w;

            for(int di=1; di<=d; di++)
            {
                G[i+di*n-n].push_back(i+di*n);
                G[i+di*n].push_back(i+di*n-n);
                M[i+di*n-n][i+di*n]=oo;
            }
        }
        G[n+d*n].push_back(en);
        G[en].push_back(n+d*n);
        M[n+d*n][en]=oo;

        int mf = Edmond(M,G,0,en);
        int pos = 0;
        while(mf < total && pos < m)
        {
            int cost = E[pos][0];
            int from = E[pos][1];
            int to = E[pos][2];
            int cap = E[pos][3];
            int day = E[pos][4];
            G[from+n*day].push_back(to+n*day+n);
            G[to+n*day+n].push_back(from+n*day);
            M[from+n*day][to+n*day+n]=cap;
            mf+=Edmond(M,G,0,en);
            pos++;
        }

        if(mf==total)
            cout<<"Case #"<<cs<<": "<<E[pos-1][0]<<"\n";
        else
            cout<<"Case #"<<cs<<": Impossible\n";
    }
}
