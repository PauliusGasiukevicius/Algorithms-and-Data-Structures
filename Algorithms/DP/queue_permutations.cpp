#include <bits/stdc++.h>
using namespace std;
#define ll long long

/*
There is a queue with N people. Every person has a different heigth. We can see P people, when we
are looking from the beginning, and R people, when we are looking from the end. Its because they
are having different height and they are covering each other. How many different permutations of our
queue has such a interesting feature?
*/

int main()
{
    ios::sync_with_stdio(0);
    ll DP[16][16][16]={};
    DP[1][1][1]=1;

    for(int n=2; n<=13; n++)
        for(int l=1; l<=n; l++)
            for(int r=1; r<=n; r++)
            DP[n][l][r] = DP[n-1][l-1][r] + DP[n-1][l][r-1] + DP[n-1][l][r]*(n-2);

    /*
    Here, in each iteration we add a new person.
    We assume he has the smallest height
    If we put him in front we have one extra person to see
     hence we add [n-1][l-1][r] ot the number of ways
     same reasoning for [n-1][l][r-1]
     and if he`s not in front, that means hes in the middle
      he doesn`t contribute to l and r that way
      and theres only (n-2 places where he can be)
    */

    int t,n,l,r;
    cin>>t;

    while(t--)
    {
        cin>>n>>l>>r;
        cout<<DP[n][l][r]<<"\n";
    }
}
