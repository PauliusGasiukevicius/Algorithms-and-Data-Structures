#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

string toRoman(string s)
{
    ll x;
    stringstream ss(s);
    ss>>x;

    map<int,string,greater<int>>mp;
    mp[1]="I";mp[4]="IV";mp[5]="V";mp[9]="IX";mp[10]="X";mp[40]="XL";mp[50]="L";
    mp[90]="XC";mp[100]="C";mp[400]="CD";mp[500]="D";mp[900]="CM";mp[1000]="M";

    string ats;
    while(x > 0)
    {
        for(auto&p:mp)
            if(p.first<=x)
        {
            x-=p.first;
            ats+=p.second;
            break;
        }
    }
    return ats;
}

ll toArabic(string s)
{
    ll ats=0;
    map<string,int>mp;
    mp["I"]=1;mp["IV"]=4;mp["V"]=5;mp["IX"]=9;mp["X"]=10;mp["XL"]=40;mp["L"]=50;
    mp["XC"]=90;mp["C"]=100;mp["CD"]=400;mp["D"]=500;mp["CM"]=900;mp["M"]=1000;

    for(int i=0; i<s.size(); i++)
    {
        ats+=mp[s.substr(i,1)];
        if(i && mp.count(s.substr(i-1,2)))
            ats = ats + mp[s.substr(i-1,2)] - mp[s.substr(i-1,1)] - mp[s.substr(i,1)];
    }
    return ats;
}

int main()
{
    ios::sync_with_stdio(0);
    string s;
    while(cin>>s)
    {
        if(isdigit(s[0]))
            cout<<toRoman(s)<<"\n";
        else
            cout<<toArabic(s)<<"\n";
    }
}
