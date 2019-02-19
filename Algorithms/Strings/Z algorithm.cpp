#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 666666666

//z[i] - longest common prefix of string s and suffix of s that starts at i
vector<int> z_function(string s) {
    int n = (int) s.length();
    vector<int> z(n);
    z[0]=n;
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r)
            z[i] = min (r - i + 1, z[i - l]);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]])
            ++z[i];
        if (i + z[i] - 1 > r)
            l = i, r = i + z[i] - 1;
    }
    return z;
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    string s;
    cin>>s;
    auto z = z_function(s);
    vector<int>A = z;
    sort(A.begin(),A.end());

    vector<array<int,2>>ats;

    for(int k=1; k<=s.size(); k++)
        if(z[s.size()-k]==k)
            ats.push_back({k,A.end()-lower_bound(A.begin(),A.end(),k)});

    cout<<ats.size()<<"\n";
    for(auto&a:ats)
        cout<<a[0]<<" "<<a[1]<<"\n";
}
