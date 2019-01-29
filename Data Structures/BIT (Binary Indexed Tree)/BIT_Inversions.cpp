#include <bits/stdc++.h>
using namespace std;
#define ll long long

void update(vector<ll>&BIT, int c, int x)
{
    for(c;c<BIT.size();c+=(c&-c))
        BIT[c]+=x;
}

ll query(vector<ll>&BIT,int c)
{
    ll sum = 0;
    for(c; c>0; c-=(c&-c))
        sum+=BIT[c];
    return sum;
}

int main()
{
    ios::sync_with_stdio(0);
    int t,n;
    cin>>t;

    while(t--)
    {
        cin>>n;
        vector<vector<int>>A(n,vector<int>(2));

        for(int i=0; i<n; i++)
            cin>>A[i][0],A[i][1]=i+1;

        sort(A.begin(),A.end());

        vector<ll>BIT(n+1);
        ll inv = 0;

        for(int i=n-1; i>=0; i--)
            {
                inv+=query(BIT,A[i][1]);
                update(BIT,A[i][1],1);
            }

        cout<<inv<<"\n";
    }
}
