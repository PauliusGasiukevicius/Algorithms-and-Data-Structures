#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

void add(vector<int>&BIT, int c, int v=1)
{
    for(;c<BIT.size();c+=c&-c)
        BIT[c]+=v;
}

int get(vector<int>&BIT, int c, int s = 0)
{
    for(;c;c-=c&-c)
        s+=BIT[c];
    return s;
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    int n;
    cin>>n;
    vector<array<int,3>>A(n);
    vector<int>ats(n+1),BIT(100001);
    for(int i=0; i<n; i++)
        cin>>A[i][0]>>A[i][1],A[i][2]=i+1;
    sort(A.begin(),A.end());

    for(int i=0; i<n; i++)
    {
        if(i && A[i][1]==A[i-1][1] && A[i][0]==A[i-1][0])
            ats[A[i][2]]=ats[A[i-1][2]];
        else ats[A[i][2]]=get(BIT,A[i][1]);
        add(BIT,A[i][1]);
    }

    for(int i=1; i<=n; i++)
        cout<<ats[i]<<"\n";
}
