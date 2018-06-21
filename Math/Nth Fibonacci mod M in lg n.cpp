#include <bits/stdc++.h>
using namespace std;
#define ll long long

ll tmp[2][2];

void matrixMul(vector<vector<ll>>&A, vector<vector<ll>>B, ll M)
{
        tmp[0][0] = (A[0][0]*B[0][0] + A[0][1] * B[1][0])%M;
        tmp[0][1] = (A[0][0]*B[0][1] + A[0][1] * B[1][1])%M;
        tmp[1][0] = (A[1][0]*B[0][0] + A[1][1] * B[1][0])%M;
        tmp[1][1] = (A[1][0]*B[0][1] + A[1][1] * B[1][1])%M;
        A[0][0]=tmp[0][0];
        A[0][1]=tmp[0][1];
        A[1][0]=tmp[1][0];
        A[1][1]=tmp[1][1];
}

vector<vector<ll>> matrixPow(vector<vector<ll>>A, ll k, ll M)
{
    if(k==1)return A;

    if(k&1)
    {
        matrixMul(A,matrixPow(A,k-1,M),M);
        return A;
    }
    else
    {
        matrixMul(A,A,M);
        return matrixPow(A,k/2,M);
    }
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
