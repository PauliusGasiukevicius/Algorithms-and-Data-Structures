#include <bits/stdc++.h>
using namespace std;
#define ll long long

//multiplies 2 matrices in O(n^3)
vector<vector<ll>> Mul(vector<vector<ll>>A, vector<vector<ll>>B, int m)
{
    int n = A.size();
    vector<vector<ll>>R(n,vector<ll>(n));

    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
            for(int k=0; k<n; k++)
            R[i][j]= (R[i][j] + A[i][k]*B[k][j])%m;

    return R;
}

//raises matrix M to degree n on O(lg n)
vector<vector<ll>> MPow(vector<vector<ll>>M, int n, int m)
{
    if(n==1)return M;
    if(n&1)return Mul(M,MPow(M,n-1,m),m);
    return MPow(Mul(M,M,m),n/2,m);
}

//This particular example solves reccurences of form F(0) = a, F(1) = b, F(n) = F(n-1) + F(n-2)
int main()
{
    ios::sync_with_stdio(0);
    ll t,n,m,a,b,mod;
    cin>>t;

    while(t--)
    {
        cin>>a>>b>>n>>m;
        mod = 1;
        while(m--)mod*=10;
        vector<vector<ll>>M = {{a+b,b},{b,a}}; //coefficients matrix
        vector<vector<ll>>Fib = {{1,1},{1,0}}; // Reccurence matrix
        if(n!=0)
        cout<<Mul(MPow(Fib,n,mod),M,mod)[1][1]%mod<<"\n";
        else cout<<a<<"\n";
    }
}

/* more examples [Source: https://comeoncodeon.wordpress.com/2011/05/08/recurrence-relation-and-matrix-exponentiation/]

| f(n+1) | = | 1 1 | x | f(n)   |
| f(n)   |   | 1 0 |   | f(n-1) |

| f(n+1) | = | a b c | x | f(n)   |
| f(n)   |   | 1 0 0 |   | f(n-1) |
| f(n-1) |   | 0 1 0 |   | f(n-2) |

| f(n+1) | = | a b 1 | x | f(n)   |
| f(n)   |   | 1 0 0 |   | f(n-1) |
| c      |   | 0 0 1 |   | c      |

| g(n+1) |   | a b c 0 |   | g(n)   |
| g(n)   | = | 1 0 0 0 | x | g(n-1) |
| f(n+2) |   | 0 0 d e |   | f(n+1) |
| f(n+1) |   | 0 0 1 0 |   | f(n)   |

*/
