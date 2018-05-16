#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

/*
PROG: shopping
LANG: C++14
*/

int main()
{
    ios::sync_with_stdio(0);
    freopen("shopping.in","r",stdin);
    freopen("shopping.out","w",stdout);

    int s;
    cin>>s;
    vector<vector<int>>K(s);
    vector<vector<int>>C(s);
    vector<int>P(s);
    for(int i=0; i<s; i++)
    {
        int sz,k,c,p;
        cin>>sz;
        while(sz--)
            cin>>c>>k,K[i].push_back(k),C[i].push_back(c);
        cin>>P[i];
    }

    int n;
    cin>>n;
    int DP[11][11][11][11][11]={};
    vector<int>c(5),k(5),p(5);
    for(int i=0; i<n; i++)
        {
            cin>>c[i]>>k[i]>>p[i];
            vector<int>kk(1,1),cc(1,c[i]);
            K.push_back(kk),C.push_back(cc),P.push_back(p[i]);
        }

    for(int a=0; a<11; a++)
    for(int b=0; b<11; b++)
    for(int c=0; c<11; c++)
    for(int d=0; d<11; d++)
    for(int e=0; e<11; e++)
        DP[a][b][c][d][e]=oo;

    DP[k[0]][k[1]][k[2]][k[3]][k[4]]=p[0]*k[0]+p[1]*k[1]+p[2]*k[2]+p[3]*k[3]+p[4]*k[4];
    DP[0][0][0][0][0]=0;
    set<int>S = {c[0],c[1],c[2],c[3],c[4]};

    for(int i=0; i<K.size(); i++)
    {
        bool can = 1;
        for(int j=0; j<C[i].size(); j++)
            if(!S.count(C[i][j]))can=0;

        if(!can)continue;

        vector<int>an(5);
        for(int j=0; j<C[i].size(); j++)
        for(int z=0; z<n; z++)
        if(C[i][j]==c[z])
        an[z]=K[i][j];

        /*
        cout<<"Offer "<<i<<"\n";
        for(int i=0; i<5; i++)cout<<an[i]<<" ";
        cout<<"\n";*/

       // for(int rep=0; rep<5; rep++)
        for(int a=0; a<6; a++)
        for(int b=0; b<6; b++)
        for(int c=0; c<6; c++)
        for(int d=0; d<6; d++)
        for(int e=0; e<6; e++)
        DP[a+an[0]][b+an[1]][c+an[2]][d+an[3]][e+an[4]] =
        min(DP[a+an[0]][b+an[1]][c+an[2]][d+an[3]][e+an[4]],
            DP[a][b][c][d][e] + P[i]);
    }

    cout<<DP[k[0]][k[1]][k[2]][k[3]][k[4]]<<"\n";
}
