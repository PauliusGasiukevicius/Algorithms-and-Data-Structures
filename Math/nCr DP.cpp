ll C[1001][1001];

ll binom(int n, int k)
{
    if(k==0 || n==k)return C[n][k] = 1;
    if(C[n][k]!=0)return C[n][k];
    return C[n][k] = binom(n-1,k-1) + binom(n-1,k);
}
