#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

int main()
{
    ios::sync_with_stdio(0);
    int n,r,cs=1;
    while(cin>>n>>r && n)
    {
        string s = string(n-r,'0') + string(r,'1');
        vector<ld>P(n),ats(n);
        for(auto&p:P)cin>>p;
        ld pp = 0;

        do
        {
            ld x = 1.0;
            for(int i=0; i<s.size(); i++)
                if(s[i]=='1')x*=P[i];
                else x*=(1.0-P[i]);

            for(int i=0; i<s.size(); i++)
                if(s[i]=='1')ats[i]+=x;

            pp+=x;

        }while(next_permutation(s.begin(),s.end()));

        cout<<"Case "<<cs++<<":\n";
        for(auto&p:ats)
            cout<<setprecision(6)<<fixed<<p/pp<<"\n";
    }
}
