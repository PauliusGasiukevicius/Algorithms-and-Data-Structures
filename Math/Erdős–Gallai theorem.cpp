#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

int main()
{
    ios::sync_with_stdio(0);
    int n;
    while(cin>>n && n)
    {
        vector<int>A(n);
        for(int&x:A)cin>>x;
        sort(A.rbegin(),A.rend());
        bool ok =1;
        if(accumulate(A.begin(),A.end(),0)&1)ok=0;
        if(A[0] < 0)ok=0;

        for(int k=0; k<n; k++)
        {
            int s = 0;
            int sk = 0;
            for(int j=0; j<=k; j++)
                sk+=A[j];

            for(int j=k+1; j<n; j++)
                s+=min(A[j],k+1);
            if(sk > k*(k+1)+s)ok=0;
        }
        if(ok)cout<<"Possible\n";
        else cout<<"Not possible\n";
    }
}

