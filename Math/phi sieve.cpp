#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

int main()
{
    ios::sync_with_stdio(0);
    vector<int>phi(2000001);
    vector<int>DepthPhi(2000001,0);

    for(int i=1; i<2000001; i++)
        phi[i]=i;

    for(int i=2; i<2000001; i++)
        if(phi[i]==i)//we have a prime
        for(int j=i; j<2000001; j+=i)
        phi[j]-=phi[j]/i;

    for(int i=2; i<2000001; i++)
            DepthPhi[i]=DepthPhi[phi[i]] + 1;

    for(int i=1; i<2000001; i++)
        DepthPhi[i]+=DepthPhi[i-1];

    int t,l,r;
    cin>>t;
    while(t--)
    {
        cin>>l>>r;
        cout<<DepthPhi[r]-DepthPhi[l-1]<<"\n";
    }
}
