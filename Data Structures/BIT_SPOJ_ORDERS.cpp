#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld double
#define oo 666666666

void add(vector<int>&BIT, int c, int v)
{
    for(;c<BIT.size();c+=c&-c)
        BIT[c]+=v;
}

int get(vector<int>&BIT, int c, int s=0)
{
    for(;c;c-=c&-c)
        s+=BIT[c];
    return s;
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    int t,n;
    cin>>t;
    while(t--)
    {
        cin>>n;
        vector<int>BIT(n+1);
        vector<int>A(n+1),ats(n+1);
        for(int i=1; i<=n; i++)
            cin>>A[i],add(BIT,i,1);

        for(int i=n; i>=1; i--)
        {
            int l = 1, r = n;
            while(l<r)
            {
                int m = (l+r+1)/2;
                int x = get(BIT,n,-get(BIT,m-1));
                if(x>=A[i]+1)
                    l=m;
                else
                    r=m-1;
            }
            ats[i]=r;
            add(BIT,r,-1);
        }

        for(int i=1; i<=n; i++)
            cout<<ats[i]<<(i==n?"\n":" ");
    }
}
