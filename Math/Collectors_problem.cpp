#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

int main()
{
    ios::sync_with_stdio(0);
    /*
        Expected number of stickers to collect all N different stickers, when all 1...N stickers
        have same probability of appearing
    */
    int t,n;
    cin>>t;
    while(t--)
    {
        cin>>n;
        ld EX = 0;
        for(int i=1; i<=n; i++)
            EX+=1.0*n/i;
        cout<<setprecision(2)<<fixed<<EX<<"\n";
    }
}
