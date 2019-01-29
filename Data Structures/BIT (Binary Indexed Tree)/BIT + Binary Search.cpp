#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

void add(vector<int>&BIT, int c, int x)
{
    for(c;c<BIT.size(); c+=c&-c)
        BIT[c]+=x;
}

int get(vector<int>&BIT, int c)
{
    int sum = 0;
    for(c;c;c-=c&-c)
        sum+=BIT[c];
    return sum;
}

int main()
{
    ios::sync_with_stdio(0);
    int t,n;
    cin>>t;

    while(t--)
    {
        cin>>n;
        vector<int>BIT(n+1);
        for(int i=1; i<=n; i++)
            add(BIT,i,1);

        for(int j=0; j<n; j++)
        {
            int k;
            cin>>k;
            k++;

            //finds k-th smallest active element in BIT
            int l = 1, r = n;

            while(l<r)
            {
                int m = (l+r)/2;

                if(get(BIT,m) < k)
                    l=m+1;
                else
                    r=m;
            }

            cout<<r<<(j+1==n?"\n":" ");
            add(BIT,r,-1);
        }
    }
}
