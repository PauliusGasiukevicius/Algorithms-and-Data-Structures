#include <bits/stdc++.h>
using namespace std;
#define ll long long

void update(vector<int>&BIT, int c, int x)
{
    for(;c<BIT.size();c+=(c&-c))
        BIT[c]+=x;
}

int query(vector<int>&BIT, int c)
{
    int ats=0;
    for(;c>0;c-=(c&-c))
        ats+=BIT[c];
    return ats;
}

int main()
{
    ios::sync_with_stdio(0);
    int t,n,m,q,l,r,v;
    cin>>t;

    while(t--)
    {
        cin>>n>>m;
        vector<int>BIT(n+2);

        while(m--)
            cin>>l>>r>>v,update(BIT,l+1,v),update(BIT,r+2,-v);

        cin>>q;

        while(q--)
        {
            cin>>r;
            cout<<query(BIT,r+1)<<"\n";
        }
    }
}
