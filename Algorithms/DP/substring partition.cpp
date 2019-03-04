#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

vector<int> prefix_function(string s) {
    int n = (int)s.length();
    vector<int> pi(n);
    for (int i = 1; i < n; i++) {
        int j = pi[i-1];
        while (j > 0 && s[i] != s[j])
            j = pi[j-1];
        if (s[i] == s[j])
            j++;
        pi[i] = j;
    }
    return pi;
}

//returns vector of indexes, if some index i is in array it means that b[i:i+a.size()]==a
vector<int> get_matches(string&a, string&b){
    vector<int> P=prefix_function(a);
    int i=0,j=0;
    vector<int>ats;

    while(i<b.size())
        if(a[j]==b[i])
        {
            if(j+1==a.size())
            {
                ats.push_back(i-j);
                j=P[j];
                i++;
            }else i++,j++;
        }
        else
        {
            if(j)j=P[j-1];
            else i++;
        }
    return ats;
}

ll mod = 1e9+7;
ll DP[100005];
ll sumDP[100005];
ll sumSumDP[100005];
ll ok[100005];

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    string a,b;
    cin>>a>>b;
    auto M = get_matches(b,a);
    for(auto&x:M)
        ok[x+b.size()]=1;

    int n = a.size();

    for(int i=1; i<=n; i++)
        {
            if(!ok[i])DP[i]=DP[i-1];
            else
            {
                //i-b.size()+1 - number of ways to choose start of current substring
                DP[i]=i-b.size()+1+sumSumDP[i-b.size()];
                DP[i]%=mod;
                if(DP[i]<0)DP[i]+=mod;

                /*O(n^3) for clarity, before prefix sums
                for(int j=0; j<=i-b.size()+1; j++)//start of current substring
                    for(int k=0; k<j; k++)//we can extend all string s[:k] to [:j-1]
                    DP[i]=(DP[i] + DP[k])%mod;// so essentially we just choose how large substring containing
                    //[i-b.size()+1 : i] will be, and then just try all possibilities for previous substrings part
                */
            }
            sumDP[i] = (sumDP[i-1] + DP[i])%mod;
            sumSumDP[i]=(sumSumDP[i-1] + sumDP[i])%mod;
        }

    ll ats = 0;
    for(int i=1; i<=n; i++)
    ats=(ats+DP[i])%mod;

    cout<<ats;
}
