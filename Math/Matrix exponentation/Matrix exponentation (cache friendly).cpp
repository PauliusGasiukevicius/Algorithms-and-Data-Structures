#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

void print(vector<vector<ll>>&A)
{
    cout<<A.size()<<" "<<A[0].size()<<endl;
    for(int i=0; i<A.size(); i++)
        for(int j=0; j<A[i].size(); j++)
        cout<<A[i][j]<<(j+1==A[i].size()?"\n":" ");
}

vector<vector<ll>> mul(vector<vector<ll>>A, vector<vector<ll>>B, ll M)
{
    //i,k,j order is more cache friendly
    vector<vector<ll>>C(A.size(),vector<ll>(A.size()));
    for(int i=0; i<A.size(); i++)
    for(int k=0; k<A.size(); k++)
    for(int j=0; j<A.size(); j++)
        C[i][j] = (C[i][j] + A[i][k]*B[k][j])%M;

    return C;
}

vector<vector<ll>> powMatrix(vector<vector<ll>>A, ll d, ll M)
{
    if(d==1)return A;
    if(d&1)return mul(A,powMatrix(A,d-1,M),M);
    return powMatrix(mul(A,A,M),d/2,M);
}
