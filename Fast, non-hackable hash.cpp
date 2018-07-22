#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;
#define ll long long
#define ld long double
#define oo INT_MAX/2

const int RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
struct chash {
    int operator()(int x) const { return hash<int>{}(x ^ RANDOM); }
};
gp_hash_table<int, string, chash> mp;


int main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    mp[666]=":)";
    cout<<mp[666]<<"\n";
}
