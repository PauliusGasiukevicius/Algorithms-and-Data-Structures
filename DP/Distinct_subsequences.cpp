#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

int main()
{
    ios::sync_with_stdio(0);
    int t;
    ll m = 1000000007;
    string s;
    cin>>t;

    while(t--)
    {
        cin>>s;
        s=" "+s;
        vector<int>last(256,-1);
        vector<ll>DP(s.size());
        DP[0]=1;

        for(int i=1; i<s.size(); i++)
        {
            DP[i]=(2*DP[i-1])%m;
            if(last[s[i]]!=-1)
                DP[i]=(DP[i] - DP[last[s[i]]] + m)%m;
            last[s[i]]=i-1; //we can`t use repeated character in any subsequence that specific
            //character extended before, thats why i-1 is there
        }

        cout<<DP.back()<<"\n";
    }
}
