#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

string negBinary(int value)
{
    if(value==0)return "0";
    string ats = "";

    while (value != 0)
	{
		int remainder = value % -2;
		value = value / -2;

		if (remainder < 0)
		{
			remainder += 2;
			value += 1;
		}

		ats+=to_string(remainder);
	}

    reverse(ats.begin(),ats.end());
	return ats;
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    int n;
    cin>>n;
    cout<<negBinary(n)<<"\n";
}
