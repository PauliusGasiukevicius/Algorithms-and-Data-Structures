#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo INT_MAX/2

int main()
{
    ios::sync_with_stdio(0);
    int q;
    cin>>q;

    ll XOR = 0;
    vector<ll>X(1),Y(1),U(1);
    priority_queue<pair<ll,ll>>q1,q2,q3,q4;

    while(q--)
    {
        char ch;
        cin>>ch;

        if(ch=='+')
        {
            ll x,y;
            cin>>x>>y;
            x^=XOR;
            y^=XOR;
            X.push_back(x);
            Y.push_back(y);
            U.push_back(0);
            ll i = X.size()-1;
            q1.push({-x-y,i});
            q2.push({x-y,i});
            q3.push({-x+y,i});
            q4.push({x+y,i});
        }

        if(ch=='-')
        {
            int idx;
            cin>>idx;
            idx^=XOR;
            U[idx]=1;
        }

        if(ch=='?')
        {
            int a,b;
            cin>>a>>b;
            a^=XOR;
            b^=XOR;
            while(U[q1.top().second])q1.pop();
            while(U[q2.top().second])q2.pop();
            while(U[q3.top().second])q3.pop();
            while(U[q4.top().second])q4.pop();

            ll ats = max({
                a+b+q1.top().first,
                -a+b+q2.top().first,
                a-b+q3.top().first,
                -a-b+q4.top().first
                         });

            cout<<ats<<"\n";
            XOR=ats;
        }
    }
}
