#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

bool valid(int r, int c, vector<string>&A)
{
    return r>=0 && c>=0 && r<A.size() && c<A[r].size() && A[r][c]!='x';
}

ll solve(vector<vector<ll>>&DP, int cur, int r, int c, vector<vector<int>>dist[21][21], ll visited, vector<pair<int,int>>&T)
{
    if(DP[cur][visited]!=-1)return DP[cur][visited];
    if(visited+1 == (1LL<<DP.size()))//if all visited
        return 0; //no need to go back, cause modified TSP, otherwise we would need dist[r][c][firstR][firstC]

    DP[cur][visited]=oo;
    for(int i=1; i<T.size(); i++)//choose next objective to reach
        if(((1<<i)&visited)==0)
    {
        ll w = dist[r][c][T[i].first][T[i].second];
        DP[cur][visited] = min(DP[cur][visited], w + solve(DP,i,T[i].first,T[i].second,dist,visited|(1<<i),T));
    }
    return DP[cur][visited];
}

int main()
{
    ios::sync_with_stdio(0);
    int n,m;
    int dr[]={-1,1,0,0};
    int dc[]={0,0,-1,1};

    while(cin>>m>>n && n)
    {
        vector<string>A(n);
        for(auto&s:A)cin>>s;
        vector<vector<int>>D(n,vector<int>(m,oo));
        vector<vector<int>>dist[21][21];
        vector<pair<int,int>>T;
        int R,C;
        for(int i=0; i<n; i++)
            for(int j=0; j<m; j++)
            if(A[i][j]=='*' || A[i][j]=='o')
        {
            if(A[i][j]=='*')T.push_back({i,j});
            else R=i,C=j;

            dist[i][j]=D;
            dist[i][j][i][j]=0;
            queue<pair<int,int>>q;
            q.push({i,j});

            while(!q.empty())
            {
                int r = q.front().first;
                int c = q.front().second;
                q.pop();

                for(int k=0; k<4; k++)
                    if(valid(r+dr[k],c+dc[k],A) && dist[i][j][r+dr[k]][c+dc[k]]==oo)
                dist[i][j][r+dr[k]][c+dc[k]]=dist[i][j][r][c]+1,q.push({r+dr[k],c+dc[k]});
            }
        }

        T.push_back({R,C});
        swap(T[0],T.back());
        vector<vector<ll>>DP(T.size(),vector<ll>(1<<(T.size()+1),-1));
        ll ats = solve(DP,0,R,C,dist,1LL,T);

       /* do
        {
            int r = R, c = C;
            ll s = 0;
            for(int i=0; i<T.size(); i++)
            {
                s+=dist[r][c][T[i].first][T[i].second];
                r=T[i].first;
                c=T[i].second;
            }
            ats=min(ats,s);
        }while(next_permutation(T.begin(),T.end())); //TSP bruteforce */
        cout<<(ats>=oo ? -1 : ats)<<"\n";
    }
}
