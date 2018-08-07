#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

bool good(ll x)
{
    while(x>10)
    {
        if(x%100==13)return 0;
        x/=10;
    }
    return 1;
}

int brute(int start, int digits)
{
    int cnt = 0;
    int c = start;

    for(int i=0; i<10000; i++)
    {
        string s = to_string(i);
        if(s[0]-'0'==start && s.size()==digits)
            {
                cnt+=good(i);
                if(good(i))
                    cout<<i<<"\n";
            }
    }
    return cnt;
}

ll DP[31][31]={};//number of [N][] digit numbers that start with [][X] and have no "13" substring
ll sum[31]={}; //sum of N-digit numbers without "13"

ll cnt(ll x)//calculates number of numbers in range [1,x] that do not have "13" as a substring
{
    string s = to_string(x);
    int n = s.size();
    ll ats = 0;
    for(int i=0; i+1<s.size(); i++)
        if(s[i]=='1' && s[i+1]=='3')
    {
        s[i+1]--;
        i+=2;
        for(i; i<n; i++)s[i]='9';
        break;
    }

    while(s.back()!='0')
    {
        x = stoll(s);
        while(x > 0 && x%10!=0)
        {
            if(good(x))ats++;
            x--;
        }
        while(!good(x))
            x--;
        s = to_string(x);
    }

    //cout<<ats<<" "<<s<<"\n";
    if(1||s.size()==1)s = "0"+s;
    n=s.size();

    for(int i = n-2; i>=0; i--)
    {
        while(s[i]>'0')
        {
            if(s.find("13")!=-1)
            {
                s[i]--;
                continue;
            }
            ll extend = 0;

            for(int j=0; j<10; j++)//how to extend current number
                if(!(s[i]=='2' && j==3))
                    ats+=DP[n-i-1][j],extend+=DP[n-i-1][j];

            //cout<<s<<" "<<i<<" "<<extend<<"\n";
            s[i]--;
        }
    }

    return ats;
}

ll bruteLessThanN(ll x)
{
    ll ats = 0;
    while(x > 0)
        ats+=good(x),x--;
    return ats;
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    freopen("hotel.in","r",stdin);
    freopen("hotel.out","w",stdout);
    for(int i=0; i<10; i++)
        DP[1][i]=1;

    for(int i=2; i<31; i++)
        for(int j=0; j<10; j++)//cur digit
        for(int k=0; k<10; k++)//last digit
            if(j==1 && k==3)continue;
            else DP[i][j]+=DP[i-1][k];

    for(int i=1; i<31; i++)
        for(int j=1; j<10; j++)
        sum[i]+=DP[i][j];

    ll n, t;
    cin>>t;

    while(t--)
    {
    ll l = 0, r = LLONG_MAX;
    cin>>n;

    while(l<r)
    {
        ll m = l + (r-l)/2;
        if(cnt(m) < n)
            l=m+1;
        else r=m;
    }
    cout<<r<<"\n";
    }
}
