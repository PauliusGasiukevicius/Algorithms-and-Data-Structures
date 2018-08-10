#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo INT_MAX/2

vector<array<int,2>> StableMatching(vector<queue<int>>&M, vector<vector<int>>&F){
//Here`s F[f][m] - gives priority female f has for male m
//And M[m] - stores queue, which women this man should propose to next
int n = M.size()-1;
vector<int>P(n+1,-1); //partner for female f
queue<int>q;
for(int i=1; i<=n; i++)
    q.push(i);

while(!q.empty())
{
    int m = q.front();
    q.pop();

    int f = M[m].front();
    M[m].pop();
    if(P[f]==-1)P[f]=m;
    else if(F[f][P[f]] > F[f][m])
        swap(P[f],m),q.push(m);
    else q.push(m);
}

vector<array<int,2>>ats;
for(int i=1; i<=n; i++)
ats.push_back({P[i],i});
return ats;
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    int t,n;
    cin>>t;
    while(t--)
    {
        cin>>n;
        vector<queue<int>>M(n+1);
        vector<vector<int>>F(n+1,vector<int>(n+1));
        for(int i=0; i<n; i++)
        {
            int f,m;
            cin>>f;
            for(int j=0; j<n; j++)
                cin>>m,F[f][m]=j;
        }

            for(int i=0; i<n; i++)
        {
            int f,m;
            cin>>m;
            for(int j=0; j<n; j++)
                cin>>f,M[m].push(f);
        }

        auto ats = StableMatching(M,F);
        for(auto&p:ats)
            cout<<p[0]<<" "<<p[1]<<"\n";
    }
}
