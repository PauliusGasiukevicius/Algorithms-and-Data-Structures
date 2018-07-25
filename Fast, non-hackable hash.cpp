#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
using namespace std;
#define ll long long
#define ld long double
#define oo INT_MAX/2

const int RANDOM = chrono::high_resolution_clock::now().time_since_epoch().count();
struct chash {
    int operator()(int x) const { return hash<int>{}(x ^ RANDOM); } //example of custom hash function
};
struct pair_hash { 
    template <class T1, class T2>
    std::size_t operator () (const std::pair<T1,T2> &p) const {
        auto h1 = std::hash<ll>{}((p.first<<31LL) | p.second);
        return h1 ^ RANDOM;
    }
};
gp_hash_table<int, string, chash> mp;
//theres also cc_hash_table and unordered_map, sometimes work better for some kinds of problems

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);
    mp[666]=":)";
    cout<<mp[666]<<"\n";
}
