#include <bits/stdc++.h>
using namespace std;
#define ll long long
#define ld long double
#define oo 1234567890

//If min is needed instead of max, just add lines as add(-a, -m) instead of add(a,m)
//and when evaluating y = query(x), just use y = -query(x)
bool Q;
struct Line {
	mutable ll k, m, p;
	bool operator<(const Line& o) const {
		return Q ? p < o.p : k < o.k;
	}
};

struct LineContainer : multiset<Line> {
	// (for doubles, use inf = 1/.0, div(a,b) = a/b)
	const ll inf = LLONG_MAX;
	ll div(ll a, ll b) { // floored division
		return a / b - ((a ^ b) < 0 && a % b); }
	bool isect(iterator x, iterator y) {
		if (y == end()) { x->p = inf; return false; }
		if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
		else x->p = div(y->m - x->m, x->k - y->k);
		return x->p >= y->p;
	}
	void add(ll k, ll m) {
		auto z = insert({k, m, 0}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p)
			isect(x, erase(y));
	}
	ll query(ll x) {
		assert(!empty());
		Q = 1; auto l = *lower_bound({0,0,x}); Q = 0;
		return l.k * x + l.m;
	}
};

ll solve(vector<ll>&A, vector<ll>&B)
{
    int n = A.size();
    vector<ll>F(n);

    for(int i=1; i<n; i++)
        F[i]=F[i-1] + A[i]*(B[i-1]-B[i]);

    LineContainer ch;

    ll initial = 0, res = 0;

    for(int i=0; i<n; i++)
        initial+=A[i]*B[i];

    res=initial;

    ch.add(A[0],-A[0]*B[0]-F[0]);

    for(int j=1; j<n; j++)
    {
        ll y = ch.query(B[j]);
        ll delta = F[j] + y;
        res = max(res, initial + delta);
        ch.add(A[j],-A[j]*B[j]-F[j]);
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
    for(auto&x:B)cin>>x;

    ll res = max(solve(A,B),solve(B,A));
    cout<<res;
}
