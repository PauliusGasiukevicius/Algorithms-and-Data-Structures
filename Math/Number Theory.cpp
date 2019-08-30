ll mulmod(ll a, ll b, ll mod){
    ll x = 0,y=a%mod;

    while(b > 0)
    {
        if(b&1)x = (x+y)%mod;
        y = (y*2)%mod;
        b /= 2;
    }
    return x%mod;
}

ll powm(ll a, ll n, ll mod){
    if(a==0)return 0;
    if(n==0 || a==1)return 1 % mod;
    ll pw = 1;
    while( n > 0)
    {
        if(n&1)pw = pw*a %mod, n--;
        a=a*a % mod;
        n/=2;
    }
    return pw;
}

bool millerTest(ll n, ll d) {
     mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
     ll a = uniform_int_distribution<ll>(2LL,n-2LL)(rnd);
     ll x = powm(a,d,n);
     if(x==1 || x==n-1)return 1;

     while(d!= n-1)
     {
         x=powm(x,2,n);
         d*=2;

         if(x==1)return 0;
         if(x==n-1)return 1;
     }
     return 0;
}

bool isPrimeMillerRabin(ll n, int iterations){ //probability this is correct is roughly 1 - (1/2)^iterations
    if(n==2 || n==3)return 1;
    if(n<4 || n%2==0)return 0;

    ll d = n-1;
    while(d%2==0)d/=2;

    while(iterations--)
    {
        if(!millerTest(n,d))
            return 0;
    }
    return 1;
}

ll pollard_rho(ll n, ll c){ //finds some factor of n in O(n^1/4), sometimes fails and gives n itself so call with various c
    ll x = 2, y = 2;
    while(1)
    {
        //x = (x*x+c)%n;
        x = (mulmod(x, x, n)+c)%n;
        //y = (y*y+c)%n, y = (y*y+c)%n;
        y = (mulmod(y, y, n)+c)%n;
        y = (mulmod(y, y, n)+c)%n;
        ll d = __gcd(x-y, n);
        if(d > 1)return d;
    }
}

