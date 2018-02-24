#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(0);
    long long n,m,a[101];
    cin>>n>>m;

    for(int i=0; i<n; i++)
        cin>>a[i],a[i]%=m;

    int i=0;
    vector<int>A,B;

    for(i;i < n/2; i++)
        A.push_back(a[i]);
    for(i;i<n;i++)
        B.push_back(a[i]);

    vector<long long>SA(1<<(A.size()),0),SB(1<<(B.size()),0);

    for(int i=0; i<(1<<A.size()); i++)
    {
        for(int j=0; j<20; j++)
            if((i&(1<<j))==(1<<j))
            SA[i] =  (SA[i] + A[j])%m;
    }

    for(int i=0; i<(1<<B.size()); i++)
    {
        for(int j=0; j<20; j++)
            if((i&(1<<j))==(1<<j))
            SB[i] =  (SB[i] + B[j])%m;
    }

    long long ats = 0LL;

    sort(SA.begin(),SA.end());
    sort(SB.begin(),SB.end());

    for(int i=0; i<SA.size(); i++)
    {
        long long left = m - SA[i] - 1; // safe till mod will ruin sum
        auto it = upper_bound(SB.begin(),SB.end(),left);
        it--;
        if(it!=SB.end())
        ats = max(ats, (SA[i]+*it)%m);
        ats = max(ats, (SA[i] + SB.back())%m);

        //cout<<SA[i]<<"\n";
    }

    cout<<ats<<"\n";
}
