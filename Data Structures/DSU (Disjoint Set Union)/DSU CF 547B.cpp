#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo INT_MAX/2

int Find(vector<int>&P, int u)
{
    return P[u] < 0 ? u : P[u]=Find(P,P[u]);
}

void Union(vector<int>&P, int u, int v)
{
    u=Find(P,u);
    v=Find(P,v);
    if(u==v)return;
    P[u]+=P[v];
    P[v]=u;
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    int n;
    cin>>n;
    vector<int>A(n+1),ats(n+1),P(n+1,-1);

    for(int i=1; i<=n; i++)
        cin>>A[i];

    ats[1] = *max_element(A.begin()+1,A.end());
    vector<vector<int>>S(n-1,vector<int>(3));//mn of i and i+1, i, i+1

    for(int i=0; i+1<n; i++)
    {
        int mn = min(A[i+1],A[i+2]);
        S[i][0]=mn;
        S[i][1]=i+1;
        S[i][2]=i+2;
    }

    sort(S.rbegin(),S.rend());//sort all edges in desc order

    for(int i=0; i<S.size(); i++)
    {
        Union(P,S[i][1],S[i][2]);
        int sz = -P[Find(P,S[i][1])];
        ats[sz]=max(ats[sz],S[i][0]);
    }

    for(int i=n-1; i>=1; i--)
        ats[i]=max(ats[i],ats[i+1]);

    for(int i=1; i<=n; i++)
        cout<<ats[i]<<" ";
}

