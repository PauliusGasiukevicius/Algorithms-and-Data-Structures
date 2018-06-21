#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

int main()
{
    ios::sync_with_stdio(0);
    int n;
    cin>>n;
    vector<int>A(n);
    for(int&x:A)cin>>x;
    vector<int>S;
    int ats = 0;

    for(int i=0; i<n; i++)
        if(S.empty())
        S.push_back(A[i]);
        else if(S.back() > A[i])
            ats=max(ats,S.back()^A[i]),S.push_back(A[i]);
        else if(S.back() < A[i])
        {
            while(!S.empty() && S.back() < A[i])
                ats=max(ats,S.back()^A[i]),S.pop_back();
            if(!S.empty())ats=max(ats,S.back()^A[i]);
                S.push_back(A[i]);
        }

    cout<<ats<<"\n";
}
