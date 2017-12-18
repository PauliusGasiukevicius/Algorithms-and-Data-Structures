#include <bits/stdc++.h>
using namespace std;
#define ll long long

vector<vector<ll>> matrixMul(vector<vector<ll>>A, vector<vector<ll>>B, ll M)
{
    vector<vector<ll>>ans(A.size(),vector<ll>(B[0].size(),0));

        for(int i=0; i<A.size(); i++)
        for(int j=0; j<B.size(); j++)
        for(int k=0; k<A[0].size(); k++)
        ans[i][j] = (ans[i][j] + A[i][k]*B[k][j])%M;

    return ans;
}

vector<vector<ll>> matrixPow(vector<vector<ll>>A, ll k, ll M)
{
    if(k==1)return A;

    if(k&1)return matrixMul(A,matrixPow(A,k-1,M),M);
    return matrixPow(matrixMul(A,A,M),k/2,M);
}

ll Fib(ll n, ll M)
{
    if(n==0)return 0;
    vector<vector<ll>>A = {{1,1},{1,0}};
    A = matrixPow(A,n,M);
    return A[0][1]%M;
}

int main()
{
    ios::sync_with_stdio(false);
    long long n,M;
    cin>>n>>M;

    cout << Fib(n,M) <<"\n";
}
