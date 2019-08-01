/*
In combinatorial mathematics, a derangement is a permutation of the elements of a set, 
such that no element appears in its original position. In other words, a derangement is a permutation that has no fixed points. 
*/

ll D[1000001];

ll Dearrangements(ll n)
{
    D[0]=1;
    for(int i=2; i<=n; i++)
    {
        D[i]=(i-1)*(D[i-1] + D[i-2]);
        D[i]%=MOD;
    }
    return D[n];
}
