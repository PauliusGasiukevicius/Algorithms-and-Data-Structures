ll C[1001][1001];

//Catalan(n) = 1/(n+1) * binom(2*n,n);
ll binom(int n, int k)
{
    if(k==0 || n==k)return C[n][k] = 1;
    if(C[n][k]!=0)return C[n][k];
    return C[n][k] = binom(n-1,k-1) + binom(n-1,k);
}

ll solve(int n, int k, vector<vector<ll>>&DP, vector<ll>&A, ll m)
{
    if(n < k)return 0;
    if(k==0)return 1;
    if(DP[n][k]!=-1)return DP[n][k];

    return DP[n][k] = (solve(n-1,k,DP,A,m)%m + A[n]*solve(n-1,k-1,DP,A,m)%m)%m;
}
