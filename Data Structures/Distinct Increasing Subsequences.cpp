#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld double
#define oo 666666666

ll M = 5000000;

void add(vector<ll>&BIT, int c, ll v)
{
    for(;c<BIT.size(); c+=c&-c)
        BIT[c]=(BIT[c]+v)%M;
}

ll get(vector<ll>&BIT, ll c)
{
    ll s=0;
    for(;c;c-=c&-c)
        s=(s+BIT[c])%M;
    return s;
}

void compress(vector<ll>&A)
{
    auto B = A;
    sort(B.begin(),B.end());
    for(int i=0; i<A.size(); i++)
        A[i]=lower_bound(B.begin(),B.end(),A[i]) - B.begin() + 1;
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    int n,k;
    cin>>n>>k;
    vector<ll>A(n);
    vector<vector<ll>>BITS(k+1,vector<ll>(n+1));
    vector<vector<ll>>DP(k+1,vector<ll>(n+1));//[len][last] - number of subsequences of length len that ends in [last]
    for(int i=0; i<n; i++)
        cin>>A[i];

    compress(A);//compress all values in A to range [1,n]

    for(int i=0; i<n; i++)
        for(int j=1; j<=k; j++)
        {
            ll have = (((j==1 ? 1 : get(BITS[j-1],A[i]-1)) - DP[j][A[i]])%M + M)%M;
            //if j==1 theres 1 way to start a new subsequence, otherwise we can extend any subsequences of length j-1
            //that started before current one
            //we subtract all subsequences of same length that as current one that ends in same element
            //to calculate only distinct subsequences
            add(BITS[j],A[i], have);
            DP[j][A[i]]=(have + DP[j][A[i]])%M;
        }

    cout<<(get(BITS[k],n)+M)%M<<"\n";
}
