#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ull unsigned ll
#define ld long double
#define oo 666666666

void printMatrix(vector<vector<ld>>&M)
{
    for(auto&r : M)
        for(int j=0;j<r.size();j++)
        cout<<setprecision(3)<<fixed<<setw(5)<<r[j]<<(j+1==r.size()?"\n":" ");
}

vector<ld> GaussianElimination(vector<vector<ld>>&M)
{
    //printMatrix(M);
    int n = M.size();
    int m = M[0].size();
    for(int i=0; i<n; i++)
    {

        int mx = i;
        for(int ii=i; ii<n; ii++)
            if(fabs(M[ii][i]) > fabs(M[mx][i]))
                mx=ii;
        swap(M[mx],M[i]);

        //cout<<"Divide row "<<i+1<<" with "<<M[i][i]<<"\n";
        ld d = M[i][i];
        for(int j=i; j<m; j++)
            M[i][j]/=d;

        //printMatrix(M);

        //cout<<"Multiply current row and add to others\n";

        for(int ii=0; ii<n; ii++)
            if(ii!=i && M[ii][i])
            {
                ld mul = -M[ii][i];
                for(int j=i; j<m; j++)
                    M[ii][j]+=M[i][j]*mul;
            }

        //printMatrix(M);
    }
    vector<ld>X;
    for(int i=0; i<n; i++)
        X.push_back(M[i].back());
    return X;
}

int main()
{
    ios::sync_with_stdio(0);
    int t;
    cin>>t;
    while(t--)
    {
        vector<ull>f(1500);
        for(auto&x:f)cin>>x;
        vector<vector<ld>>M(7);

        for(int i=0; i<7; i++)
        {
            M[i].push_back(1);
            ll k=i+1;
            for(int j=1; j<7; j++)
                M[i].push_back(k),k*=(i+1);
            M[i].push_back(f[i]);
        }

        auto X = GaussianElimination(M);
        vector<ull>A(7);
        ull mx = 0;
        for(int i=0; i<7; i++)
            A[i]=round(X[i]),mx=max(mx,A[i]);

        bool ok = mx < 1001;

        for(ll i=0; i<f.size() && ok; i++)
        {
            ld s=0;
            for(ll j=0; j<7; j++)
                s+=A[j]*(i==0 ? 1 : pow((ld)i+1,(ld)j));
            if(fabs(s-f[i]) > 1e-3)
            {
                //cout<<"Failed at "<<i<<" "<<s<<" "<<f[i]<<"\n";
                ok=0;
                break;
            }
        }

        if(!ok)
        cout<<"This is a smart sequence!\n";
        else
        for(int i=0; i<7; i++)
        cout<<A[i]<<(i==6?"\n":" ");
    }
}
