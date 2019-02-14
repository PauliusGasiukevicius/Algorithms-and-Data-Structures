#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

ll DP[3003][3003]; // [prefix size][last_element] - cnt of permutations of 1...i with last element j
ll pf[3003][3003]; // prefix sums to get n^2 from n^3
ll mod = 1e9+7;

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n;
    string s; //given string is a sequence of '<' and '>', all permutations must satisfy those signs
    cin>>n>>s;
    s="  "+s;

    DP[1][1]=pf[1][1]=1; //well obviously only 1 way to make permutation of 1 element satisfying 0 signs

    for(int i=2; i<=n; i++)
        for(int j=1; j<=i; j++)
        {
                if(s[i]=='>')//if current element need to be less then last one
                {
                    //so last element should be greater than j,
                    //hence we can try all elements from range [j,i-1]
                    //why not [j+1,i]? cause after inserting element j all element >= j are increased by 1
                    //this lets us keep permutation correct
                    DP[i][j]+=pf[i-1][i-1]-pf[i-1][j-1];
                    DP[i][j]%=mod;
                    DP[i][j]=(DP[i][j]+mod)%mod;
                    //for(int k=j; k<=n; k++)
                    //DP[i][j]+=DP[i-1][k];
                }
                else//-> if current element need to be more then last one
                {
                    //so we know that last element was < j
                    //so we try all values for last elm in range [1,j-1]
                    //after inserting element j all element >= j are increased by 1
                    //this lets us keep permutation correct
                    DP[i][j]+=pf[i-1][j-1];
                    DP[i][j]%=mod;
                    //for(int k=j-1; k>=1; k--)
                    //DP[i][j]+=DP[i-1][k];
                }
            pf[i][j] = (pf[i][j-1] + DP[i][j])%mod;
        }

    ll ats = 0;
    for(int i=0; i<=n; i++)
        ats=(ats + DP[n][i])%mod;

    cout<<(ats+mod)%mod;
}
