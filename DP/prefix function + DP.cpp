#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

/*
Your task is to calculate the number of strings of length n whose substring is a given string of length m.
All strings consist of characters A–Z.
*/

ll DP[1001][101];
ll M = 1e9+7;
string s;
int n;
vector<int>KMP;
int jump[101][256];

vector<int> KMP_table(string&a)
{
    vector<int>KMP(a.size());
    for(int i=1,j=0; i<a.size(); i++)
        if(a[i]==a[j])KMP[i]=j+1,j++;
        else
        {
            while(a[i]!=a[j] && j)
                j=KMP[j-1];
            KMP[i]=(a[i]==a[j] ? j+1 : 0);
        }
    return KMP;
}

ll solve(int pos, int pf)
{
    if(pos==n)return pf>=s.size();
    if(DP[pos][pf]!=-1)return DP[pos][pf];
    ll ats = 0;

    for(int j='A'; j<='Z'; j++)
        if(pf>=s.size() || s[pf]==j)ats=(ats + solve(pos+1,min(pf+1,(int)s.size())))%M;
        else ats = (ats + solve(pos+1,jump[pf][j]))%M;

    return DP[pos][pf]=ats;
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    cin>>n>>s;

    KMP = KMP_table(s);
    for(int i=0; i<s.size(); i++)
        for(int j='A'; j<='Z'; j++)
    {
        int pos = (i ? KMP[i-1] : 0);
        while(pos)
        {
            if(s[pos]==j)break;
            pos = KMP[pos-1];
        }
        jump[i][j]=pos + (s[pos]==j);
    }

    for(int i=0; i<=n; i++)
        for(int j=0; j<=s.size(); j++)
        DP[i][j]=-1;
    cout<<solve(0,0);
}
