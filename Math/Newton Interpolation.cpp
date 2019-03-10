#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

void Newton_Interpolation(vector<ld>X, vector<ld>Y)
{
    int n = X.size();
    vector<vector<ld>>D(n,vector<ld>(n));
    for(int i=0; i<n; i++)
        D[i][0]=Y[i];

    for(int j = 1; j < n; j++)
        for(int i = j; i < n; i++)
            D[i][j] = (D[i-1][j-1] - D[i][j-1])/(X[i-j]-X[i]);

    vector<vector<ld>>L(n);
    L[0]={Y[0]};

    for(int i=1; i<n; i++)
    {
        vector<ld>c = {-X[0], 1};

        for(int j=1; j<i; j++)
        {
            vector<ld>nxt = {-X[j],1};
            auto cp = c;
            c.insert(c.begin(),0);

            for(int k=0; k<cp.size(); k++)
                c[k]+=cp[k]*nxt[0];
        }

        for(int j=0; j<c.size(); j++)
            c[j]*=D[i][i];

        for(int j=0; j<L[i-1].size(); j++)
            c[j]+=L[i-1][j];

        L[i]=c;
    }

    while(L.back().size() > 1 && L.back().back()==0)L.back().pop_back();
    for(int pw = L.back().size()-1; pw>=0; pw--)
        cout<<L.back()[pw]<<" x^"<<pw<<"  ";
    cout<<"\n";
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    Newton_Interpolation({1,2,3,4,5},{1,4,10,20,35});
}
