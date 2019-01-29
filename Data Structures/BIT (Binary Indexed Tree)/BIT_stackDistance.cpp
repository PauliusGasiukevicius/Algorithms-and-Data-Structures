#include <bits/stdc++.h>
using namespace std;
#define ll long long

void add(vector<int>&BIT, int c, int val)
{
    for(;c<BIT.size(); c+=c&-c)
        BIT[c]+=val;
}

int query(vector<int>&BIT, int c)
{
    int s=0;
    for(;c;c-=c&-c)
        s+=BIT[c];
    return s;
}

int main()
{
    ios::sync_with_stdio(0);
    int t,n,q;
    cin>>t;
    while(t--)
    {
        cin>>n>>q;
        vector<int>BIT(n+q+2);
        vector<int>pos(n+1);

        for(int i=1; i<=n; i++)
            pos[i]=q+i,add(BIT,i+q,1);

        for(int k=0; k<q; k++)
        {
            int a;
            cin>>a;
            int ats = query(BIT,pos[a]-1);
            add(BIT,pos[a],-1);
            pos[a]=q-k;
            add(BIT,pos[a],1);
            cout<<ats<<" ";
        }
        cout<<"\n";
    }
}
