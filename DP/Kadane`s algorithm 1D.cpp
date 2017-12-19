#include <bits/stdc++.h>
using namespace std;

int main()
{
    ios::sync_with_stdio(0);
    int n;

        cin>>n;
        vector<int>A(n);
        for(int&x:A)cin>>x;
        int ats = A[0];
        int c = 0;

        for(int&x:A)
        {
            c+=x;
            ats=max(ats,c);
            c=max(x,0);
        }
        cout<<ats<<"\n";
}
