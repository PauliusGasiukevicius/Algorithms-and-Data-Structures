#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo INT_MAX/2

int main()
{
    ios::sync_with_stdio(0);
    int t,n,k;
    cin>>t;
    while(t--)
    {
        cin>>k>>n;
        priority_queue<int>l;
        priority_queue<int,vector<int>,greater<int>>r;

        for(int i=1; i<=n; i++)
        {
            int x;
            cin>>x;
            if(r.empty() || r.top() <= x)r.push(x);
            else l.push(x);

            while(!l.empty() && r.size() < k)
                r.push(l.top()),l.pop();

            while(r.size() > k)
                l.push(r.top()),r.pop();

            if(i<k)cout<<"-1 ";
            else cout<<r.top()<<(i==n?"\n":" ");
        }
    }
}
