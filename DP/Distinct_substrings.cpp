#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

ll DP[500005];
int last[256];
ll M = 1e9+7;

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    string s;
    cin>>s;
    for(int i='a'; i<='z'; i++)last[i]=-1;
    DP[0]=1;//empty substr

    for(int i=1; i<=s.size(); i++)
    {
        DP[i]=(2*DP[i-1])%M; // 2 choices either extend current subseq or not
        //if there were subsequences of form xxxxx + s[i]
        //we can sub how many of them there was (its DP[last[s[i-1]]])
        if(last[s[i-1]]!=-1)DP[i] = (DP[i] - DP[last[s[i-1]]] + M)%M;
        last[s[i-1]]=i-1;
    }
    cout<<DP[s.size()] - 1;//-1 to ignore empty substring
}
