/* Finding if you can partition a set into 2 parts, such that their sums are equal */
#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(0);
    int n;
        cin>>n;
        int sum = 0;
        vector<int>A(n);
        for(int&x:A)cin>>x,sum+=x;

        if(sum&1)
        {
            cout<<"NO\n";
            return 0;
        }

        vector<int>ats(sum/2 + 1,0);
        ats[0]=1;

        for(int i=0; i<n; i++)
            for(int j=ats.size()-1 - A[i]; j>=0; j--)
                if(ats[j]!=0)
                ats[j+A[i]]=1;

        if(ats[sum/2]!=0)
            cout<<"YES\n";
        else
            cout<<"NO\n";
}
