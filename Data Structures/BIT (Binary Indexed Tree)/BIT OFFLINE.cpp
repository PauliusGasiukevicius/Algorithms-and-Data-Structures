#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

const int N = 1000001;
int BIT[N];

void add(int c, int x)
{
    for(c;c<N;c+=c&-c)
        BIT[c]+=x;
}

int get(int c)
{
    int s=0;
    for(c;c;c-=c&-c)
        s+=BIT[c];
    return s;
}

int main()
{
    ios::sync_with_stdio(0);
    int n,q;
    cin>>n;
    vector<int>A(n+1), last(N+1,-1);
    for(int i=1; i<=n; i++)
        cin>>A[i];

    cin>>q;
    vector<int>ats(q);
    vector<vector<pair<int,int>>>Q(n+1);
    for(int i=0; i<q; i++)
    {
        int l,r;
        cin>>l>>r;
        Q[r].push_back({l,i});
    }

    for(int i=1; i<=n; i++)
    {
        if(last[A[i]]!=-1)
            add(last[A[i]],-1);
        last[A[i]]=i;
        add(i,1);

        for(auto&v : Q[i])
        {
            int l = v.first;
            int idx = v.second;
            ats[idx] = get(i) - get(l-1);
        }
    }

    for(int i=0; i<q; i++)
    cout<<ats[i]<<"\n";
}
