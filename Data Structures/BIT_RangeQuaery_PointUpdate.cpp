#include <bits/stdc++.h>
using namespace std;
#define ll long long

int BIT[1000001];
int N = 1000000;

void update(int c, int x)
{
    while(c <= N)
    {
        BIT[c]+=x;
        c+=(c & -c);
    }
}

int query(int c)
{
    int ats = 0;
    while(c > 0)
    {
        ats+=BIT[c];
        c-=(c&-c);
    }
    return ats;
}

int main()
{
    ios::sync_with_stdio(0);
    int q,x,l,r,pos=1;
    cin>>q;
    char ch;

    while(q--)
    {
        cin>>ch;
        if(ch=='+')
            cin>>x,update(pos++,x);
        else
        {
            cin>>l>>r;
            cout<<query(r)-query(l-1)<<"\n";
        }
    }
}
