#include <bits/stdc++.h>
using namespace std;

int DP[5001][5001];
/*
* min number of insertions to make string a palindrome = string size - LCS of string and its reverse
* Longest repeatings subsequence is LCS on string with itself with extra condition that i!=j
*/
int main()
{
    ios::sync_with_stdio(0);
    string s,r;
    cin>>s>>r;

    for(int i=1; i<=s.size(); i++)
        for(int j=1; j<=r.size(); j++)
        if(s[i-1]==r[j-1])
        DP[i][j]=DP[i-1][j-1] + 1;
    else DP[i][j] = max(DP[i-1][j],DP[i][j-1]);

    cout<<DP[s.size()][r.size()]<<"\n";
}
