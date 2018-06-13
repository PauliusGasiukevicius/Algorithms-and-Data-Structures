#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

int main()
{
    ios::sync_with_stdio(0);
    int n,cs=0;
    while(cin>>n)
    {
        if(cs)cout<<"\n";
        cs++;
        vector<vector<int>>A(n+1,vector<int>(n+1));
        int r = 1,c=(n+1)/2;
        int nxt = 1;

        while(nxt <= n*n)
        {
            A[r][c]=nxt++;
            int oldr=r, oldc=c;
            r--,c++;
            if(r<1 && c>n)r=oldr+1,c=oldc;
            if(r<1)r=n;
            if(c>n)c=1;
            if(A[r][c])r=oldr+1, c=oldc;
        }

        cout<<"n="<<n<<", sum="<<(n*n+1)*n/2<<"\n";
        int w = floor(log10(n*n))+1;
        for(int i=1; i<=n; i++)
            {
                cout<<" ";
                for(int j=1; j<=n; j++)
            cout<<setw(w)<<A[i][j]<<(j==n?"\n":" ");
            }
    }
}
