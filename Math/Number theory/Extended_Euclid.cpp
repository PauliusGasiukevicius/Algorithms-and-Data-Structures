//Finds GCD(a,b), also finds such x and y that a*x + b*y = GCD(a,b)
//Can be used to find modulo inverses: 
//Inverse (lets call it x) of A modulo M is solution to A*x + M*y = GCD(A,M) = 1. (if gcd > 1 -> no solutions with this method)
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
