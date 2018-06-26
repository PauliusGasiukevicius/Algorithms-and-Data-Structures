#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo INT_MAX/2

int main()
{
    ios::sync_with_stdio(0);
    int t,n;
    cin>>t;

    while(t--)
    {
        cin>>n;
        vector<vector<int>>A(n,vector<int>(2));
        for(int i=0; i<n; i++)
            cin>>A[i][0]>>A[i][1];

        sort(A.begin(),A.end(),[](vector<int>a, vector<int>b)
             {
                 if(a[0]!=b[0])return a[0] < b[0];
                 return a[1] > b[1];
             }
             );
        vector<int>B;
        for(int i=n-1; i>=0; i--)
            B.push_back(A[i][1]);

        vector<int>temp(n);
        int k = 0;
        for(int i=1; i<n; i++)
            if(B[i] >= B[temp[k]])
            temp[++k]=i;
            else
            {
                int l = 0, r = k;
                while(l < r)
                {
                    int m = (l+r)/2;
                    if(B[i] >= B[temp[m]])
                        l=m+1;
                    else
                        r=m;
                }
                temp[r]=i;
            }
        cout<<k+1<<"\n";
    }
}
