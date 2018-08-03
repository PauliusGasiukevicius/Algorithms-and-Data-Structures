#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld double
#define oo 666666666

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
const int RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
struct chash {int operator()(int x) const { return hash<int>{}(x ^ RANDOM); }};
gp_hash_table<int, int, chash> mp;

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
    int q;
    cin>>q;
    vector<pair<char,int>>Q(q);
    vector<int>A;
    for(auto&p:Q)
    {
        cin>>p.first>>p.second;
        if(p.first!='K')
            A.push_back(p.second);
    }

    sort(A.begin(),A.end());
    A.erase(unique(A.begin(),A.end()),A.end());
    for(int i=0; i<A.size(); i++)
        mp[A[i]]=i+1;

    int n = A.size();
    vector<int>BIT(A.size()+1);
    bitset<200001>in(0);

    for(auto&p:Q)
    if(p.first=='D')
    {
        int pos = mp[p.second];
        if(!in[pos])continue;
        in[pos]=0;
        add(BIT,pos,-1);
    }
    else if(p.first=='I')
    {
        int pos = mp[p.second];
        if(in[pos])continue;
        in[pos]=1;
        add(BIT,pos,1);
    }
    else if(p.first=='K')
    {
        int k = p.second;
        int total = get(BIT,n);
        if(total < k)
        {
            cout<<"invalid\n";
            continue;
        }

        int l = 1, r = n;
        while(l<r)
        {
            int m = (l+r)/2;
            int sum = get(BIT,m);

            if(sum < k)
                l=m+1;
            else
                r=m;
        }

        cout<<A[r-1]<<"\n";
    }
    else
    {
        int pos = mp[p.second];
        cout<<get(BIT,pos-1)<<"\n";
    }
}
