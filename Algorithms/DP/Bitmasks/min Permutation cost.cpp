#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

//Note some bitmask algorithms fail when done recursively
int DP[1<<20];
int n;
int A[21],S[21];

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin>>n;
    for(int i=0; i<n; i++)
        cin>>A[i]>>S[i];

    for(int i=1; i<(1<<n); i++)
        DP[i]=oo;

    for(int i=1; i<(1<<n); i++)
    {
        bitset<32>b(i);
        for(int j=0; j<n; j++)//last to place in cur mask
            if(b[j])
        {
            int opt = DP[i&~(1<<j)];
            while(opt%A[j]!=0)opt++;
            DP[i]=min(DP[i],opt+S[j]);
        }
    }

    cout<<DP[(1<<n)-1];
}
