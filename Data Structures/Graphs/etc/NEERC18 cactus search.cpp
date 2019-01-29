#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

vector<int>g[505];
int M[505][505];

int main()
{
    //ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n,m,k,x,y;
    cin>>n>>m;

    for(int i=1; i<=n; i++)
    for(int j=1; j<=n; j++)
        M[i][j]=666;

    while(m--)
    {
        cin>>k>>x;
        k--;
        while(k--)
        {
            cin>>y;
            g[x].push_back(y);
            g[y].push_back(x);
            M[x][y]=M[y][x]=1;
            x=y;
        }
    }

    for(int i=1; i<=n; i++)M[i][i]=0;

    for(int k=1; k<=n; k++)
    for(int i=1; i<=n; i++)
    for(int j=1; j<=n; j++)
        M[i][j]=min(M[i][j],M[i][k]+M[k][j]);

    for(int q=0; q<n; q++)
    {
        string s;
        vector<int>cand,nxt;
        bool done = 0;

        for(int i=1; i<=n; i++)
            cand.push_back(i);

        while(cand.size() > 1)
        {
            int guess = cand.back();
            int sumOfDistances = 666666666;

            for(auto& u : cand)
            {
                int sum = 0;
                for(auto& v : cand)
                    sum+=M[u][v];

                if(sum < sumOfDistances)
                {
                    sumOfDistances = sum;
                    guess = u;
                }
            }

            cout<<guess<<"\n"<<flush;
            cin>>s;

            if(s=="FOUND")
            {
                done=1;
                break;
            }
            else
            {
                int w;
                cin>>w;

                for(auto& u : cand)
                    if(M[w][u] < M[guess][u])
                    nxt.push_back(u);

                cand = nxt;
                nxt.clear();
            }
        }

        if(!done)
        {
            cout<<cand.back()<<"\n"<<flush;
            cin>>s;
        }
    }
}
