#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define oo LLONG_MAX/2

int main()
{
    ios::sync_with_stdio(0);
    int t,cs=1;
    cin>>t;
    map<string,int>mp;
    map<int,string>rmp;
    mp["January"]=0;
    mp["February"]=1;
    mp["March"]=2;
    mp["April"]=3;
    mp["May"]=4;
    mp["June"]=5;
    mp["July"]=6;
    mp["August"]=7;
    mp["September"]=8;
    mp["October"]=9;
    mp["November"]=10;
    mp["December"]=11;

    for(auto&p:mp)
        rmp[p.second]=p.first;
    int Months[]={31,28,31,30,31,30,31,31,30,31,30,31};
    int Leap[]={31,29,31,30,31,30,31,31,30,31,30,31};

    while(t--)
    {
        int y1,y2,m1,m2,d1,d2;
        char c;
        string s;
        cin>>s>>d1>>c>>y1;
        m1=mp[s];
        cin>>s>>d2>>c>>y2;
        m2=mp[s];

        int ats = 0;

        if(m1>1)y1++;

        if(m2<1 || (m2==1 && d2<29))y2--;

        ats = y2/4 - y2/100 + y2/400 - (y1-1)/4 + (y1-1)/100 - (y1-1)/400;

        cout<<"Case "<<cs++<<": "<<ats<<"\n";
    }
}
