#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

ll DP[1001][20001];
int done[1001][20001];
vector<array<ll,4>>A;//[w+s][val][weight][cap]
ll n;

ll solve(int pos, int cap)
{
    if(cap ==0 || pos >= n)return 0;
    if(done[pos][cap])return DP[pos][cap];

    done[pos][cap]=1;
    if(A[pos][2] <= cap)DP[pos][cap] = A[pos][1] + solve(pos+1, min(cap-A[pos][2], A[pos][3]));
    DP[pos][cap]=max(DP[pos][cap], solve(pos+1,cap));
    return DP[pos][cap];
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin>>n;
    A.resize(n);
    for(int i=0; i<n; i++)
    {
        ll w,s,v; //w-block weight, s - block capacity to hold weight, v - value
        cin>>w>>s>>v;
        A[i]={w+s,v,w,s};
    }

    //lets say we have 2 blocks A(s1,w1) and B(s2,w2)
    //if we put A on B remaining cap is s2-w1
    //otherwise its s1-w2
    //so if block A should go on bottom s1-w2 > s2-w1 or s1+w1 > s2+w2

    sort(A.rbegin(),A.rend());
    cout<<solve(0,20000)<<"\n";
}


/* Bottom-Up version
     sort(A.begin(),A.end());
    vector<ll> dp(MAX_S + 1);
    // dp[i] - best score of boxes with total weight i
    for(auto block : A) {
        for(int w = min(block.s, MAX_S - block.w); w >= 0; --w) {
            dp[w+block.w] = max(dp[w+block.w], dp[w] + block.v);
        }
    }
    ll answer = 0;
    for(int i = 0; i <= MAX_S; ++i) {
        answer = max(answer, dp[i]);
    }
*/
