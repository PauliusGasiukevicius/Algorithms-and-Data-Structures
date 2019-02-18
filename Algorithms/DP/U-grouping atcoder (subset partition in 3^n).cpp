#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

ll A[17][17];
ll DP[1<<17];

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n;
    cin>>n;
    for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
        cin>>A[i][j];

    for(int i=0; i<(1<<n); i++)
    {
        bitset<17>b(i);
        for(int j=0; j<n; j++)
            for(int k=j+1; k<n; k++)
            if(b[j] && b[k])
            DP[i]+=A[j][k];

        int sub = i;
        while(sub)
        {
            sub = (sub-1)&i;
            //^so we go through all masks by doing sub-1
            //and because we only want sub-subset we do &subset
            //so unimportant bits get turned off
            //hence we loop only through required sub-subset 
            DP[i]=max(DP[i],DP[sub] + DP[sub^i]);
        }
    }
    /*
        So this work in 3^n
        i.e. n=3
        mask -> # submasks
        000 -> 1
        001 -> 2
        010 -> 2
        011 -> 4
        100 -> 2
        101 -> 4
        110 -> 4
        111 -> 8
        as we can see total is 3^3 = 27, other cases work similarly, can be proven by induction or some binomial maths
    */
    cout<<DP[(1<<n)-1];
}
