#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

/*
You would like to write a list of positive integers 1,2,3,… using your computer.
However, you can press each key 0–9 at most n times during the process.
What is the last number you can write?
*/

ll DP[21][2][21]; //[position][is current number == prefix of limit or less ?][how much ones we have]

ll solve(vector<int>&digits, int pos, int pf, int ones, int needOnes)
{
    //cout<<pos<<" "<<pf<<" "<<ones<<"\n";
    if(pos>=digits.size())return ones==needOnes;
    if(DP[pos][pf][ones]!=-1)return DP[pos][pf][ones];

    DP[pos][pf][ones]=0;
    for(int j=0; j<=(pf ? digits[pos] : 9); j++)
    DP[pos][pf][ones]+=solve(digits,pos+1,pf&(j==digits[pos]),ones + (j==1), needOnes);

    return DP[pos][pf][ones];
}

ll need(ll m)
{
    vector<int>digits;
    while(m > 0)
        digits.push_back(m%10),m/=10;
    reverse(digits.begin(),digits.end());

    ll ats = 0;
    for(int j=1; j<=digits.size(); j++)
    {
        memset(DP,-1,sizeof DP);
        ats+=solve(digits,0,1,0,j)*j;
    }
    return ats;
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    ll n;
    cin>>n;
    ll l = 0, r = 1000000000000000000LL;

    while(l<r)
    {
        ll m = (l+r+1)/2;
        if(need(m)<=n)
            l=m;
        else r=m-1;
    }
    cout<<r;
}
