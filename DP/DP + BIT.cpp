#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld double
#define oo 666666666

void add(vector<ll>&BIT, int c, ll v)
{
    for(;c<BIT.size(); c+=c&-c)
        BIT[c]+=v;
}

ll get(vector<ll>&BIT, ll c)
{
    ll s=0;
    for(;c;c-=c&-c)
        s+=BIT[c];
    return s;
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    int n,k;
    cin>>n>>k;
    k++;
    vector<array<ll,2>>A(n);
    vector<vector<ll>>BITS(k+1,vector<ll>(n+1));
    for(int i=0; i<n; i++)
        cin>>A[i][0],A[i][1]=i+1;

    sort(A.begin(),A.end());

    for(int i=0; i<n; i++)
    {
        add(BITS[1],A[i][1],1);
        for(int j=2; j<=k; j++)
        add(BITS[j],A[i][1],get(BITS[j-1],A[i][1]-1));
    }

    /*
    for(int j=1; j<=k; j++)
    for(int i=1; i<=n; i++)
        cout<<get(BITS[j],i) - get(BITS[j],i-1)<<(i==n?"\n":" ");*/

    cout<<get(BITS[k],n)<<"\n";
}
