#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

int DP[101][101][101];
int jump[101][256];
string a,b,s;

int solve(int i, int j, int k){
    if(i >= a.size() || j >= b.size() || k >=s.size())return 0;
    if(DP[i][j][k]!=-1)return DP[i][j][k];

    int ats = max(solve(i,j+1,k),solve(i+1,j,k));
    if(a[i]==b[j] && jump[k][a[i]]<s.size())
        ats=max(ats,1 + solve(i+1,j+1,jump[k][a[i]]));

    return DP[i][j][k] = ats;
}

string restore(){
    string ats;
    int i =0, j=0, k=0;
    int left = solve(i,j,k);

    while(left > 0 && i < a.size() && j < b.size())
    {
        if(solve(i+1,j,k)==left)i++;
        else if(solve(i,j+1,k)==left)j++;
        else if(a[i]==b[j] && jump[k][a[i]]!=s.size())
            {
                ats.push_back(a[i]);
                k=jump[k][a[i]];
                i++,j++;
                left--;
            }
        else break;
    }
    return ats;
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    memset(DP, -1, sizeof DP);
    cin>>a>>b>>s;

    for(int i=0; i<=s.size(); i++)
    for(char ch='A'; ch<='Z'; ch++)
    {
        string pf = s.substr(0,i);
        pf.push_back(ch);
        int pos = s.find(pf);
        int nxt = pos!=0 ? 0 : pf.size();
        jump[i][ch]= max(jump[i][ch], nxt);

        while(pf.size() > 1)
        {
            pf.erase(pf.begin());
            pos = s.find(pf);
            nxt = pos!=0 ? 0 : pf.size();
            jump[i][ch]= max(jump[i][ch], nxt);
        }
    //    if(jump[i][ch]==s.size())cout<<i<<" "<<ch<<"\n";
    }
    //cout<<solve(0,0,0)<<"\n";
    if(solve(0,0,0)==0)cout<<"0\n";
    else cout<<restore();
}
