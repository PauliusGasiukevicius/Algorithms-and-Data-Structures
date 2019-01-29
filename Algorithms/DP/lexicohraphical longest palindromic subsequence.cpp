#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

int DP[1001][1001];
vector<int>pos[256];
string s;
int n;
int solve(int i, int j)//Longest Palindromic subsequence
{
    if(i > j)return 0;
    if(i==j)return 1;
    if(i+1==j && s[i]==s[j])return 2;
    if(DP[i][j]!=-1)return DP[i][j];
    if(s[i]==s[j])return DP[i][j] = 2 + solve(i+1,j-1);
    return DP[i][j] = max(solve(i+1,j), solve(i,j-1));
}

string lex(int l, int r)
{
    if(l>r)return "";
    if(l==r)return s.substr(r,1);
    int opt = solve(l,r);
    for(char i='a'; i<='z'; i++)
    {
        auto L = lower_bound(pos[i].begin(),pos[i].end(),l);
        auto R = upper_bound(pos[i].begin(),pos[i].end(),r);
        if(L==pos[i].end() || R==pos[i].begin())continue;
        R--;
        if(*L > r || *R < l)continue;

        if(*L!=*R && 2+solve(*L+1,*R-1)==opt)
            return s.substr(*L,1)+lex(*L+1,*R-1)+s.substr(*R,1);
        else if(*L==*R && 1==opt)
            return s.substr(*L,1);
    }
    return "";
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    while(cin>>s)
    {
        n = s.size();
        for(int i=0; i<n; i++)
        for(int j=0; j<n; j++)
        DP[i][j]=-1;

        for(int i='a'; i<='z'; i++)
            pos[i].clear();

        for(int i=0; i<n; i++)
            pos[s[i]].push_back(i);

        cout<<lex(0,n-1)<<"\n";
    }
}