//Finds GCD(a,b), also finds such x and y that a*x + b*y = GCD(a,b)
//Can be used to find modulo inverses: 
//Inverse (lets call it x) of A modulo M is solution to A*x + M*y = GCD(A,M) = 1. (if gcd > 1 -> no solutions with this method)
ll gcd(ll a, ll b, ll& x, ll& y){
    if (a == 0){
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

//Diophantine equation is equation of form a*x + b*y = c, where a,b,c is known and we need to find x,y
//This function returns false if no solutions exist
//otherwise it finds any {x0,y0} satisfying equation
//We can modify solution to suit our needs (like both positive, min(x+y), max(x+y) by using the fact that
//if x0 and y0 are solutions, x0+b/gcd(a,b) and y0-a/gcd(a,b) are also solutions
bool find_any_solution(ll a, ll b, ll c, ll &x0, ll &y0, ll &g) {
    g = gcd(abs(a), abs(b), x0, y0);
    if (c % g) return false;

    x0 *= c / g;
    y0 *= c / g;
    if (a < 0) x0 = -x0;
    if (b < 0) y0 = -y0;
    return true;
}


void shift_solution (ll & x, ll & y, ll a, ll b, ll cnt) {
    x += cnt * b;
    y -= cnt * a;
}

//Gives number of solutions satisfying that minx <= x <= maxx (samy for y)
ll find_all_solutions (ll a, ll b, ll c, ll minx, ll maxx, ll miny, ll maxy) {
    ll x, y, g;
    if (! find_any_solution (a, b, c, x, y, g))return 0;
    a /= g;  b /= g;

    ll sign_a = a>0 ? +1 : -1;
    ll sign_b = b>0 ? +1 : -1;

    shift_solution (x, y, a, b, (minx - x) / b);
    if (x < minx)shift_solution (x, y, a, b, sign_b);
    if (x > maxx)return 0;
    ll lx1 = x;

    shift_solution (x, y, a, b, (maxx - x) / b);
    if (x > maxx)shift_solution (x, y, a, b, -sign_b);
    ll rx1 = x;

    shift_solution (x, y, a, b, - (miny - y) / a);
    if (y < miny)shift_solution (x, y, a, b, -sign_a);
    if (y > maxy)return 0;
    ll lx2 = x;

    shift_solution (x, y, a, b, - (maxy - y) / a);
    if (y > maxy)shift_solution (x, y, a, b, sign_a);
    ll rx2 = x;

    if (lx2 > rx2)swap (lx2, rx2);
    ll lx = max (lx1, lx2);
    ll rx = min (rx1, rx2);

    if (lx > rx) return 0;
    return (rx - lx) / abs(b) + 1;
}

//All stuff below is for Implementation of generalized lucas theorem for finding nCr mod M for any n and small m
const int mxMod = 1000000;
vector<int> phi(mxMod+1, -1), primes;

bool arePrimesGenerated = false;
void genprime(){ //Generate primes and also calculate phi function values
    for(int i = 2;i <=mxMod; i++)
        if(phi[i]==-1)
        {
            primes.push_back(i);
            phi[i] = i-1;
            for(int j = 2*i; j<=mxMod; j+=i)
            {
                if(phi[j]==-1)phi[j] = j;
                phi[j] = (phi[j]/i)*(i-1);
            }
        }
}

ll powm(ll a, ll n, ll m = 1LL<<62){ //Calculates x raised to the power of p % m
    if(n==0)return 1%m;
    if(n&1)return a*powm(a,n-1,m)%m;
    return powm((a*a)%m,n/2,m);
}

ll inverse(ll x, ll m){
    if(x==1)return 1;
    return powm(x, phi[m]-1, m)%m;
}

ll ff(ll n, ll p, ll q){//finds (n!)_p (factorial of n without any p factors)
    ll x = 1, y = powm(p, q);
    for(int i = 2; i<=n;i++)
        if(i%p)
            x = (x*i)%y;
    return x%y;
}

ll nCr_mod_pq(ll n, ll m, ll p, ll q){ //Generalized Lucas Theorem calculates nCm mod p^q
    ll r = n-m, x = powm(p, q);
    ll e0 = 0, eq = 0;
    ll mul = (p==2&&q>=3)? 1: -1;
    ll cr = r, cm = m, carry = 0, cnt = 0;
    while(cr||cm||carry)
    {
        cnt++;
        ll rr = cr%p, rm = cm%p;
        if(rr + rm + carry >= p)
        {
            e0++;
            if(cnt>=q)eq++;
        }
        carry = (carry+rr+rm)/p;
        cr/=p;
        cm/=p;
    }
    mul = powm(p, e0)*powm(mul, eq);
    ll ret = (mul % x + x) % x;
    ll temp = 1;
    for(int i = 0;;i++)//This is THE line that calculates the formula
    {
        ret = ((ret*ff((n/temp)%x, p, q)%x)%x*(inverse(ff((m/temp)%x, p, q), x)%x*inverse(ff((r/temp)%x, p, q), x)%x)%x)%x;

        if(temp>n/p && temp>m/p && temp>r/p)
            break;
        temp = temp*p;
    }
    return (ret%x+x)%x;
}

array<ll, 2> chinese_remainder_theorem( vector<ll> A, vector<ll> M ) {
    if(A.size() != M.size()) return {-1,-1}; /** Invalid input*/
    ll n = A.size();

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

        ll x = ((a1*(m2/g))%mod *q %mod + (a2*(m1/g))%mod * p %mod) % mod;/** Overflow is possible*/

        a1 = x;
        if (a1 < 0) a1 += mod; /** Result is not suppose to be negative*/
        m1 = mod;
    }
    return {a1, m1};
}

ll nCr_mod_anyMod(ll n, ll r, ll m)
{
    if(!arePrimesGenerated)genprime(),arePrimesGenerated = 1;

    vector<ll>A,M; //A - results, M - modulo`s (pj^qi)
    vector<array<ll,2>>P; //stores factors in form {p,q} -> p^q

    for(ll p=2; p<=m; p++)
        if(m%p==0)
        {
            ll q = 0, pq = 1;
            while(m%p==0)m/=p,q++, pq*=p;
            P.push_back({p,q});
            M.push_back(pq);
        }

    for(auto&f:P)
    A.push_back(nCr_mod_pq(n,r,f[0],f[1]));

    return chinese_remainder_theorem(A,M)[0];
}