#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(0);
    int n,m;
    cin>>n>>m;
    int u[10001], v[10001], w[10001];
    vector<int>SP(n+1,666666666);
    SP[1]=0;
    for(int i=0; i<m; i++)
        cin>>u[i]>>v[i]>>w[i];

    for(int i=0; i<n; i++)
        for(int j=0; j<m; j++)
            if(SP[u[j]] + w[j] < SP[v[j]])
            SP[v[j]]=SP[u[j]]+w[j];

    for(int i=1; i<=n; i++)
        cout<<min(SP[i],30000)<<" ";
}
