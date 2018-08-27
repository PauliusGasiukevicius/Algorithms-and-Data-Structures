#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    int n;
    cin>>n;
    vector<int>A(n);
    for(int&x:A)cin>>x;
    ll ats = 0;
    vector<int>S;

    for(int i=0; i<n; i++)
        if(S.empty() || A[i] >= A[S.back()])
        S.push_back(i);
        else
        {
            while(!S.empty() && A[S.back()] > A[i])
            {
                int top = S.back();
                S.pop_back();
                if(S.empty())ats=max(ats,1LL*i*A[top]);
                else ats=max(ats,(i-S.back()-1LL)*(A[top]));
            }
            S.push_back(i);
        }

    while(!S.empty())
    {
        int top = S.back();
        S.pop_back();
        if(S.empty())ats=max(ats,1LL*n*A[top]);
        else ats=max(ats,(n-S.back()-1LL)*(A[top]));
    }

    cout<<ats;
}
