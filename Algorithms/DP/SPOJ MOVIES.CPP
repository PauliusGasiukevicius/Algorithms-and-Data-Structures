#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld double
#define oo 666666666
ll S,F;
map<string,vector<string>>G;
map<string,ll>IN;
map<pair<string,ll>,ll>buy1,buy2,DP,T;

ll rec(string cur, int mustBuy = 1)
{
    if(DP.count({cur,mustBuy}))return DP[{cur,mustBuy}];
    ll ats = oo;
    int tickets = 0;

    if(mustBuy)
    {
        ll costS = S;
        ll costF = F;
        int TS=1,TF=1;

        for(auto&p: G[cur])
        {
            costS+=rec(p);
            costF+=rec(p,0);
            TS+=T[{p,1}];
            TF+=T[{p,0}];
        }
        ats=min(costS,costF);
        tickets=min(TS,TF);

        if(ats==costF && (costS > costF || (costS==costF && TF==tickets)))
        {
            tickets=TF;
            for(auto&p : G[cur])
            {
                buy1[{cur,mustBuy}]+=buy1[{p,0}];
                buy2[{cur,mustBuy}]+=buy2[{p,0}];
            }
            buy2[{cur,mustBuy}]++;
        }
        else
        {
            tickets=TS;
            for(auto&p : G[cur])
            {
                buy1[{cur,mustBuy}]+=buy1[{p,1}];
                buy2[{cur,mustBuy}]+=buy2[{p,1}];
            }
            buy1[{cur,mustBuy}]++;
        }
    }
    else
    {
        ll costN = 0;
        ll costF = F;
        int TN=0,TF=1;

        for(auto&p: G[cur])
        {
            costN+=rec(p);
            costF+=rec(p,0);
            TN+=T[{p,1}];
            TF+=T[{p,0}];
        }
        ats=min(costN,costF);
        tickets=min(TN,TF);

        if(ats==costF && (costN > costF || (costN==costF && TF==tickets)))
        {
            tickets=TF;
            for(auto&p : G[cur])
            {
                buy1[{cur,mustBuy}]+=buy1[{p,0}];
                buy2[{cur,mustBuy}]+=buy2[{p,0}];
            }
            buy2[{cur,mustBuy}]++;
        }
        else
        {
            tickets=TN;
            for(auto&p : G[cur])
            {
                buy1[{cur,mustBuy}]+=buy1[{p,1}];
                buy2[{cur,mustBuy}]+=buy2[{p,1}];
            }
        }
    }

    T[{cur,mustBuy}]=tickets;
    return DP[{cur,mustBuy}]=ats;
}

void solve()
{
    static int cs = 1;
    DP.clear();
    T.clear();
    buy1.clear(),buy2.clear();
    ll ats1=0,ats2=0,total=0;

    for(auto&p: G)
        if(IN[p.first]==0)
        {
            total+=rec(p.first);
            ats1+=buy1[{p.first,1}];
            ats2+=buy2[{p.first,1}];
        }
    cout<<cs++<<". "<<ats1<<" "<<ats2<<" "<<total<<"\n";
}

void trimB(string&s)
{
    while(!s.empty() && iswspace(s.back()))
        s.pop_back();
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    string s,x;
    getline(cin,s);
    trimB(s);
        while(s.empty())getline(cin,s),trimB(s);
    stringstream ss(s);
    ss>>S>>F;

    while(getline(cin,s))
    {
        trimB(s);
        while(s.empty())getline(cin,s),trimB(s);;

        if(s[0]>='0' && s[0]<='9')
        {
            solve();
            stringstream ss(s);
            ss>>S>>F;
            if(S==0 && F==0)return 0;
            G.clear();
            IN.clear();
            continue;
        }
        stringstream ss(s);
        ss>>s;
        G[s];
        while(ss>>x)
        G[s].push_back(x),G[x],IN[x]++;
    }
}
