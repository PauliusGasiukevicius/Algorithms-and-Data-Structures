#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

/*
PROG: buylow
LANG: C++14
*/

int main()
{
    ios::sync_with_stdio(0);
    freopen("buylow.in","r",stdin);
    freopen("buylow.out","w",stdout);
    int n;
    cin>>n;
    vector<ll>A(n+1),DP(n+1,1),cnt(n+1,1);

    for(int i=1; i<=n; i++)
        cin>>A[i];

    for(int i=2; i<=n; i++)
        {
            map<pair<int,int>,int>saw;
            for(int j=1; j<i; j++)
        if(A[j] > A[i])
        {
            if(DP[i] < DP[j] + 1)
                cnt[i] = cnt[j],DP[i]=DP[j]+1,saw[{A[j],DP[j]}]=cnt[j];
            else if (DP[i]==DP[j]+1 && !saw.count({A[j],DP[j]}))
                cnt[i]+=cnt[j],saw[{A[j],DP[j]}]=cnt[j];
            else if(DP[i]==DP[j]+1 && cnt[j] > saw[{A[j],DP[j]}])
                cnt[i]-=saw[{A[j],DP[j]}],cnt[i]+=cnt[j],saw[{A[j],DP[j]}]=cnt[j];
        }
        }

       /*
    for(int i=1; i<=n; i++)cout<<A[i]<<(i==n?"\n":"  ");
    for(int i=1; i<=n; i++)cout<<DP[i]<<(i==n?"\n":"  ");
    for(int i=1; i<=n; i++)cout<<cnt[i]<<(i==n?"\n":"  ");*/


    ll ats = 0,mx = *max_element(DP.begin(),DP.end());
    ll last = -oo;
    for(int i=n; i>=1; i--)
    if(DP[i]==mx && A[i]!=last)
    ats+=cnt[i],last=A[i];

    cout<<mx<<" "<<ats<<"\n";
}
