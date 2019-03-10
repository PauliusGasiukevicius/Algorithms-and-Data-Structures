//Finds GCD(a,b), also finds such x and y that a*x + b*y = GCD(a,b)
ll gcd(ll a, ll b, ll& x, ll& y)
{
    if (a == 0)
    {
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
    if (! find_any_solution (a, b, c, x, y, g))
        return 0;
    a /= g;  b /= g;

    ll sign_a = a>0 ? +1 : -1;
    ll sign_b = b>0 ? +1 : -1;

    shift_solution (x, y, a, b, (minx - x) / b);
    if (x < minx)
        shift_solution (x, y, a, b, sign_b);
    if (x > maxx)
        return 0;
    ll lx1 = x;

    shift_solution (x, y, a, b, (maxx - x) / b);
    if (x > maxx)
        shift_solution (x, y, a, b, -sign_b);
    ll rx1 = x;

    shift_solution (x, y, a, b, - (miny - y) / a);
    if (y < miny)
        shift_solution (x, y, a, b, -sign_a);
    if (y > maxy)
        return 0;
    ll lx2 = x;

    shift_solution (x, y, a, b, - (maxy - y) / a);
    if (y > maxy)
        shift_solution (x, y, a, b, sign_a);
    ll rx2 = x;

    if (lx2 > rx2)
        swap (lx2, rx2);
    ll lx = max (lx1, lx2);
    ll rx = min (rx1, rx2);

    if (lx > rx) return 0;
    return (rx - lx) / abs(b) + 1;
}
