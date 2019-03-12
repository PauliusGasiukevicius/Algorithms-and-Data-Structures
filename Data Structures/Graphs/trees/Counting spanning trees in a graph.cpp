#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

const ld EPS = 1e-9;
ld Determinant(vector<vector<ld>>a){
    int n = a.size();
    ld det = 1;
    for (int i=0; i<n; ++i) {
        int k = i;
        for (int j=i+1; j<n; ++j)
            if (abs (a[j][i]) > abs (a[k][i]))
                k = j;
        if (abs (a[k][i]) < EPS) {
            det = 0;
            break;
        }
        swap (a[i], a[k]);
        if (i != k)
            det = -det;
        det *= a[i][i];
        for (int j=i+1; j<n; ++j)
            a[i][j] /= a[i][i];
        for (int j=0; j<n; ++j)
            if (j != i && abs (a[j][i]) > EPS)
                for (int k=i+1; k<n; ++k)
                    a[j][k] -= a[i][k] * a[j][i];
    }

    return det;
}

ll Kirchhoff(vector<vector<int>>M){
    int n=M.size();
    vector<vector<ld>>L(n,vector<ld>(n));

    for(int i=0; i<n; i++)
    for(int j=0; j<n; j++)
        if(i==j)
        {
            L[i][i]=0;
            for(int k=0; k<n; k++)
                if(k!=i)
                L[i][i]+=M[i][k];
        }
        else L[i][j]=-M[i][j];

    for(int i=0; i<n; i++)
        L[i].pop_back();
    L.pop_back();

    return round(Determinant(L));
}
/** Can also count MST's : 
1) Split the edges into sets according to their cost.
2) Then, for each cost starting with the smallest one, consider those edges only. They form several components. 
3) For each such component, compute the number of spanning trees using the Matrix Tree Theorem,
4) multiply the result by this value, and then merge the component into a single vertex.*/

int A[31][31][31][31];
map<array<int,2>,int>mp;

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n,m,k,nxt=0;
    cin>>m>>n>>k;
    while(k--)
    {
        int r,c,x,y;
        cin>>r>>c>>x>>y;
        A[r][c][x][y]=A[x][y][r][c]=1;
    }

    vector<vector<int>>M(n*m,vector<int>(n*m));

    for(int i=1; i<=n; i++)
    for(int j=1; j<=m; j++)
        mp[{i,j}]=nxt++;

    for(int i=1; i<=n; i++)
    for(int j=1; j<=m; j++)
    {
        int dr[]={-1,0,1,0};
        int dc[]={0,-1,0,1};
        for(int k=0; k<4; k++)
        {
            int r = i+dr[k];
            int c = j+dc[k];
            if(min(r,c)>=1 && r<=n && c<=m && !A[i][j][r][c])
                M[mp[{i,j}]][mp[{r,c}]]=1;
        }
    }

    cout<<Kirchhoff(M);
}
