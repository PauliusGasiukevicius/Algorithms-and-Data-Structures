ll gcd(ll a, ll b, ll& x, ll& y) {
    if (a == 0) {
        x = 0;
        y = 1;
        return b;
    }
    ll x1, y1;
    ll d = gcd(b % a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return d;
}

/** Works for non-co-prime moduli.
 Returns {-1,-1} if solution does not exist or input is invalid.
 Otherwise, returns {x,L}, where x is the solution unique to mod L, where L = LCM(m1,m2,...)
   solves system of modular equations:
    {
    x = a1 mod m1
    x = a2 mod m2
    x = a3 mod m3
    ...
    }
*/
array<ll, 2> chinese_remainder_theorem( vector<ll> A, vector<ll> M ) {
    if(A.size() != M.size()) return {-1,-1}; /** Invalid input*/
    int n = A.size();

    ll a1 = A[0];
    ll m1 = M[0];

    for ( int i = 1; i < n; i++ ) {
        ll a2 = A[i];
        ll m2 = M[i];

        ll g = __gcd(m1, m2);
        if ( a1 % g != a2 % g ) return {-1,-1}; /** No solution */

        ll p, q;
        gcd(m1/g, m2/g, p, q);

        ll mod = m1 / g * m2; /** LCM of m1 and m2*/

        int x = ((a1*(m2/g))%mod *q %mod + (a2*(m1/g))%mod * p %mod) % mod;/** Overflow is possible*/

        a1 = x;
        if (a1 < 0) a1 += mod; /** Result is not suppose to be negative*/
        m1 = mod;
    }
    return {a1, m1};
}
