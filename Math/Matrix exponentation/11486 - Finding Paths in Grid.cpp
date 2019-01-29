#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

vector<vector<ll>> mul(vector<vector<ll>>A, vector<vector<ll>>B, ll m)
{
    int n = A.size();
    vector<vector<ll>>C(n,vector<ll>(n));
    for(int i=0; i<n; i++)
    for(int j=0; j<n; j++)
    for(int k=0; k<n; k++)
    C[i][j] = (C[i][j] + A[i][k]*B[k][j])%m;

    return C;
}

vector<vector<ll>> powm(vector<vector<ll>>A, ll n, ll m)
{
    if(n==1)return A;
    if(n&1)return mul(A,powm(A,n-1,m),m);
    return powm(mul(A,A,m),n/2,m);
}

int main()
{
    ios::sync_with_stdio(0);
    vector<int>perm = {0,0,0,1,1,1,1};
    vector<vector<int>>states;
    do
    {
        states.push_back(perm);
    }while(next_permutation(perm.begin(),perm.end()));

    int n = states.size(); //There`s only C(4,7) states
    vector<vector<ll>>A(n,vector<ll>(n));

    for(int i=0; i<n; i++)
    for(int j=0; j<n; j++)
    {
        bool can = 1;
        bitset<8>used(0);
        for(int k=0; k<7; k++)
            if(states[j][k])
        {
            if(k-1>=0 && states[i][k-1] && !used[k-1])
            {
                used[k-1]=1;
                continue;
            }
            if(k+1<7 && states[i][k+1] && !used[k+1])
            {
                used[k+1]=1;
                continue;
            }
            can=0;
        }
        A[i][j]=(can ? 1 : 0);
    }
    //base graph matrix constructed

    ll t,N,m=1000000007;
    cin>>t;
    while(t--)
    {
        cin>>N;
        vector<int>s(7);
        for(int&x:s)cin>>x,x=(x ? 1 : 0);
        if(N==1)
        {
            cout<<"1\n";
            continue;
        }
        int st = 0;
        for(int i=0; i<n; i++)
            if(states[i]==s)
            {
                st=i;
                break;
            }

        auto M = powm(A,N-1,m);//adj matrix raised to Nth power gives amount of walks between
                               //all pairs of nodes with walk length N
        ll ats = 0;

        for(int i=0; i<n; i++)
            ats = (ats + M[st][i])%m;

        cout<<ats<<"\n";
    }
}
