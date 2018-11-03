#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

string minimalRotation(string s)
{
    int n = s.size();
    s+=s;
    int have[256]={};
    for(auto&ch:s)have[ch]++;
    vector<int>pos;

    for(int j='a'; j<='z'; j++)
        if(have[j])
        {
            for(int i=0; i<s.size(); i++)
                if(s[i]==j)
                if(i==0 || s[i]!=s[i-1])pos.push_back(i);

            int bestSame = 0;
            char bestLast = 0;
            int ats = 0;

            for(auto c:pos)
            {
                int st = c;
                int same = 1;
                int last = j;
                while(c+1 < s.size())
                {
                    ++c;
                    if(s[c]==last)same++;
                    else
                    {
                        last=s[c];
                        break;
                    }
                }

                if(bestSame < same || (bestSame==same && last < bestLast))
                {
                    ats=st;
                    bestSame = same;
                    bestLast = last;
                }
            }

            return s.substr(ats,n);
        }
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    string s;
    cin>>s;
    cout<<minimalRotation(s);
}
