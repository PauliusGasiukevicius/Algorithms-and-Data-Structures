#include <bits/stdc++.h>
using namespace std;
#define ld long double
#define ll long long
#define oo 666666666

ll SC[101];
ll C[101][101];

ll SuperCatalan(int x) //1, 1, 3, 11, 45, 197, 903, 4279....
{
    if(x<3)return 1;
    if(SC[x])return SC[x];
    return SC[x] = (3*(2*x-3)*SuperCatalan(x-1)-(x-3)*SuperCatalan(x-2))/x;
}

ll Choose(int n, int k)
{
    if(k==0 || k==n)return 1;
    if(C[n][k])return C[n][k];
    return C[n][k]=Choose(n-1,k-1) + Choose(n-1,k);
}

ll Catalan(int x) //1, 2, 5, 14, 42, 132, 429 .....
{
    return Choose(2*x,x)/(x+1);
}

int main()
{
    ios::sync_with_stdio(0);
    int n;
    while(cin>>n)
        cout<<SuperCatalan(n)-Catalan(n-1)<<"\n";
}
