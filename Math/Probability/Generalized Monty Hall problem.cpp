#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

int main()
{
    ios::sync_with_stdio(0);
    ll cows,cars,open;
    while(cin>>cows>>cars>>open)
    {
        ld ats = 0.0;
        //Using Strategy to always change doors
        //Case 1: we select a Cow door
        ats+=1.0*cows/(cows+cars) * (cars) / (cars+cows-1-open);
        //Case 2: we select a Car door
        ats+=1.0*cars/(cows+cars) * (cars-1) / (cars+cows-1-open);

        cout<<setprecision(5)<<fixed<<ats<<"\n";
    }
}
