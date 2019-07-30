#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 1234567890

//If min is needed instead of max, just add lines as insert_line(-a, -m) instead of (a,m)
//and when evaluating y = eval(x), just use y = -eval(x)
const ll is_query = -(1LL<<62);
struct Line {
    ll m, b;
    mutable function<const Line*()> succ;
    bool operator<(const Line& rhs) const {
        if (rhs.b != is_query) return m < rhs.m;
        const Line* s = succ();
        if (!s) return 0;
        ll x = rhs.m;
        return b - s->b < (s->m - m) * x;
    }
};
struct HullDynamic : public multiset<Line> { // will maintain upper hull for maximum
    bool bad(iterator y) {
        auto z = next(y);
        if (y == begin()) {
            if (z == end()) return 0;
            return y->m == z->m && y->b <= z->b;
        }
        auto x = prev(y);
        if (z == end()) return y->m == x->m && y->b <= x->b;
        return (x->b - y->b)*(z->m - y->m) >= (y->b - z->b)*(y->m - x->m);
    }
    void insert_line(ll m, ll b) {
        auto y = insert({ m, b });
        y->succ = [=] { return next(y) == end() ? 0 : &*next(y); };
        if (bad(y)) { erase(y); return; }
        while (next(y) != end() && bad(next(y))) erase(next(y));
        while (y != begin() && bad(prev(y))) erase(prev(y));
    }
    ll eval(ll x) {
        auto l = *lower_bound((Line) { x, is_query });
        return l.m * x + l.b;
    }
};

ll solve(vector<ll>&A, vector<ll>&B)
{
    int n = A.size();
    vector<ll>F(n);

    for(int i=1; i<n; i++)
        F[i]=F[i-1] + A[i]*(B[i]-B[i-1]);

    HullDynamic ch;

    ll initial = 0, res = 0;

    for(int i=0; i<n; i++)
        initial+=A[i]*B[i];

    res=initial;

    ch.insert_line(A[0],-A[0]*B[0]+F[0]);

    for(int j=1; j<n; j++)
    {
        ll y = -ch.eval(B[j]);
        ll delta = F[j] + y;
        res = max(res, initial - delta);
        ch.insert_line(A[j],-A[j]*B[j]+F[j]);
    }

    return res;
}

int main()
{
    ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);
    int n;
    cin>>n;
    vector<ll>A(n),B(n);

    for(auto&x:A)cin>>x;
    for(int i=0; i<n; i++)
        B[i]=i+1;

    ll res = max(solve(A,B), solve(B,A));
    reverse(A.begin(),A.end());
    reverse(B.begin(),B.end());
    res = max({res, solve(A,B), solve(B,A)});

    cout<<res;
}
