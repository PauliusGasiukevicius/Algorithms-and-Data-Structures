#pragma GCC optimize("Ofast")
#pragma GCC optimize ("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

/*
    To calculate the Grundy value of a given state you need to:
    1)  Get all possible transitions from this state
    2)  Each transition can lead to a sum of independent games.
        Calculate the Grundy value for each independent game and xor-sum them.
    3)  After we calculated Grundy values for each transition we find the state's value as the mex
        of these numbers.

    If the value is zero, then the current state is losing, otherwise it is winning.

In comparison to the previous section, we take into account the fact that there can be transitions
 to combined games. We consider them a Nim with pile sizes equal to the independent games' Grundy values.
 We can xor-sum them just like usual Nim according to Bouton's theorem.
*/

int Grundy[5005];
int v[5005];

int solve(int n)
{
    //states 0..2 - losing so grundy number is 0
    for(int i=2; i<=n; i++)
    {
        for(int j=0; j<=i; j++)
            v[j]=0;

        for(int j=0; j<=i-2; j++)
            v[Grundy[j]^Grundy[i-2-j]]=1; //gotta XOR all independant reachable games

        while(v[Grundy[i]])Grundy[i]++; //finding MEX
    }
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int t,n;
    cin>>t;
    solve(5000);

    while(t--)
    {
        cin>>n;
        cout<<(Grundy[n]==0 ? "Second\n" : "First\n");
    }
}
