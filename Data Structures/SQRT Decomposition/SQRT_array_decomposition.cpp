#include <bits/stdc++.h>
using namespace std;
#define ll long long

int main()
{
    ios::sync_with_stdio(0);
    int n,m,x;
    char c;

    cin>>n>>m;

    int k = sqrt(n+1) + 1;
    vector<int>A(n+1);
    vector<int>B(k+1);

    while(m--)
    {
        cin>>c;
        if(c=='F')
        {
            cin>>x;
            B[x/k] += (A[x]^1) - A[x];
            A[x]^=1;
        }
        else
        {
            int l,r;
            cin>>l>>r;
            int sum = 0;

            while(l%k!=0 && l<r)
                sum+=A[l++];

            while(l+k<=r)
                sum+=B[l/k],l+=k;

            while(l<=r)
                sum+=A[l++];

            cout<<sum<<"\n";
        }
    }
}
