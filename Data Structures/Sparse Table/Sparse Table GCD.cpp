#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

const int mxLog = 20;
const int mxN = 3e5;
int A[mxN+1];
int Log[mxN+1];//Logarithm only useful for queries like max/min/gcd
//where including same element twice does not matter
int st[mxN+1][mxLog+1];

void buildSparseTable(int n)
{
    Log[1]=0;
    for(int i=2; i<=mxN; i++)
        Log[i]=Log[i/2]+1;

    for(int k=0; k<=mxLog; k++)
        for(int i=1; i + (1<<k) - 1 <=mxN; i++)
            st[i][k]= k==0 ? A[i] : __gcd(st[i][k-1],st[i+(1<<(k-1))][k-1]);
}

int Get(int l, int r)
{
    int lg = Log[r-l+1];
    return __gcd(st[l][lg], st[r-(1<<lg)+1][lg]);
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n;
    cin>>n;
    for(int i=1; i<=n; i++)
        cin>>A[i];

    buildSparseTable(n);

    int mx = 0;
    vector<int>ats;

    for(int i=1; i<=n; i++)
    {
        int le = i, ri = n;
        while(le < ri)
        {
            int mi = (le+ri+1)/2;
            if(Get(i,mi)%A[i]==0)
                le=mi;
            else
                ri=mi-1;
        }
        int R = ri;
        le = 1, ri = i;
        while(le < ri)
        {
            int mi = (le+ri)/2;
            if(Get(mi,i)%A[i]==0)
                ri=mi;
            else
                le=mi+1;
        }
        int L = ri;
        if(R-L > mx)
        {
            mx=R-L;
            ats = {L};
        }
        else if(R-L == mx)
        {
            ats.push_back(L);
        }
    }
    sort(ats.begin(),ats.end());
    ats.erase(unique(ats.begin(),ats.end()),ats.end());
    cout<<ats.size()<<" "<<mx<<"\n";
    for(int&x:ats)
        cout<<x<<" ";
}
