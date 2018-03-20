#include <bits/stdc++.h>
using namespace std;
#define ll long long

int exist(vector<vector<ll>>&A, ll x1, ll y1, ll x2, ll y2)
{
    for(int i=0; i<A.size(); i++)
        if(x1>=A[i][0] && x2<=A[i][2] && y1>=A[i][1] && y2<=A[i][3])return i+1;
    return 0;
}

int main()
{
    ios::sync_with_stdio(0);
    ll n;
    cin>>n;
    vector<vector<ll>>A(n,vector<ll>(4));
    vector<ll>X,Y;
    for(auto&v:A)
        for(int j=0; j<4; j++)
    {
        cin>>v[j];
        if(j&1)Y.push_back(v[j]);
        else X.push_back(v[j]);
    }
    sort(X.begin(),X.end());
    sort(Y.begin(),Y.end());

    ll ats = 0;

    for(int i=1; i<X.size(); i++)
        for(int j=1; j<Y.size(); j++)
        if(X[i]!=X[i-1] && Y[j]!=Y[j-1] && exist(A,X[i-1],Y[j-1],X[i],Y[j]))
            ats+=(X[i]-X[i-1])*(Y[j]-Y[j-1]);

    cout<<ats<<"\n";
}
