const int mxLog = 20;
const int mxN = 3e5;
int A[mxN+1];
int Log[mxN+1];//Logarithm only useful for queries like max/min/gcd
//where including same element twice does not matter
int st[mxN+1][mxLog+1];

void buildSparseTable(int n)
{
    Log[1]=0;
    for(int i=2; i<=mxN; i++)
        Log[i]=Log[i/2]+1;

    for(int k=0; k<=mxLog; k++)
        for(int i=1; i + (1<<k) - 1 <=mxN; i++)
            st[i][k]= k==0 ? A[i] : __gcd(st[i][k-1],st[i+(1<<(k-1))][k-1]);
}

int Get(int l, int r)
{
    int lg = Log[r-l+1];
    return __gcd(st[l][lg], st[r-(1<<lg)+1][lg]);
}